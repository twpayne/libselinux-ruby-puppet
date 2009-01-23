Name: libselinux-ruby-puppet
Version: 0.24.7
Release: 1
Summary: The minimal SELinux bindings for Ruby required to run puppet
Group: Development/Libraries
License: Ruby
URL: http://github.com/twpayne/libselinux-ruby-puppet
Source: %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires: libselinux-devel
BuildRequires: ruby-devel
Conflicts: libselinux-ruby

%define sitearchdir %(eval "ruby -rrbconfig -e 'puts(Config::CONFIG[\\"sitearchdir\\"])'")

%description
The minimal SELinux bindings for Ruby required to run puppet

%prep
%setup -q

%build
ruby extconf.rb
make

%install
rm -fr %{buildroot}
make DESTDIR=%{buildroot} install

%clean
rm -fr %{buildroot}

%files
%defattr(-,root,root)
%{sitearchdir}/selinux.so
