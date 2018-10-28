#include "php_hello.h"

//方法申明
//ZEND_METHOD(my_class,	__construct);
//ZEND_METHOD(my_class,	__destruct );
//ZEND_METHOD(my_class,	public_method);

//方法实现
ZEND_METHOD(my_class, __construct){
	php_printf("我是__construct方法\n");
}

ZEND_METHOD(my_class, __destruct ){
	php_printf("我是__destruct方法\n");
}

ZEND_METHOD(my_class, public_method){
	php_printf("我是public类型的方法\n");
}

zend_class_entry *my_class_ce;
static zend_function_entry my_class_method[] = {
		ZEND_ME(my_class, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
		ZEND_ME(my_class, __destruct , NULL, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
		ZEND_ME(my_class, public_method, NULL, ZEND_ACC_PUBLIC)
		{NULL, NULL, NULL}
};

ZEND_MINIT_FUNCTION(hello) {
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "my_class", my_class_method);
	my_class_ce = zend_register_internal_class(&ce TSRMLS_CC);

	//注意：ZEND_ACC_FINAL是用来修饰方法的，而ZEND_ACC_FINAL_CLASS是用来修饰类的
	my_class_ce->ce_flags	|=	ZEND_ACC_FINAL_CLASS;

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
