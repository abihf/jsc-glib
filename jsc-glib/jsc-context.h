/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 4 -*-  */
/*
 * jsc-context.h
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

#ifndef _JSC_CONTEXT_H_
#define _JSC_CONTEXT_H_

#include <glib-object.h>

/**
 * JSCObject: (skip)
 */
typedef struct _JSCObject JSCObject;
/**
 * JSCValue: (skip)
 */
typedef struct _JSCValue JSCValue;

/**
 * SECTION:jsc-context
 * @short_description: JavaScriptCore runtime context
 * @title: JSCContext
 * @stability: Unstable
 * @include: jsc-glib.h
 *
 * This class hold JSContextRef
 */
G_BEGIN_DECLS


#define JSC_TYPE_CONTEXT             (jsc_context_get_type ())
#define JSC_CONTEXT(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), JSC_TYPE_CONTEXT, JSCContext))
#define JSC_CONTEXT_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), JSC_TYPE_CONTEXT, JSCContextClass))
#define JSC_IS_CONTEXT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), JSC_TYPE_CONTEXT))
#define JSC_IS_CONTEXT_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), JSC_TYPE_CONTEXT))
#define JSC_CONTEXT_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), JSC_TYPE_CONTEXT, JSCContextClass))

typedef struct _JSCContextClass JSCContextClass;
typedef struct _JSCContext JSCContext;
typedef struct _JSCContextPrivate JSCContextPrivate;


struct _JSCContextClass
{
  GObjectClass parent_class;
};

struct _JSCContext
{
  GObject parent_instance;
  JSCContextPrivate *priv;
};

GType jsc_context_get_type (void) G_GNUC_CONST;

/**
 * jsc_context_new: (constructor)
 * 
 * create new #JSCContext 
 * 
 * Returns: a #JSCContext
 */
JSCContext *
jsc_context_new();

/**
 * jsc_context_new_from_native: (constructor)
 * @native_context: JSContextRef or JSGlobalContextRef from JavaScriptCore
 * 
 * create new #JSCContext from JSContextRef 
 * 
 * Returns: a #JSCContext
 */
JSCContext *
jsc_context_new_from_native (gpointer *native_context);

/**
 * jsc_context_get_global_object: (method)
 * @context: a #JSCContext
 * 
 * get global object that associated to this context
 * 
 * Returns: global #JSCObject
 */
JSCObject *
jsc_context_get_global_object(JSCContext *context);

/**
 * jsc_context_evaluate_script: (method)
 * @context: a #JSCContext
 * @script: string contains javascript to be evaluted
 * @error: (nullable): set when evaluation throws exception
 * 
 * Evaluate javascript in this context. See #jsc_context_evaluate_script_full
 * 
 * Returns: result from evaluated script
 */
JSCValue *
jsc_context_evaluate_script(JSCContext *context,
                            const gchar *script,
                            GError **error);

/**
 * jsc_context_evaluate_script_full: (method)
 * @context: a #JSCContext
 * @script: string contains javascript to be evaluted
 * @this_object: (nullable): value of this. If NULL, use global object
 * @source_url: (nullable): source url used for error reporting
 * @first_line_number: base line number used for error reporting
 * @error: (nullable): set when evaluation throws exception
 * 
 * evaluate javascript in this context
 * 
 * Returns: result from evaluated script
 */
JSCValue *
jsc_context_evaluate_script_full(JSCContext *context,
                                 const gchar *script,
                                 JSCObject *this_object,
                                 const gchar *source_url,
                                 gint first_line_number, 
                                 GError **error);


G_END_DECLS

#endif /* _JSC_CONTEXT_H_ */

