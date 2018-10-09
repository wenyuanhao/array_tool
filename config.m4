dnl $Id$
dnl config.m4 for extension array_tool

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(array_tool, for array_tool support,
dnl Make sure that the comment is aligned:
dnl [  --with-array_tool             Include array_tool support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(array_tool, whether to enable array_tool support,
dnl Make sure that the comment is aligned:
[  --enable-array_tool           Enable array_tool support])

if test "$PHP_ARRAY_TOOL" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-array_tool -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/array_tool.h"  # you most likely want to change this
  dnl if test -r $PHP_ARRAY_TOOL/$SEARCH_FOR; then # path given as parameter
  dnl   ARRAY_TOOL_DIR=$PHP_ARRAY_TOOL
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for array_tool files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       ARRAY_TOOL_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$ARRAY_TOOL_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the array_tool distribution])
  dnl fi

  dnl # --with-array_tool -> add include path
  dnl PHP_ADD_INCLUDE($ARRAY_TOOL_DIR/include)

  dnl # --with-array_tool -> check for lib and symbol presence
  dnl LIBNAME=array_tool # you may want to change this
  dnl LIBSYMBOL=array_tool # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $ARRAY_TOOL_DIR/lib, ARRAY_TOOL_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_ARRAY_TOOLLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong array_tool lib version or lib not found])
  dnl ],[
  dnl   -L$ARRAY_TOOL_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(ARRAY_TOOL_SHARED_LIBADD)

  PHP_NEW_EXTENSION(array_tool, array_tool.c, $ext_shared)
fi
