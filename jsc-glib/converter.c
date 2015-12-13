
#include "jsc-glib.h"
#include "private.h"


// ------------ js conversation --------

#define CONTEXT jsc_context_to_native (ctx)

void
_value_to_boolean(JSCContext *ctx, JSValueRef val, gpointer output, GError **error)
{
  *(gboolean*)output = JSValueToBoolean (CONTEXT, val);
}

void
_value_to_number(JSCContext *ctx, JSValueRef val, gpointer output, GError **error)
{
	JSValueRef exception = NULL;
	double result = JSValueToNumber (CONTEXT, val, &exception);
	jsc_error_set_from_exception (error, ctx, exception);
	*(gdouble*)output = result;
}

void
_value_to_string(JSCContext *ctx,
		 JSValueRef val,
		 gpointer output,
		 GError **error)
{
  	JSValueRef exception = NULL;
	JSStringRef result = JSValueToStringCopy (CONTEXT, val, &exception);
	if (exception == NULL) {
		int max_len = JSStringGetMaximumUTF8CStringSize (result);
		gchar *buffer = g_malloc (max_len);
		JSStringGetUTF8CString (result, buffer, max_len);
		JSStringRelease (result);
		*(gchar **)output = buffer;
	} else {
		jsc_error_set_from_exception (error, ctx, exception);
		*(gchar **)output = NULL;
	}
}

JSValueRef
JSValueMakeStringUTF(JSContextRef ctx,
		 const gchar *str)
{
	JSStringRef js_string = JSStringCreateWithUTF8CString(str);
	JSValueRef result = JSValueMakeString (ctx, js_string);
	JSStringRelease (js_string);
	return result;
}

void
_value_to_object(JSCContext *ctx,
		 JSValueRef val,
		 gpointer output,
		 GError **error)
{
	JSValueRef exception = NULL;
	JSObjectRef object = JSValueToObject (CONTEXT, val, &exception);
	*(JSObjectRef *)output = object;
}

JSValueRef
JSValueMakeObject (JSContextRef ctx,
		  JSCObject *object)
{
	return (JSValueRef) jsc_object_to_native (object);
}