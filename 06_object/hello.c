#include "php_hello.h"

zend_class_entry *my_class_ce;

ZEND_FUNCTION(hello){
	zval *obj;
	MAKE_STD_ZVAL(obj);
	object_init_ex(obj, my_class_ce);

	zval *_function_name;
	MAKE_STD_ZVAL(_function_name);
	ZVAL_STRINGL(_function_name, "hello", strlen("hello"), 1);

	//调用对象里的方法
	call_user_function(NULL, &obj, _function_name, return_value, 0, NULL );

	zval_ptr_dtor(&obj);
	return;
}
static zend_function_entry myclass_func[] = {
	ZEND_FE(hello, NULL)
	{NULL, NULL, NULL}
};


ZEND_METHOD(myclass, __construct){
	php_printf("new class!\n");
}

ZEND_METHOD(myclass, hello){
	php_printf("method echo: hello world!\n");
}

static zend_function_entry myclass_method[] = {
	ZEND_ME(myclass, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	ZEND_ME(myclass, hello,	NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

ZEND_MINIT_FUNCTION(hello) {
	zend_class_entry my_ce;
	INIT_CLASS_ENTRY(my_ce, "myclass", myclass_method);
	my_class_ce = zend_register_internal_class(&my_ce TSRMLS_CC);

	return SUCCESS;
}

//module entry
zend_module_entry hello_module_entry = {
	STANDARD_MODULE_HEADER,
	"hello", //扩展名称
	myclass_func, /* Functions */
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