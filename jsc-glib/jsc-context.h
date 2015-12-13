/* jsc-context.h
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

#ifndef _JSC_CONTEXT_H_
#define _JSC_CONTEXT_H_

#include <glib-object.h>

typedef struct _JSCObject JSCObject;
typedef struct _JSCValue JSCValue;

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


GType jsc_context_get_type (void) G_GNUC_CONST;


JSCContext *
jsc_context_new();

JSCContext *
jsc_context_new_from_native (gpointer *native_context);

JSCObject *
jsc_context_get_global_object(JSCContext *context);

JSCValue *
jsc_context_evaluate_script(JSCContext *context,
                            const gchar *script,
                            GError **error);

JSCValue *
jsc_context_evaluate_script_full(JSCContext *context,
                                 const gchar *script,
                                 JSCObject *this_object,
                                 const gchar *source_url,
                                 gint first_line_number, 
                                 GError **error);


G_END_DECLS

#endif /* _JSC_CONTEXT_H_ */

