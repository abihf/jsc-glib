/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 4 -*-  */
/*
 * jsc-object.c
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

struct _JSCObjectPrivate
{
   JSCContext *context;
   JSObjectRef object;
};


enum
{
  PROP_0,

  PROP_CONTEXT
};



G_DEFINE_TYPE (JSCObject, jsc_object, G_TYPE_OBJECT);

static void
jsc_object_init (JSCObject *jsc_object)
{
  jsc_object->priv = G_TYPE_INSTANCE_GET_PRIVATE (jsc_object, JSC_TYPE_OBJECT, JSCObjectPrivate);

  /* TODO: Add initialization code here */
}

static void
jsc_object_finalize (GObject *object)
{
  /* TODO: Add deinitalization code here */

  G_OBJECT_CLASS (jsc_object_parent_class)->finalize (object);
}

static void
jsc_object_class_init (JSCObjectClass *klass)
{
  GObjectClass* object_class = G_OBJECT_CLASS (klass);

  g_type_class_add_private (klass, sizeof (JSCObjectPrivate));

  object_class->finalize = jsc_object_finalize;
}

JSCContext *
jsc_object_get_context(JSCObject *object)
{
	return object->priv->context;
}

#define CONTEXT(o)  jsc_context_to_native (o->priv->context)
#define TO_NATIVE(o) o->priv->object


JSCObject *
jsc_object_new_from_native(JSCContext *context, 
                           JSObjectRef js_object)
{
  JSCObject *object = JSC_OBJECT(g_object_new(JSC_TYPE_OBJECT, NULL));
  object->priv->context = context;
  object->priv->object = js_object;
  return object;
}

JSObjectRef
jsc_object_to_native (JSCObject *object)
{
	return object->priv->object;
}


static void 
jsc_object_set_property_native (JSCObject *object, 
                         const gchar *name, 
                         JSValueRef value, 
                         JSCPropertyAttributeFlags flags,
                         GError **error)
{
	g_return_if_fail (JSC_IS_OBJECT (object));

	JSContextRef context = CONTEXT (object);
	JSObjectRef js_object = TO_NATIVE (object);
	JSStringRef prop_name = JSStringCreateWithUTF8CString (name);

	JSValueRef exception = NULL;
	JSObjectSetProperty (context, js_object, prop_name, value, flags, &exception);
	JSStringRelease (prop_name);

	if (exception != NULL) {
		jsc_error_set_from_exception (error, object->priv->context, exception);
	}
}

static JSValueRef
jsc_object_get_property_native (JSCObject *object, 
                    const gchar *name, 
                    GError **error)
{
	JSContextRef context = CONTEXT (object);
	JSObjectRef js_object = TO_NATIVE (object);
	JSStringRef prop_name = JSStringCreateWithUTF8CString (name);
	JSValueRef js_value = JSObjectGetProperty (context, js_object, prop_name, NULL);
	
	JSStringRelease (prop_name);
	return js_value;
}


void
jsc_object_set_property (JSCObject *object, 
                         const gchar *name, 
                         JSCValue *value, 
                         JSCPropertyAttributeFlags flags,
                         GError **error)
{
	g_return_if_fail (JSC_IS_OBJECT (object));

	JSValueRef js_value = jsc_value_to_native(value);
	jsc_object_set_property_native (object, name, js_value, flags, error);
}

JSCValue *
jsc_object_get_property (JSCObject *object, 
                    const gchar *name, 
                    GError **error)
{
	JSValueRef js_value = jsc_object_get_property_native (object, name, error);
	return jsc_value_new_from_native (object->priv->context, js_value);
}


void
jsc_object_set_number_property (JSCObject *object, 
                            const gchar *name, 
                            gdouble value, 
                            JSCPropertyAttributeFlags flags,
                            GError **error)
{
	JSValueRef js_value = JSValueMakeNumber (CONTEXT (object), value);
	jsc_object_set_property_native (object, name, js_value, flags, error);
}

gdouble
jsc_object_get_number_property (JSCObject *object, 
                            const gchar *name,
                                GError **error)
{
	JSCValue *js_value = jsc_object_get_property (object, name, NULL);
	gdouble number = jsc_value_get_number (js_value, error);
	g_object_unref(js_value);
	return number;
}

void
jsc_object_set_string_property (JSCObject *object, 
                            const gchar *name, 
                            const gchar *value, 
                            JSCPropertyAttributeFlags flags,
                            GError **error)
{
	JSCValue *str_value = jsc_value_new_from_string (object->priv->context, value);
	jsc_object_set_property (object, name, str_value, flags, error);
	g_object_unref(str_value);
}

gchar *
jsc_object_get_string_property (JSCObject *object, 
                            const gchar *name,
                                GError **error)
{
	JSCValue *js_value = jsc_object_get_property (object, name, NULL);
	gchar *string = jsc_value_get_string (js_value, error);
	g_object_unref(js_value);
	return string;
}

