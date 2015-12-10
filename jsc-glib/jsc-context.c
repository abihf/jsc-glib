/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 4 -*-  */
/*
 * jsc-context.c
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

struct _JSCContextPrivate
{
   JSContextRef context;
	 gboolean is_global;
};



G_DEFINE_TYPE (JSCContext, jsc_context, G_TYPE_OBJECT);

static void
jsc_context_init (JSCContext *jsc_context)
{
  jsc_context->priv = G_TYPE_INSTANCE_GET_PRIVATE (jsc_context, JSC_TYPE_CONTEXT, JSCContextPrivate);
	jsc_context->priv->is_global = true;
	
  /* TODO: Add initialization code here */
}

static void
jsc_context_finalize (GObject *object)
{
  /* TODO: Add deinitalization code here */
	JSCContextPrivate *priv = JSC_CONTEXT(object)->priv;
	if (priv->is_global)
		JSGlobalContextRelease (priv->context);

  G_OBJECT_CLASS (jsc_context_parent_class)->finalize (object);
}

static void
jsc_context_class_init (JSCContextClass *klass)
{
  GObjectClass* object_class = G_OBJECT_CLASS (klass);

  g_type_class_add_private (klass, sizeof (JSCContextPrivate));

  object_class->finalize = jsc_context_finalize;
}

JSCContext *
jsc_context_new()
{
	JSCContext *context = JSC_CONTEXT (g_object_new (JSC_TYPE_CONTEXT, NULL));
	context->priv->context = JSGlobalContextCreate(NULL);
	context->priv->is_global = true;
	return context;
}

JSCContext *
jsc_context_new_from_native(gpointer *native_context)
{
	JSCContext *context = JSC_CONTEXT (g_object_new (JSC_TYPE_CONTEXT, NULL));
	context->priv->context = (JSContextRef) native_context;
	context->priv->is_global = false;
	return context;
}

JSContextRef 
jsc_context_to_native(JSCContext *context)
{
  return context->priv->context;
}


JSCObject *
jsc_context_get_global_object(JSCContext *context)
{
  JSObjectRef js_object = JSContextGetGlobalObject (context->priv->context);
  return jsc_object_new_from_native(context, js_object);
}


JSCValue *
jsc_context_evaluate_script(JSCContext *context,
                            const gchar *script,
                            GError **error)
{
	return jsc_context_evaluate_script_full (context, script, NULL, NULL, 0, error);
}

JSCValue *
jsc_context_evaluate_script_full(JSCContext *context,
                                 const gchar *script,
                                 JSCObject *this_object,
                                 const gchar *source_url,
                                 gint first_line_number, 
                                 GError **error)
{
	JSContextRef ctx = context->priv->context;
	JSStringRef js_script = JSStringCreateWithUTF8CString (script);
	JSObjectRef js_this = (this_object) ? jsc_object_to_native(this_object) : NULL;
	JSStringRef js_source_url = (source_url != NULL) ? 
		JSStringCreateWithUTF8CString (source_url) : NULL;
	JSValueRef exception = NULL;

	JSValueRef result = JSEvaluateScript (ctx, 
	                                      js_script, 
	                                      js_this, 
	                                      js_source_url, 
	                                      first_line_number, 
	                                      &exception);
	JSStringRelease (js_script);
	if (js_source_url)
		JSStringRelease (js_source_url);

	if (exception != NULL)
		jsc_error_set_from_exception (error, context, exception);

	return jsc_value_new_from_native (context, result);
}
