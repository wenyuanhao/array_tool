/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_array_tool.h"

/* If you declare any globals in php_array_tool.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(array_tool)
*/

/* True global resources - no need for thread safety here */
static int le_array_tool;

/* {{{ array_tool_functions[]
 *
 * Every user visible function must have an entry in array_tool_functions[].
 */
const zend_function_entry array_tool_functions[] = {
	PHP_FE(confirm_array_tool_compiled,	NULL)		/* For testing, remove later. */
	//PHP_FE(array_column,	NULL)
	//PHP_FE(merge_key_array,	NULL)
	PHP_FE_END	/* Must be the last line in array_tool_functions[] */
};
/* }}} */

/* {{{ array_tool_module_entry
 */
zend_module_entry array_tool_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"array_tool",
	array_tool_functions,
	PHP_MINIT(array_tool),
	PHP_MSHUTDOWN(array_tool),
	PHP_RINIT(array_tool),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(array_tool),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(array_tool),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_ARRAY_TOOL_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_ARRAY_TOOL
ZEND_GET_MODULE(array_tool)
#endif

zend_class_entry *array_tool_ce;
static zend_function_entry array_tool_method[]= {
	//ZEND_ME(array_tool, public_method, NULL, ZEND_ACC_PUBLIC)
	ZEND_ME(array_tool, array_column, NULL, ZEND_ACC_STATIC|ZEND_ACC_PUBLIC)
	ZEND_ME(array_tool, merge_key_array, NULL, ZEND_ACC_STATIC|ZEND_ACC_PUBLIC)
	{NULL,NULL,NULL}
};

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("array_tool.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_array_tool_globals, array_tool_globals)
    STD_PHP_INI_ENTRY("array_tool.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_array_tool_globals, array_tool_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_array_tool_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_array_tool_init_globals(zend_array_tool_globals *array_tool_globals)
{
	array_tool_globals->global_value = 0;
	array_tool_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(array_tool)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "array_tool", array_tool_method);
	array_tool_ce = zend_register_internal_class(&ce TSRMLS_CC);
	//define property
	//zend_declare_property_null(array_tool_ce, "public_var", strlen("public_var"), ZEND_ACC_PUBLIC TSRMLS_CC);
	return SUCCESS;
}

/*ZEND_METHOD(array_tool, public_method){
	php_printf("this is a public method\n");
}*/
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(array_tool)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(array_tool)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(array_tool)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(array_tool)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "array_tool support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_array_tool_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_array_tool_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "array_tool", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/

static inline
zend_bool array_column_param_helper(zval **param,
                                    const char *name TSRMLS_DC) {
    switch (Z_TYPE_PP(param)) {
        case IS_DOUBLE:
            convert_to_long_ex(param);
            /* fallthrough */
        case IS_LONG:
            return 1;   

        case IS_OBJECT:
            convert_to_string_ex(param);
            /* fallthrough */
        case IS_STRING:
            return 1;   

        default:
            php_error_docref(NULL TSRMLS_CC, E_WARNING, "The %s key should be either a string or an integer", name);
            return 0;   
    }   
}



/* {{{ proto string array_column(array arr, string key, string column)
    */
//PHP_FUNCTION(array_column)
ZEND_METHOD(array_tool, array_column){
	zval **zcolumn = NULL, **zkey = NULL, **data;
	HashTable *arr_hash;
	HashPosition pointer;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "hZ!|Z!", &arr_hash, &zcolumn, &zkey) == FAILURE) {
    	return;
	}

	if ((zcolumn && !array_column_param_helper(zcolumn, "column" TSRMLS_CC)) ||
    	(zkey && !array_column_param_helper(zkey, "index" TSRMLS_CC))) {
    	RETURN_FALSE;
	}

	array_init(return_value);
	for (zend_hash_internal_pointer_reset_ex(arr_hash, &pointer);
        zend_hash_get_current_data_ex(arr_hash, (void**)&data, &pointer) == SUCCESS;
        zend_hash_move_forward_ex(arr_hash, &pointer)) {
    	zval **zcolval, **zkeyval = NULL;
    	HashTable *ht;

		if (Z_TYPE_PP(data) != IS_ARRAY) {
			/* Skip elemens which are not sub-arrays */
			continue;
		}
		ht = Z_ARRVAL_PP(data);

		if (!zcolumn) {
			/* NULL column ID means use entire subarray as data */
			zcolval = data;

			/* Otherwise, skip if the value doesn't exist in our subarray */
		} else if ((Z_TYPE_PP(zcolumn) == IS_STRING) &&
			(zend_hash_find(ht, Z_STRVAL_PP(zcolumn), Z_STRLEN_PP(zcolumn) + 1, (void**)&zcolval) == FAILURE)) {
			continue;
		} else if ((Z_TYPE_PP(zcolumn) == IS_LONG) &&
			(zend_hash_index_find(ht, Z_LVAL_PP(zcolumn), (void**)&zcolval) == FAILURE)) {
			continue;
		}

		/* Failure will leave zkeyval alone which will land us on the final else block below
		 * which is to append the value as next_index
		 */
		if (zkey && (Z_TYPE_PP(zkey) == IS_STRING)) {
			zend_hash_find(ht, Z_STRVAL_PP(zkey), Z_STRLEN_PP(zkey) + 1, (void**)&zkeyval);
		} else if (zkey && (Z_TYPE_PP(zkey) == IS_LONG)) {
			zend_hash_index_find(ht, Z_LVAL_PP(zkey), (void**)&zkeyval);
		}

		Z_ADDREF_PP(zcolval);
		if (zkeyval && Z_TYPE_PP(zkeyval) == IS_STRING) {
			//key is string
			add_assoc_zval(return_value, Z_STRVAL_PP(zkeyval), *zcolval);
		} else if (zkeyval && Z_TYPE_PP(zkeyval) == IS_LONG) {
			//key is long 
			add_index_zval(return_value, Z_LVAL_PP(zkeyval), *zcolval);
		} else if (zkeyval && Z_TYPE_PP(zkeyval) == IS_OBJECT) {
			//key is object 
			SEPARATE_ZVAL(zkeyval);
			convert_to_string(*zkeyval);
			add_assoc_zval(return_value, Z_STRVAL_PP(zkeyval), *zcolval);
		} else {
			//no key
			add_next_index_zval(return_value, *zcolval);
		}
	}
}
/* }}} */

/* {{{ */
//PHP_FUNCTION(merge_key_array){
ZEND_METHOD(array_tool, merge_key_array){
	HashTable *arr_hash;
	char *key;
	int key_len;
	HashPosition pos;
	zval **zkey, **zkeyval, **zdata, **znewdata, 
		*empty_arr;
	

	//php_error_docref(NULL TSRMLS_CC, E_WARNING, "%p", zkey);
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "hZ", &arr_hash, &zkey) == FAILURE) {
    	RETURN_FALSE;
	}
	if(Z_TYPE_PP(zkey) != IS_LONG && Z_TYPE_PP(zkey) != IS_STRING){
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "key is not int or string");
		RETURN_FALSE;
	}
	array_init(return_value);

	zend_hash_internal_pointer_reset_ex(arr_hash, &pos);
	while(zend_hash_get_current_data_ex(arr_hash, (void**)&zdata, &pos) == SUCCESS) {
		zend_hash_move_forward_ex(arr_hash, &pos);
		if(Z_TYPE_PP(zdata) != IS_ARRAY){
			continue;
		}		

		if (Z_TYPE_PP(zkey) == IS_LONG) {
 			if(zend_hash_index_find(Z_ARRVAL_PP(zdata), Z_LVAL_PP(zkey), (void**)&zkeyval) == FAILURE){
				continue;
			}
		}else{
			if(zend_hash_find(Z_ARRVAL_PP(zdata), Z_STRVAL_PP(zkey), Z_STRLEN_PP(zkey)+1, (void**)&zkeyval) == FAILURE){
				continue;
			}	
		}
		
		if(Z_TYPE_PP(zkeyval) == IS_LONG){
			zval_add_ref(zdata);	
			if(zend_hash_index_find(Z_ARRVAL_P(return_value), Z_LVAL_PP(zkeyval), (void**)&znewdata) == SUCCESS){
				add_next_index_zval(*znewdata, *zdata);
			}else{
				empty_arr = NULL; 
				MAKE_STD_ZVAL(empty_arr);
				array_init(empty_arr);
		    	add_next_index_zval(empty_arr, *zdata);
				add_index_zval(return_value, Z_LVAL_PP(zkeyval), empty_arr);	
			}
		}else if(Z_TYPE_PP(zkeyval) == IS_STRING){
			zval_add_ref(zdata);	
			if(zend_hash_find(Z_ARRVAL_P(return_value), Z_STRVAL_PP(zkeyval), Z_STRLEN_PP(zkeyval)+1, (void**)&znewdata) == SUCCESS){
				add_next_index_zval(*znewdata, *zdata);
			}else{
				empty_arr = NULL; 
				MAKE_STD_ZVAL(empty_arr);
				array_init(empty_arr);
		    	add_next_index_zval(empty_arr, *zdata);
				add_assoc_zval(return_value, Z_STRVAL_PP(zkeyval), empty_arr);	
			}
		}	
	}
}
/* }}} */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
