#include "php_hello.h"

zend_class_entry *interface_ce, *parent_class_ce, *my_class_ce;

ZEND_METHOD(parent_class, hello){
	php_printf("hello	world!\n");
}

static zend_function_entry interface_method[] = {
	ZEND_ABSTRACT_ME(my_interface, hello, NULL)
	{NULL, NULL, NULL}
};

static zend_function_entry parent_class_method[] = {
	ZEND_ME(parent_class, hello, NULL,ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

static zend_function_entry my_class_method[] = {
	{NULL, NULL, NULL}
};

ZEND_MINIT_FUNCTION(hello) {
	zend_class_entry i_ce, p_ce, my_ce;
	INIT_CLASS_ENTRY(i_ce, "my_interface", interface_method);
	interface_ce = zend_register_internal_interface(&i_ce TSRMLS_CC);

	//定义父类，最后使用zend_class_implements函数声明它实现的接口
	INIT_CLASS_ENTRY(p_ce, "parent_class", parent_class_method);
	parent_class_ce = zend_register_internal_class(&p_ce TSRMLS_CC);
	//implement一个接口，第二个参数为1
	zend_class_implements(parent_class_ce TSRMLS_CC, 1, interface_ce);

	//定义子类
	INIT_CLASS_ENTRY(my_ce, "my_class", my_class_method);
	//继承父类
	my_class_ce = zend_register_internal_class_ex(&my_ce, parent_class_ce, "parent_class" TSRMLS_CC);

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
