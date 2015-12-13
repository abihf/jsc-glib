/* jsc-value.c
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

#ifndef _JSC_VALUE_H_
#define _JSC_VALUE_H_

#include <glib-object.h>
typedef struct _JSCObject JSCObject;

G_BEGIN_DECLS

/**
 * SECTION:jsc-value
 * @short_description: Class for storing javascript value
 * @title: JSCValue
 * @stability: Unstable
 * @include: jsc-glib.h
 *
 * This class hold JSValueRef and it's context
 */

#define JSC_TYPE_VALUE             (jsc_value_get_type ())
#define JSC_VALUE(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), JSC_TYPE_VALUE, JSCValue))
#define JSC_VALUE_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), JSC_TYPE_VALUE, JSCValueClass))
#define JSC_IS_VALUE(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), JSC_TYPE_VALUE))
#define JSC_IS_VALUE_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), JSC_TYPE_VALUE))
#define JSC_VALUE_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), JSC_TYPE_VALUE, JSCValueClass))

typedef struct _JSCValueClass JSCValueClass;
typedef struct _JSCValue JSCValue;
typedef struct _JSCValuePrivate JSCValuePrivate;

/**
 * JSCValueType:
 * @JSC_VALUE_TYPE_UNDEFINED  : value is undefined
 * @JSC_VALUE_TYPE_NULL       : value is null
 * @JSC_VALUE_TYPE_NUMBER     : value contains number.
 *                              Use #jsc_value_get_number to get it's content
 * @JSC_VALUE_TYPE_STRING     : value contains string
 *                              Use #jsc_value_get_string to get it's content
 * @JSC_VALUE_TYPE_OBJECT     : value contains
 *                              Use #jsc_value_get_object to get it's content
 *
 * type of value which #jsc_value_get_value_type returns
 */
typedef enum {
	JSC_VALUE_TYPE_UNDEFINED,    /*< nick=undefined >*/
	JSC_VALUE_TYPE_NULL,         /*< nick=null >*/
	JSC_VALUE_TYPE_BOOLEAN,      /*< nick=boolean >*/
	JSC_VALUE_TYPE_NUMBER,       /*< nick=number >*/
	JSC_VALUE_TYPE_STRING,       /*< nick=string >*/
	JSC_VALUE_TYPE_OBJECT        /*< nick=object >*/
} JSCValueType;


struct _JSCValueClass
{
  GObjectClass parent_class;
};

struct _JSCValue
{
  GObject parent_instance;
  JSCValuePrivate *priv;
};

GType jsc_value_get_type (void) G_GNUC_CONST;


//--- common

/**
 * jsc_value_get_context: (method)
 * @value: a #JSCValue
 *
 * Returns: (transfer none): a #JSContext where @value was created
 */
const JSCContext *
jsc_value_get_context (JSCValue *value);


/**
 * jsc_value_get_value_type: (method)
 * @value: a #JSCValue
 *
 * Returns: type of @value
 */
JSCValueType
jsc_value_get_value_type (JSCValue *value);


/**
 * jsc_value_equal: (method)
 * @value: a #JSCValue
 *
 * Returns: type of @value
 */
gboolean
jsc_value_equal (JSCValue *value_a,
                 JSCValue *value_b,
                 gboolean strict,
                 GError **error);



//--- UNDEFINED

JSCValue *
jsc_value_new_undefined(JSCContext *context);


gboolean
jsc_value_is_undefined(JSCValue *value);


//--- NULL

JSCValue *
jsc_value_new_null(JSCContext *context);


gboolean
jsc_value_is_null(JSCValue *value);



//--- BOOLEAN VALUE

JSCValue *
jsc_value_new_from_boolean(JSCContext *context, gboolean value);

gboolean
jsc_value_is_boolean(JSCValue *value);

gboolean
jsc_value_get_boolean(JSCValue *value, GError **error);



//--- NUMBER VALUE

JSCValue *
jsc_value_new_from_number(JSCContext *context, gdouble value);


gboolean
jsc_value_is_number(JSCValue *value);

gdouble
jsc_value_get_number(JSCValue *value, GError **error);



//--- STRING VALUE

/**
 * jsc_value_new_from_string: (constructor)
 * @ctx: a #JSCContext instance where value will be created
 * @value: string value
 *
 * Return: new #JSCValue containg string value
 */
JSCValue *
jsc_value_new_from_string(JSCContext *ctx,
                          const gchar *value);


/**
 * jsc_value_is_string: (method)
 * @js_value: a #JSCValue
 *
 * Return: return true if a #JSCValue is string
 */
gboolean
jsc_value_is_string(JSCValue *value);

/**
 * jsc_value_new_from_string: (method)
 * @js_value: a #JSCValue
 * @error: (nullable): string value
 *
 * Return: string value
 */
gchar *
jsc_value_get_string(JSCValue *js_value,
                     GError **error);




//--- OBJECT

gboolean
jsc_value_is_object(JSCValue *value);


JSCObject *
jsc_value_get_object(JSCValue *value, GError **error);




G_END_DECLS

#endif /* _JSC_VALUE_H_ */

