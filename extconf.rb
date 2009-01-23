require "mkmf"

have_library("selinux", "is_selinux_enabled")
create_makefile("selinux")
