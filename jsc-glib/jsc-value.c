/* jsc-value.c
 * 
 * This file is part of JSC-GLib
 * Copyright (C) 2015  Abi Hafshin
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 *
 * Author:
 *   Abi Hafshin    <abi@hafs.in>
 */

#include "jsc-glib.h"
#include "private.h"

/**
 * SECTION:jsc-value
 * @short_description: Class for storing javascript value
 * @title: JSCValue
 * @stability: Unstable
 * @include: jsc-glib.h
 *
 * This class hold JSValueRef and it's context
 */


struct _JSCValuePrivate
{
	JSCContext *context;
	JSValueRef value;
};


G_DEFINE_TYPE (JSCValue, jsc_value, G_TYPE_OBJECT);


static void
jsc_value_init (JSCValue *jsc_value)
{
	jsc_value->priv = G_TYPE_INSTANCE_GET_PRIVATE (jsc_value, JSC_TYPE_VALUE, JSCValuePrivate);


}

static void
jsc_value_finalize (GObject *object)
{
	g_object_unref (G_OBJECT (JSC_VALUE(object)->priv->context) );

	G_OBJECT_CLASS (jsc_value_parent_class)->finalize (object);
}

static void
jsc_value_class_init (JSCValueClass *klass)
{
	GObjectClass* object_class = G_OBJECT_CLASS (klass);
	g_type_class_add_private (klass, sizeof (JSCValuePrivate));
	object_class->finalize = jsc_value_finalize;
}

JSCValue *
jsc_value_new_from_native(JSCContext *context,
                          JSValueRef native_value)
{
	JSCValue *value      = JSC_VALUE (g_object_new (JSC_TYPE_VALUE, NULL) );
	value->priv->context = context;
	value->priv->value   = (JSValueRef)native_value;
	g_object_ref (G_OBJECT(context));
	return value;
}

JSValueRef
jsc_value_to_native (JSCValue *value)
{
	return value->priv->value;
}


/**
 * jsc_value_get_context:
 * @value: a #JSCValue
 *
 * Returns: (transfer none): a #JSCContext where @value was created
 */
JSCContext *
jsc_value_get_context(JSCValue *value)
{
	return value->priv->context;
}

#define CONTEXT(v) jsc_context_to_native (v->priv->context)
#define TO_NATIVE(v) v->priv->value

/**
 * jsc_value_get_value_type:
 * @value: a #JSCValue
 *
 * Returns: type of @value
 */
JSCValueType
jsc_value_get_value_type(JSCValue *value)
{
	// just cast it :)
	return (JSCValueType)JSValueGetType (CONTEXT(value), TO_NATIVE(value));
}

/**
 * jsc_value_equal:
 * @value: a #JSCValue
 * @other: other #JSCValue
 * @strict: strict mode. check the type
 * @error: (out) (nullable): error
 *
 * Check wether @value and @other equals
 * 
 * Returns: true if @value and @other equals
 */
gboolean
jsc_value_equal(JSCValue *value, 
                JSCValue *other, 
                gboolean strict, 
                GError **error)
{
	JSValueRef exception = NULL;
	gboolean result = false;
	if (strict)
		result = JSValueIsEqual (CONTEXT(value), TO_NATIVE(value), TO_NATIVE(other), &exception);
	else
		result = JSValueIsStrictEqual (CONTEXT(value), TO_NATIVE(value), TO_NATIVE(other));
	if (exception != NULL)
		jsc_error_set_from_exception (error, value->priv->context, exception);
	return result;
}

// ------------ undefined -----------------

JSCValue *
jsc_value_new_undefined(JSCContext *context)
{
	JSValueRef js_value = JSValueMakeUndefined ( jsc_context_to_native (context) );
	return jsc_value_new_from_native (context, js_value);
}

gboolean
jsc_value_is_undefined(JSCValue *value)
{
	return JSValueIsUndefined (CONTEXT (value), value->priv->value);
}


// ------------ null -----------------

JSCValue *
jsc_value_new_null(JSCContext *context)
{
	JSValueRef js_value = JSValueMakeNull (jsc_context_to_native (context));
	return jsc_value_new_from_native (context, js_value);
}

gboolean
jsc_value_is_null(JSCValue *value)
{
	return JSValueIsNull (CONTEXT (value), value->priv->value);
}

// ------------ boolean -----------------

JSCValue *
jsc_value_new_from_boolean(JSCContext *context, gboolean value)
{
	JSValueRef js_value = JSValueMakeBoolean (jsc_context_to_native (context), value);
	return jsc_value_new_from_native (context, js_value);
}

gboolean
jsc_value_is_boolean(JSCValue *value)
{
	return JSValueIsBoolean (jsc_context_to_native (value->priv->context), value->priv->value);
}

gboolean
jsc_value_get_boolean(JSCValue *value, GError **error)
{
	if (!jsc_value_is_boolean (value)) {
		g_set_error_literal (error, JSC_ERROR, JSC_ERROR_CONVERSION_ERROR, _("Invalid value type"));
		return false;
	}
	return JSValueToBoolean (jsc_context_to_native (value->priv->context),
	                         value->priv->value);
}


// ------------ double -----------------
JSCValue *
jsc_value_new_from_number(JSCContext *context, gdouble value)
{
	JSValueRef js_value = JSValueMakeNumber (jsc_context_to_native (context), value);
	return jsc_value_new_from_native (context, js_value);
}

gboolean
jsc_value_is_number(JSCValue *value)
{
	return JSValueIsNumber (jsc_context_to_native (value->priv->context), value->priv->value);
}

gdouble
jsc_value_get_number(JSCValue *value, GError **error)
{
	if (!jsc_value_is_number (value)) {
		g_set_error_literal (error, JSC_ERROR, JSC_ERROR_CONVERSION_ERROR, _("Invalid value type"));
		return 0;
	}
	JSValueRef exception = NULL;
	double ret = JSValueToNumber (jsc_context_to_native (value->priv->context),
	                         value->priv->value, &exception);
	if (exception != NULL) {
		jsc_error_set_from_exception (error, value->priv->context, exception);
		return 0;
	}
	return ret;
}

// ------------ string -----------------

/**
 * jsc_value_new_from_string: (constructor)
 * @context: a #JSCContext instance where value will be created
 * @value: string value
 *
 * Return: new #JSCValue containg string value
 */
JSCValue *
jsc_value_new_from_string(JSCContext *context, const gchar *value)
{
	JSStringRef string_value = JSStringCreateWithUTF8CString (value);
	JSValueRef js_value = JSValueMakeString (jsc_context_to_native (context), string_value);
	JSStringRelease (string_value);
	return jsc_value_new_from_native (context, js_value);
}

/**
 * jsc_value_is_string:
 * @value: a #JSCValue
 *
 * Return: return true if a #JSCValue is string
 */
gboolean
jsc_value_is_string(JSCValue *value)
{
	return JSValueIsString (jsc_context_to_native (value->priv->context), value->priv->value);
}

/**
 * jsc_value_get_string:
 * @value: a #JSCValue
 * @error: (nullable) (out): error
 *
 * Return: string value
 */
gchar *
jsc_value_get_string(JSCValue *value, GError **error)
{
	if (!jsc_value_is_string (value)) {
		g_set_error_literal(error, JSC_ERROR, JSC_ERROR_CONVERSION_ERROR, "Invalid value type");
		return NULL;
	}
	JSValueRef exception = NULL;
	JSStringRef string_ref = JSValueToStringCopy (jsc_context_to_native (value->priv->context),
	                                              value->priv->value, &exception);
	if (exception != NULL) {
		jsc_error_set_from_exception (error, value->priv->context, exception);
		return NULL;
	}
	int max_len = JSStringGetMaximumUTF8CStringSize (string_ref);
	gchar *buffer = g_malloc (max_len);
	JSStringGetUTF8CString (string_ref, buffer, max_len);
	JSStringRelease (string_ref);
	return buffer;
}



// ------------ object -----------------

gboolean
jsc_value_is_object(JSCValue *value)
{
	return JSValueIsNumber (CONTEXT (value), value->priv->value);
}

/**
 * jsc_value_get_object:
 * @value: a #JSCValue
 * @error: error
 * 
 * get object from value
 * 
 * Returns: (transfer full): a #JSCObject. 
 */
JSCObject *
jsc_value_get_object(JSCValue *value, GError **error)
{
	if (!jsc_value_is_object (value)) {
		g_set_error_literal (error, JSC_ERROR, JSC_ERROR_CONVERSION_ERROR, _("Invalid value type"));
		return NULL;
	}
	JSValueRef exception = NULL;
	JSObjectRef obj = JSValueToObject (CONTEXT (value),
	                         value->priv->value, &exception);
	if (exception != NULL) {
		jsc_error_set_from_exception (error, value->priv->context, exception);
		return NULL;
	}
	return jsc_object_new_from_native (value->priv->context, obj);
}



