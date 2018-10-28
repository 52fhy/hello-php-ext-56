#include "php_hello.h"

/*定义PHP函数*/
PHP_FUNCTION(hello)
{
    php_printf("Hello World!\n");
}

PHP_FUNCTION(my_pi)
{
    RETURN_DOUBLE(3.14159265358);
}

PHP_FUNCTION(my_output)
{
    // php_printf("Hello World %s!\n", "phper");
	php_error_docref(NULL TSRMLS_CC, E_ERROR, "Failed to write %d bytes to %s", 1, "filename");
}

static zend_function_entry hello_functions[] = {
    ZEND_FE(hello,        NULL)
    ZEND_FE(my_pi,        NULL)
	ZEND_FE(my_output,        NULL)
    { NULL, NULL, NULL }
};

//module entry
zend_module_entry hello_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901 /* 代表PHP4.2.0版本 */
     STANDARD_MODULE_HEADER,
#endif
    "hello", //这个地方是扩展名称，往往我们会在这个地方使用一个宏。
    hello_functions, /* Functions */
    NULL, /* MINIT */
    NULL, /* MSHUTDOWN */
    NULL, /* RINIT */
    NULL, /* RSHUTDOWN */
    NULL, /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
    "0.1", //这个地方是我们扩展的版本
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_HELLO
ZEND_GET_MODULE(hello)
#endif