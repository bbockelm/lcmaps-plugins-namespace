Summary: PID namespaces implementation for glexec as a LCMAPS plugin
Name: lcmaps-plugins-namespace
Version: 0.2.0
Release: 1%{?dist}
License: Public Domain
Group: System Environment/Libraries

# Generated with:
# git clone https://github.com/bbockelm/lcmaps-plugins-namespace.git
# cd lcmaps-plugin-namespace
# ./bootstrap
# ./configure
# make dist
Source0: %{name}-%{version}.tar.gz

BuildRequires: lcmaps-common-devel

BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-buildroot

%description
This plugin utilizes the Linux PID namespace feature to
track the processes spawned by glexec.

%prep
%setup -q

%build

%configure
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT

make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,-)
%{_libdir}/lcmaps/liblcmaps_namespace.so
%{_libdir}/lcmaps/lcmaps_namespace.mod
%{_libexecdir}/%{name}/lcmaps-namespace-init

%changelog
* Sat Dec 13 2014 Brian Bockelman <bbockelm@cse.unl.edu> - 0.2.0-1
- Remount /proc and drop privs in the exec'd binary.

* Sat Dec 13 2014 Brian Bockelman <bbockelm@cse.unl.edu> - 0.1.0-1
- Initial implementation of the PID namespace plugin.

