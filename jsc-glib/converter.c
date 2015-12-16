/* converter.c
 *
 * Copyright (C) 2015 Abi Hafshin <abi@hafs.in>
 *
 * This file is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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