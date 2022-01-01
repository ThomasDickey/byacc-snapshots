Summary: byacc - public domain Berkeley LALR Yacc parser generator
%define AppProgram byacc
%define AltProgram byacc2
%define AppVersion 20220101
%define UseProgram yacc
# $Id: byacc.spec,v 1.62 2022/01/01 14:59:55 tom Exp $
Name: %{AppProgram}
Version: %{AppVersion}
Release: 1
License: Public Domain, MIT
Group: Applications/Development
URL: ftp://invisible-island.net/%{AppProgram}
Source0: %{AppProgram}-%{AppVersion}.tgz
Packager: Thomas E. Dickey <dickey@invisible-island.net>

%description
This package provides a parser generator utility that reads a grammar
specification from a file and generates an LR(1) parser for it.  The
parsers consist of a set of LALR(1) parsing tables and a driver
routine written in the C programming language.  It has a public domain
license which includes the generated C.

%package -n byacc2
Summary:        Curses library with POSIX thread support.

%description -n byacc2
This package provides a parser generator utility that reads a grammar
specification from a file and generates an LR(1) parser for it.  The
parsers consist of a set of LALR(1) parsing tables and a driver
routine written in the C programming language.  It has a public domain
license which includes the generated C.

This package has the backtracking extension.

%prep

%define debug_package %{nil}

%setup -q -n %{AppProgram}-%{AppVersion}

%build
%define my_srcdir ..
%define CFG_OPTS \\\
  --verbose \\\
  --disable-echo \\\
  --enable-stdnoreturn \\\
  --target %{_target_platform} \\\
  --prefix=%{_prefix} \\\
  --srcdir=%{my_srcdir} \\\
  --bindir=%{_bindir} \\\
  --libdir=%{_libdir} \\\
  --mandir=%{_mandir}

%global _configure ../configure

mkdir BUILD-byacc
pushd BUILD-byacc
CONFIGURE_TOP=%{my_srcdir} \
%configure %{CFG_OPTS} \
  --program-prefix=b \
make
popd

mkdir BUILD-byacc2
pushd BUILD-byacc2
CONFIGURE_TOP=%{my_srcdir} \
%configure %{CFG_OPTS} \
  --enable-btyacc \
  --program-transform-name='s,\<yacc,byacc2,g' \
  --with-max-table-size=123456 \
make
popd

%install
[ "$RPM_BUILD_ROOT" != "/" ] && rm -rf $RPM_BUILD_ROOT

pushd BUILD-byacc
make install DESTDIR=$RPM_BUILD_ROOT
( cd $RPM_BUILD_ROOT%{_bindir} && ln -vs %{AppProgram} %{UseProgram} )
popd

pushd BUILD-byacc2
make install DESTDIR=$RPM_BUILD_ROOT
popd

%clean
[ "$RPM_BUILD_ROOT" != "/" ] && rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%{_prefix}/bin/%{AppProgram}
%{_prefix}/bin/%{UseProgram}
%{_mandir}/man1/%{AppProgram}.*

%files -n byacc2
%defattr(-,root,root)
%{_prefix}/bin/%{AltProgram}
%{_mandir}/man1/%{AltProgram}.*

%changelog
# each patch should add its ChangeLog entries here

* Sat Jan 01 2022 Thomas Dickey
- rename btyacc package to byacc2 to co-exist with traditional btyacc

* Fri May 25 2018 Thomas Dickey
- add btyacc package

* Sun Jul 09 2017 Thomas Dickey
- use predefined "configure"

* Sun Jun 06 2010 Thomas Dickey
- initial version
