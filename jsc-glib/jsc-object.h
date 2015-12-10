/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 4 -*-  */
/*
 * jsc-object.h
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

#ifndef _JSC_OBJECT_H_
#define _JSC_OBJECT_H_

#include <glib-object.h>
typedef struct _JSCValue JSCValue;

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

JSCContext *
jsc_object_get_context(JSCObject *object);


void
jsc_object_set_property (JSCObject *object, 
                         const gchar *name, 
                         JSCValue *value, 
                         JSCPropertyAttributeFlags flags,
                         GError **error);


JSCValue *
jsc_object_get_property (JSCObject *object, 
                    const gchar *name, 
                    GError **error);


void
jsc_object_set_number_property (JSCObject *object, 
                            const gchar *name, 
                            gdouble value, 
                            JSCPropertyAttributeFlags flags,
                            GError **error);

gdouble
jsc_object_get_number_property (JSCObject *object, 
                            const gchar *name,
                                GError **error);


void
jsc_object_set_string_property (JSCObject *object, 
                            const gchar *name, 
                            const gchar *value, 
                            JSCPropertyAttributeFlags flags,
                            GError **error);


gchar *
jsc_object_get_string_property (JSCObject *object, 
                            const gchar *name,
                                GError **error);

G_END_DECLS

#endif /* _JSC_OBJECT_H_ */

