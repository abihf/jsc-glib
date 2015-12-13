/* jsc-object.c
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

struct _JSCObjectPrivate
{
	 JSCContext *context;
	 JSObjectRef object;
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
	g_object_unref (G_OBJECT (JSC_OBJECT(object)->priv->context) );

	G_OBJECT_CLASS (jsc_object_parent_class)->finalize (object);
}

static void
jsc_object_class_init (JSCObjectClass *klass)
{
	GObjectClass* object_class = G_OBJECT_CLASS (klass);

	g_type_class_add_private (klass, sizeof (JSCObjectPrivate));

	object_class->finalize = jsc_object_finalize;
}

const JSCContext *
jsc_object_get_context(JSCObject *object)
{
	return object->priv->context;
}

JSCValue *
jsc_object_to_value (JSCObject *object)
{
	return (JSCValue *)object;
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
	g_object_ref (G_OBJECT(context));
	return object;
}

JSObjectRef
jsc_object_to_native (JSCObject *object)
{
	return object->priv->object;
}


static void
_set_prop (JSCObject *object,
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

static void
_set_prop_at (JSCObject *object,
              guint index,
              JSValueRef value,
              GError **error)
{
	g_return_if_fail (JSC_IS_OBJECT (object));

	JSContextRef context = CONTEXT (object);
	JSObjectRef js_object = TO_NATIVE (object);

	JSValueRef exception = NULL;
	JSObjectSetPropertyAtIndex (context, js_object, index, value, &exception);

	if (exception != NULL) {
		jsc_error_set_from_exception (error, object->priv->context, exception);
	}
}


static void
_get_prop(JSCObject *object,
          const gchar *name,
          ValueConverter converter,
          gpointer output,
          GError **error)
{
	JSContextRef context = CONTEXT (object);
	JSObjectRef js_object = TO_NATIVE (object);
	JSStringRef prop_name = JSStringCreateWithUTF8CString (name);
	JSValueRef js_value = JSObjectGetProperty (context, js_object, prop_name, NULL);
	JSStringRelease (prop_name);
	converter(object->priv->context, js_value, output, error);
}

static void
_get_prop_at (JSCObject *object,
              guint index,
              ValueConverter converter,
              gpointer output,
              GError **error)
{
	JSContextRef context = CONTEXT (object);
	JSObjectRef js_object = TO_NATIVE (object);
	JSValueRef js_value = JSObjectGetPropertyAtIndex (context, js_object, index, NULL);
	converter(object->priv->context, js_value, output, error);
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
	_set_prop (object, name, js_value, flags, error);
}

/**
 * LOL :D
 */
static void
_value_to_value(JSCContext *ctx,
                JSValueRef val,
                gpointer output,
                GError **error)
{
	*(JSValueRef *)output = val;
}

JSCValue *
jsc_object_get_property (JSCObject *object,
                         const gchar *name,
                         GError **error)
{
	JSValueRef js_value = NULL;
	_get_prop(object, name, _value_to_value, &js_value, error);
	if (*error == NULL)
		return jsc_value_new_from_native (object->priv->context, js_value);
	else
		return NULL;
}

// ----------------------------------------------------------------------------
//        GENERATED CODE
// ----------------------------------------------------------------------------


// ---- boolean

void
jsc_object_set_boolean_property (JSCObject *object,
                                 const gchar *name,
                                 gboolean value,
                                 JSCPropertyAttributeFlags flags,
                                 GError **error)
{
	_set_prop(object, name, JSValueMakeBoolean(CONTEXT (object), value), flags, error);
}

void
jsc_object_set_boolean_property_at (JSCObject *object,
                                    guint index,
                                    gboolean value,
                                    GError **error)
{
	_set_prop_at(object, index, JSValueMakeBoolean(CONTEXT (object), value), error);
}

gboolean
jsc_object_get_boolean_property (JSCObject *object,
                                 const gchar *name,
                                 GError **error)
{
	gboolean result;
	_get_prop (object, name, _value_to_boolean, &result, error);
	return result;
}

gboolean
jsc_object_get_boolean_property_at (JSCObject *object,
                                    guint index,
                                    GError **error)
{
	gboolean result;
	_get_prop_at (object, index, _value_to_boolean, &result, error);
	return result;
}




// ---- number

void
jsc_object_set_number_property (JSCObject *object,
                                const gchar *name,
                                gdouble value,
                                JSCPropertyAttributeFlags flags,
                                GError **error)
{
	_set_prop(object, name, JSValueMakeNumber(CONTEXT (object), value), flags, error);
}

void
jsc_object_set_number_property_at (JSCObject *object,
                                   guint index,
                                   gdouble value,
                                   GError **error)
{
	_set_prop_at(object, index, JSValueMakeNumber(CONTEXT (object), value), error);
}

gdouble
jsc_object_get_number_property (JSCObject *object,
                                const gchar *name,
                                GError **error)
{
	gdouble result;
	_get_prop (object, name, _value_to_number, &result, error);
	return result;
}

gdouble
jsc_object_get_number_property_at (JSCObject *object,
                                   guint index,
                                   GError **error)
{
	gdouble result;
	_get_prop_at (object, index, _value_to_number, &result, error);
	return result;
}




// ---- string

void
jsc_object_set_string_property (JSCObject *object,
                                const gchar *name,
                                const gchar * value,
                                JSCPropertyAttributeFlags flags,
                                GError **error)
{
	_set_prop(object, name, JSValueMakeStringUTF(CONTEXT (object), value), flags, error);
}

void
jsc_object_set_string_property_at (JSCObject *object,
                                   guint index,
                                   const gchar * value,
                                   GError **error)
{
	_set_prop_at(object, index, JSValueMakeStringUTF(CONTEXT (object), value), error);
}

gchar *
jsc_object_get_string_property (JSCObject *object,
                                const gchar *name,
                                GError **error)
{
	gchar * result;
	_get_prop (object, name, _value_to_string, &result, error);
	return result;
}

gchar *
jsc_object_get_string_property_at (JSCObject *object,
                                   guint index,
                                   GError **error)
{
	gchar * result;
	_get_prop_at (object, index, _value_to_string, &result, error);
	return result;
}




// ---- object

void
jsc_object_set_object_property (JSCObject *object,
                                const gchar *name,
                                JSCObject * value,
                                JSCPropertyAttributeFlags flags,
                                GError **error)
{
	_set_prop(object, name, JSValueMakeObject(CONTEXT (object), value), flags, error);
}

void
jsc_object_set_object_property_at (JSCObject *object,
                                   guint index,
                                   JSCObject * value,
                                   GError **error)
{
	_set_prop_at(object, index, JSValueMakeObject(CONTEXT (object), value), error);
}

JSCObject *
jsc_object_get_object_property (JSCObject *object,
                                const gchar *name,
                                GError **error)
{
	JSCObject * result;
	_get_prop (object, name, _value_to_object, &result, error);
	return result;
}

JSCObject *
jsc_object_get_object_property_at (JSCObject *object,
                                   guint index,
                                   GError **error)
{
	JSCObject * result;
	_get_prop_at (object, index, _value_to_object, &result, error);
	return result;
}



