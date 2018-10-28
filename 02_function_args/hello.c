#include "php_hello.h"

/*定义PHP函数*/
PHP_FUNCTION(hello_params)
{
    char *name;
    int len;
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &len) == FAILURE){
        RETURN_NULL();
    }
    php_printf("Hello %s!\n", name);
    // php_printf("Hello    ");
    // PHPWRITE(name,   len);
    // php_printf("!\n");
}

ZEND_FUNCTION(hello_params_some)   {
    char    *name;
    int name_len;
    char    *greeting;
    int greeting_len;
    if  (zend_parse_parameters(ZEND_NUM_ARGS()  TSRMLS_CC,  "ss",&name, &name_len,  &greeting,  &greeting_len)  ==  FAILURE)    {
        RETURN_NULL();
    }
    php_printf("Hello   ");
    PHPWRITE(greeting,  greeting_len);
    php_printf("    ");
    PHPWRITE(name,  name_len);
    php_printf("!\n");
}

PHP_FUNCTION(hello_default_params)
{
    char *name = "world";
    int len = sizeof("world") - 1;
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &name, &len) == FAILURE){
        RETURN_NULL();
    }
    php_printf("Hello ");
    PHPWRITE(name,  len);
    php_printf("!\n");
}


//参数声明
ZEND_BEGIN_ARG_INFO(arginfo_hello_function_args, 0)
    ZEND_ARG_ARRAY_INFO(0, arr, 0) //是否引用,参数名称,是否为null
    ZEND_ARG_OBJ_INFO(0, obj, MyClass, 0) //是否引用,参数名称,类名,是否为null
    ZEND_ARG_INFO(0, arg3) //是否引用,参数名称
ZEND_END_ARG_INFO()
//函数定义
ZEND_FUNCTION(hello_function_args)
{
    zval *arr;
    zval *obj;
    long len;
    if  (zend_parse_parameters(ZEND_NUM_ARGS()  TSRMLS_CC,  "aol",&arr, &obj,   &len)   ==  FAILURE)    {
        RETURN_NULL();
    }
}

static zend_function_entry hello_functions[] = {
    ZEND_FE(hello_params,        NULL)
	ZEND_FE(hello_params_some,        NULL)
	ZEND_FE(hello_default_params,        NULL)
	ZEND_FE(hello_function_args,        arginfo_hello_function_args)
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