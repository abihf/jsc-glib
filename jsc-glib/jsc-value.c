/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 4 -*-  */
/*
 * jsc-value.c
 * Copyright (C) 2015 Abi Hafshin <abi@hafs.in>
 *
 * glib-jsc is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * glib-jsc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "jsc-glib.h"
#include "private.h"

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

	/* TODO: Add initialization code here */
}

static void
jsc_value_finalize (GObject *object)
{
	/* TODO: Add deinitalization code here */

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
	JSCValue *value = JSC_VALUE (g_object_new (JSC_TYPE_VALUE, NULL) );
	value->priv->context = context;
	value->priv->value = (JSValueRef)native_value;
	return value;
}

JSValueRef
jsc_value_to_native (JSCValue *value)
{
	return value->priv->value;
}


JSCContext *
jsc_value_get_context(JSCValue *value)
{
	return value->priv->context;
}

#define CONTEXT(v) jsc_context_to_native (v->priv->context)
#define TO_NATIVE(v) v->priv->value

JSCValueType
jsc_value_type(JSCValue *value)
{
	return JSValueGetType (CONTEXT(value), TO_NATIVE(value));
}

gboolean
jsc_value_equal(JSCValue *value_a, JSCValue *value_b, gboolean strict, GError **error)
{
	JSValueRef exception = NULL;
	gboolean result = false;
	if (strict)
		result = JSValueIsEqual (CONTEXT(value_a), TO_NATIVE(value_a), TO_NATIVE(value_b), &exception);
	else
		result = JSValueIsStrictEqual (CONTEXT(value_a), TO_NATIVE(value_a), TO_NATIVE(value_b));
	if (exception != NULL)
		jsc_error_set_from_exception (error, value_a->priv->context, exception);
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

JSCValue *
jsc_value_new_from_string(JSCContext *context, const gchar *value)
{
	JSStringRef string_value = JSStringCreateWithUTF8CString (value);
	JSValueRef js_value = JSValueMakeString (jsc_context_to_native (context), string_value);
	JSStringRelease (string_value);
	return jsc_value_new_from_native (context, js_value);
}

gboolean
jsc_value_is_string(JSCValue *value)
{
	return JSValueIsString (jsc_context_to_native (value->priv->context), value->priv->value);
}

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



