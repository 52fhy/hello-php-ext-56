#include "php_hello.h"

PHP_FUNCTION(hello) {
	php_printf("Hello World!\n");
}

static zend_function_entry hello_functions[] = {
	ZEND_FE(hello, NULL)
	{NULL, NULL, NULL }
};

//方法申明：如果方法定义在ZEND_ME使用之前，可以不用申明
//另外：ZEND_METHOD的第一个参数建议和类名一致，宏展开后和方法名拼接在一起。第一个参数和zend_class_entry *my_class_ce没有关系
ZEND_METHOD(my_class,	__construct);
ZEND_METHOD(my_class,	__destruct );
ZEND_METHOD(my_class,	public_method);

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
		//ZEND_ME第一个参数即为ZEND_METHOD的第一个参数
		ZEND_ME(my_class, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
		ZEND_ME(my_class, __destruct , NULL, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
		ZEND_ME(my_class, public_method, NULL, ZEND_ACC_PUBLIC)
		ZEND_ABSTRACT_ME(my_class, abstract_method, NULL)
		{NULL, NULL, NULL}
};

ZEND_MINIT_FUNCTION(hello) {
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "my_class", my_class_method);
	my_class_ce = zend_register_internal_class(&ce TSRMLS_CC);

	//声明类属性
	zend_declare_property_null(my_class_ce, "public_var", strlen("public_var"),	ZEND_ACC_PUBLIC	TSRMLS_CC);
	zend_declare_property_string(my_class_ce, "ver", strlen("ver"), "1.0", ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(my_class_ce, "private_var", strlen("private_var"),	ZEND_ACC_PRIVATE TSRMLS_CC);

	//声明类常量
	zend_declare_class_constant_long(my_class_ce, "TYPE_1", strlen("TYPE_1"), 100 TSRMLS_DC);
	zend_declare_class_constant_bool(my_class_ce, "TYPE_TRUE", strlen("TYPE_TRUE"), 1 TSRMLS_DC);
	zend_declare_class_constant_string(my_class_ce, "TYPE_STRING", strlen("TYPE_STRING"), "string" TSRMLS_DC);

	return SUCCESS;
}

//module entry
zend_module_entry hello_module_entry = {
	STANDARD_MODULE_HEADER,
	"hello", //扩展名称
	hello_functions, /* Functions */
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
