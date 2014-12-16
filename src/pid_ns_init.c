
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <errno.h>

long int child_pid;

void signal_handler(int signo)
{
    if (child_pid > 0)
    {
        kill(child_pid, signo);
    }
}

int main(int argc, char **argv)
{
    child_pid = -1;

    if (argc != 4)
    {
        return 127;
    }

    // Get the child PID from the parent
    errno = 0;
    child_pid = strtol(argv[1], NULL, 10);
    if (errno)
    {
        return 127;
    }

    errno = 0;
    uid_t uid = strtol(argv[2], NULL, 10);
    if (errno)
    {
        kill(child_pid, SIGKILL);
        return 127;
    }
    gid_t gid = strtol(argv[3], NULL, 10);
    if (errno)
    {
        kill(child_pid, SIGKILL);
        return 127;
    }
    if (-1 == setgid(gid))
    {
        kill(child_pid, SIGKILL);
        return 1;
    }
    if (-1 == setuid(uid))
    {
        kill(child_pid, SIGKILL);
        return 1;
    }

    // Install signal handler so we can pass signals to the children.
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGHUP, &sa, 0);
    sigaction(SIGINT, &sa, 0);
    sigaction(SIGQUIT, &sa, 0);
    sigaction(SIGILL, &sa, 0);
    sigaction(SIGABRT, &sa, 0);
    sigaction(SIGTERM, &sa, 0);
    sigaction(SIGSEGV, &sa, 0);
    sigaction(SIGPIPE, &sa, 0);
    sigaction(SIGUSR1, &sa, 0);
    sigaction(SIGUSR2, &sa, 0);

    // Log to syslog that we have started watching:
    if (child_pid != 2) // We are the watcher outside the PID namespace.
    {
        openlog("lcmaps-namespace", LOG_PID, LOG_DAEMON);
        syslog(LOG_NOTICE, "glexec.mon[%d#%ld]: Started, target uid %d\n", getpid(), child_pid, uid);
    }

    // Reap children, pass along signals, exit correctly.
    int status;
    while (1)
    {
        int result = wait(&status);
        if (((result == -1) && (errno == EINTR)) || (result != child_pid))
        {
            continue;
        }

        struct rusage usage;
        if ((child_pid != 2) && (-1 != getrusage(RUSAGE_CHILDREN, &usage)))
        {
            syslog(LOG_NOTICE, "glexec.mon[%d#%ld]: Terminated, CPU user %lu system %lu", getpid(), child_pid, usage.ru_utime.tv_sec, usage.ru_stime.tv_sec);
        }

        if (WIFEXITED(status)) {_exit(WEXITSTATUS(status));}
        else {_exit(WTERMSIG(status)+128);}
        _exit(status);
    }
}

