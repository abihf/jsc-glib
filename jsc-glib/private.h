/* private.h
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

#include <glib.h>
#include <JavaScriptCore/JavaScript.h>
#include <libintl.h>
#include "config.h"
#include <glib/gi18n-lib.h>
#include "jsc-glib.h"


JSCObject *
jsc_object_new_from_native(JSCContext *context,
			   JSObjectRef js_object);

JSContextRef jsc_context_to_native (JSCContext *context);

/**
 * jsc_value_new_from_native: (constructor)
 * @ctx: a #JSCContext instance where value will be created
 * @js_value: native #JSValueRef
 *
 * Return: new #JSCValue from native #JSValueRef
 */
JSCValue *
jsc_value_new_from_native(JSCContext *context,
                          JSValueRef js_value);

JSValueRef
jsc_value_to_native(JSCValue *value);

void
jsc_error_set_from_exception(GError **error,
			     JSCContext *context,
			     JSValueRef exception);

JSObjectRef
jsc_object_to_native (JSCObject *object);



// -------------------- converter --------------

typedef	void (ValueConverter)(JSCContext *ctx,
	                          JSValueRef val,
	                          gpointer output,
	                          GError **error);

void
_value_to_boolean(JSCContext *ctx,
		  JSValueRef val,
		  gpointer output,
		  GError **error);

void
_value_to_number(JSCContext *ctx,
		 JSValueRef val,
		 gpointer output,
		 GError **error);
void
_value_to_string(JSCContext *ctx,
		 JSValueRef val,
		 gpointer output,
		 GError **error);

void
_value_to_object(JSCContext *ctx,
		 JSValueRef val,
		 gpointer output,
		 GError **error);

JSValueRef
JSValueMakeObject (JSContextRef ctx,
		  JSCObject *object);

JSValueRef
JSValueMakeStringUTF(JSContextRef ctx,
		 const gchar *str);
