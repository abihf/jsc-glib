/* jsc-object.h
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

#ifndef _JSC_OBJECT_H_
#define _JSC_OBJECT_H_

#include <glib-object.h>

G_BEGIN_DECLS
/**
 * SECTION:jsc-object
 * @short_description: Class for storing javascript object
 * @title: JSCObject
 * @stability: Unstable
 * @include: jsc-glib.h
 *
 * This class hold JSObjectRef and it's context
 */


#define JSC_TYPE_OBJECT             (jsc_object_get_type ())
#define JSC_OBJECT(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), JSC_TYPE_OBJECT, JSCObject))
#define JSC_OBJECT_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), JSC_TYPE_OBJECT, JSCObjectClass))
#define JSC_IS_OBJECT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), JSC_TYPE_OBJECT))
#define JSC_IS_OBJECT_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), JSC_TYPE_OBJECT))
#define JSC_OBJECT_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), JSC_TYPE_OBJECT, JSCObjectClass))

typedef struct _JSCObjectClass JSCObjectClass;
typedef struct _JSCObject JSCObject;
typedef struct _JSCObjectPrivate JSCObjectPrivate;

/**
 * JSCPropertyAttributeFlags:
 * @JSC_PROPERTY_ATTRIBUTE_NONE: No flags.
 * @JSC_PROPERTY_ATTRIBUTE_RO: Property is read only.
 * @JSC_PROPERTY_ATTRIBUTE_NO_ENUM: Property is not enumerable.
 * @JSC_PROPERTY_ATTRIBUTE_NO_DELETE: Property is not deletable.
 *
 * Flags used when setting property of #JSCObject
 */
typedef enum {
  JSC_PROPERTY_ATTRIBUTE_NONE       = 0,        /*< nick=none >*/
  JSC_PROPERTY_ATTRIBUTE_RO         = (1 << 0), /*< nick=ro >*/
  JSC_PROPERTY_ATTRIBUTE_NO_ENUM    = (1 << 1), /*< nick=no-enum >*/
  JSC_PROPERTY_ATTRIBUTE_NO_DELETE  = (1 << 2)  /*< nick=no-delete >*/
} JSCPropertyAttributeFlags;



struct _JSCObjectClass
{
  GObjectClass parent_class;
};

struct _JSCObject
{
  GObject parent_instance;
  JSCObjectPrivate *priv;
};

GType jsc_object_get_type (void) G_GNUC_CONST;

/**
 * jsc_object_get_context: (member)
 * @object: a #JSCObject
 *
 * Returns: (transfer none): a #JSContext where @object was created
 */
const JSCContext *
jsc_object_get_context(JSCObject *object);


/**
 * jsc_object_to_value: (method)
 * @object: a #JSCObject
 *
 * convert @object to #JSCValue for being used other function such as
 *
 * Returns: (transfer none): a #JSCValue
 */
JSCValue *
jsc_object_to_value (JSCObject *object);

JSCValueType
jsc_object_get_property_type (JSCObject *object,
                              const gchar *name,
                              GError **error);

JSCValueType
jsc_object_get_property_type_at (JSCObject *object,
                                 guint index,
                                 GError **error);


void
jsc_object_set_property (JSCObject *object,
                         const gchar *name,
                         JSCValue *value,
                         JSCPropertyAttributeFlags flags,
                         GError **error);

void
jsc_object_set_property_at (JSCObject *object,
                            guint index,
                            JSCValue *value,
                            GError **error);


JSCValue *
jsc_object_get_property (JSCObject *object,
                         const gchar *name,
                         GError **error);

JSCValue *
jsc_object_get_property_at (JSCObject *object,
                            guint index,
                            GError **error);

// ---- undefined

void
jsc_object_set_undefined_property (JSCObject *object,
                                   const gchar *name,
                                   GError **error);

void
jsc_object_set_undefined_property_at (JSCObject *object,
                                      guint index,
                                      GError **error);



// ---- null

void
jsc_object_set_null_property (JSCObject *object,
                              const gchar *name,
                              GError **error);

void
jsc_object_set_null_property_at (JSCObject *object,
                                 guint index,
                                 GError **error);

// ---- boolean

/**
 * jsc_object_set_boolean_property: (method)
 * @object: a #JSCObject
 * @name: property name
 * @value: value to set
 * @flags: property flags
 * @error: (out): error object when exception raised
 *
 * Set property named @name of @object to @value.
 * This method will do something similar to @object[@name] = @value;
 */
void
jsc_object_set_boolean_property (JSCObject *object,
	const gchar *name,
        gboolean value,
        JSCPropertyAttributeFlags flags,
        GError **error);

/**
 * jsc_object_set_boolean_property_at: (method)
 * @object: a #JSCObject
 * @index: property index
 * @value: value to set
 * @error: (out): error object when exception raised
 *
 * Set property at index @index of @object to @value.
 * This method will do something similar to @object[@index] = @value;
 * 
 */
void
jsc_object_set_boolean_property_at (JSCObject *object,
	guint index,
        gboolean value,
        GError **error);

/**
 * jsc_object_get_boolean_property: (method)
 * @object: a #JSCObject
 * @name: property name
 * @error: (out): error object when exception raised
 *
 * Get property named @name of @object to @value.
 * 
 * Returns: value of @object[@name]
 */
gboolean
jsc_object_get_boolean_property (JSCObject *object,
	const gchar *name,
	GError **error);

/**
 * jsc_object_get_boolean_property_at: (method)
 * @object: a #JSCObject
 * @index: property index
 * @error: (out): error object when exception raised
 *
 * Get property at index @index of @object to @value.
 * 
 * Returns: value of @object[@index]
 */
gboolean
jsc_object_get_boolean_property_at (JSCObject *object,
	guint index,
	GError **error);




// ---- number

/**
 * jsc_object_set_number_property: (method)
 * @object: a #JSCObject
 * @name: property name
 * @value: value to set
 * @flags: property flags
 * @error: (out): error object when exception raised
 *
 * Set property named @name of @object to @value.
 * This method will do something similar to @object[@name] = @value;
 */
void
jsc_object_set_number_property (JSCObject *object,
	const gchar *name,
        gdouble value,
        JSCPropertyAttributeFlags flags,
        GError **error);

/**
 * jsc_object_set_number_property_at: (method)
 * @object: a #JSCObject
 * @index: property index
 * @value: value to set
 * @error: (out): error object when exception raised
 *
 * Set property at index @index of @object to @value.
 * This method will do something similar to @object[@index] = @value;
 * 
 */
void
jsc_object_set_number_property_at (JSCObject *object,
	guint index,
        gdouble value,
        GError **error);

/**
 * jsc_object_get_number_property: (method)
 * @object: a #JSCObject
 * @name: property name
 * @error: (out): error object when exception raised
 *
 * Get property named @name of @object to @value.
 * 
 * Returns: value of @object[@name]
 */
gdouble
jsc_object_get_number_property (JSCObject *object,
	const gchar *name,
	GError **error);

/**
 * jsc_object_get_number_property_at: (method)
 * @object: a #JSCObject
 * @index: property index
 * @error: (out): error object when exception raised
 *
 * Get property at index @index of @object to @value.
 * 
 * Returns: value of @object[@index]
 */
gdouble
jsc_object_get_number_property_at (JSCObject *object,
	guint index,
	GError **error);




// ---- string

/**
 * jsc_object_set_string_property: (method)
 * @object: a #JSCObject
 * @name: property name
 * @value: value to set
 * @flags: property flags
 * @error: (out): error object when exception raised
 *
 * Set property named @name of @object to @value.
 * This method will do something similar to @object[@name] = @value;
 */
void
jsc_object_set_string_property (JSCObject *object,
	const gchar *name,
        const gchar * value,
        JSCPropertyAttributeFlags flags,
        GError **error);

/**
 * jsc_object_set_string_property_at: (method)
 * @object: a #JSCObject
 * @index: property index
 * @value: value to set
 * @error: (out): error object when exception raised
 *
 * Set property at index @index of @object to @value.
 * This method will do something similar to @object[@index] = @value;
 * 
 */
void
jsc_object_set_string_property_at (JSCObject *object,
	guint index,
        const gchar * value,
        GError **error);

/**
 * jsc_object_get_string_property: (method)
 * @object: a #JSCObject
 * @name: property name
 * @error: (out): error object when exception raised
 *
 * Get property named @name of @object to @value.
 * 
 * Returns: value of @object[@name]
 */
gchar *
jsc_object_get_string_property (JSCObject *object,
	const gchar *name,
	GError **error);

/**
 * jsc_object_get_string_property_at: (method)
 * @object: a #JSCObject
 * @index: property index
 * @error: (out): error object when exception raised
 *
 * Get property at index @index of @object to @value.
 * 
 * Returns: value of @object[@index]
 */
gchar *
jsc_object_get_string_property_at (JSCObject *object,
	guint index,
	GError **error);




// ---- object

/**
 * jsc_object_set_object_property: (method)
 * @object: a #JSCObject
 * @name: property name
 * @value: value to set
 * @flags: property flags
 * @error: (out): error object when exception raised
 *
 * Set property named @name of @object to @value.
 * This method will do something similar to @object[@name] = @value;
 */
void
jsc_object_set_object_property (JSCObject *object,
	const gchar *name,
        JSCObject * value,
        JSCPropertyAttributeFlags flags,
        GError **error);

/**
 * jsc_object_set_object_property_at: (method)
 * @object: a #JSCObject
 * @index: property index
 * @value: value to set
 * @error: (out): error object when exception raised
 *
 * Set property at index @index of @object to @value.
 * This method will do something similar to @object[@index] = @value;
 * 
 */
void
jsc_object_set_object_property_at (JSCObject *object,
	guint index,
        JSCObject * value,
        GError **error);

/**
 * jsc_object_get_object_property: (method)
 * @object: a #JSCObject
 * @name: property name
 * @error: (out): error object when exception raised
 *
 * Get property named @name of @object to @value.
 * 
 * Returns: value of @object[@name]
 */
JSCObject *
jsc_object_get_object_property (JSCObject *object,
	const gchar *name,
	GError **error);

/**
 * jsc_object_get_object_property_at: (method)
 * @object: a #JSCObject
 * @index: property index
 * @error: (out): error object when exception raised
 *
 * Get property at index @index of @object to @value.
 * 
 * Returns: value of @object[@index]
 */
JSCObject *
jsc_object_get_object_property_at (JSCObject *object,
	guint index,
	GError **error);

G_END_DECLS

#endif /* _JSC_OBJECT_H_ */

