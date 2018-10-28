#include "php_hello.h"

zend_class_entry *interface_ce;
static zend_function_entry interface_method[] = {
	ZEND_ABSTRACT_ME(my_interface, hello, NULL)
	{NULL, NULL, NULL}
};

ZEND_MINIT_FUNCTION(hello) {
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "my_interface", interface_method);
	interface_ce = zend_register_internal_interface(&ce TSRMLS_CC);

	return SUCCESS;
}

//module entry
zend_module_entry hello_module_entry = {
	STANDARD_MODULE_HEADER,
	"hello", //扩展名称
	NULL, /* Functions */
	PHP_MINIT(hello), /* MINIT */
	NULL, /* MSHUTDOWN */
	NULL, /* RINIT */
	NULL, /* RSHUTDOWN */
	NULL, /* MINFO */
	"0.1", //扩展的版本
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_HELLO
		ZEND_GET_MODULE(hello)
#endif
