/***************************************************************************
 *            private.h
 *
 *  Mon December 07 00:45:23 2015
 *  Copyright  2015  Abi Hafshin
 *  <user@host>
 ****************************************************************************/

#include <glib.h>
#include <JavaScriptCore/JavaScript.h>
#include <libintl.h>
#include "config.h"
#include <glib/gi18n-lib.h>


JSCObject *jsc_object_new_from_native(JSCContext *context, JSObjectRef js_object);

JSContextRef jsc_context_to_native (JSCContext *context);

/**
 * jsc_value_new_from_native: (constructor)
 * @ctx: a #JSCContext instance where value will be created
 * @js_value: native #JSValueRef
 * 
 * Return: new #JSCValue from native #JSValueRef
 */JSCValue *
jsc_value_new_from_native(JSCContext *context, 
                          JSValueRef js_value);

JSValueRef jsc_value_to_native(JSCValue *value);

void 
jsc_error_set_from_exception(GError **error, JSCContext *context, JSValueRef exception);
