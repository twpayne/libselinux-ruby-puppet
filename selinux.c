#include <ruby.h>
#include <selinux/selinux.h>

VALUE Selinux_is_selinux_enabled(VALUE self)
{
	return INT2FIX(is_selinux_enabled());
}

VALUE Selinux_lgetfilecon(VALUE self, VALUE path)
{
	char *_path = StringValuePtr(path);
	security_context_t _con = NULL;
	int _result = lgetfilecon(_path, &_con);
	VALUE result = rb_ary_new3(2, INT2FIX(_result), _result == -1 ? Qnil : rb_str_new2(_con));
	freecon(_con);
	return result;
}

VALUE Selinux_lsetfilecon(VALUE self, VALUE path, VALUE con)
{
	char *_path = StringValuePtr(path);
	security_context_t _con = StringValuePtr(con);
	return INT2FIX(lsetfilecon(_path, _con));
}

VALUE Selinux_matchpathcon(VALUE self, VALUE path, VALUE mode)
{
	char *_path = StringValuePtr(path);
	mode_t _mode = FIX2INT(mode);
	security_context_t _con = NULL;
	int _result = matchpathcon(_path, _mode, &_con);
	VALUE result = rb_ary_new3(2, INT2FIX(_result), _result == -1 ? Qnil : rb_str_new2(_con));
	freecon(_con);
	return result;
}

void Init_selinux(void)
{
	VALUE rb_mSelinux = rb_define_module("Selinux");
	rb_define_singleton_method(rb_mSelinux, "is_selinux_enabled", Selinux_is_selinux_enabled, 0);
	rb_define_singleton_method(rb_mSelinux, "lgetfilecon", Selinux_lgetfilecon, 1);
	rb_define_singleton_method(rb_mSelinux, "lsetfilecon", Selinux_lsetfilecon, 2);
	rb_define_singleton_method(rb_mSelinux, "matchpathcon", Selinux_matchpathcon, 2);
}
