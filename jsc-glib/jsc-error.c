/* jsc-error.c
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


/**
 * jsc_error_quark:
 *
 * Gets the JSCError Quark.
 *
 * Returns: a #GQuark.
 **/
G_DEFINE_QUARK (jsc-error-quark, jsc_error)


void 
jsc_error_set_from_exception(GError **error, 
                             JSCContext *context, 
                             JSValueRef exception)
{
	if (!error || *error || exception == NULL) return;
	JSContextRef ctx = jsc_context_to_native (context);
	JSCObject *error_object = jsc_object_new_from_native (context,
							      JSValueToObject (ctx, exception, NULL));
	gchar *name = jsc_object_get_string_property (error_object,
						      "name",
						      NULL);
	gchar *message = jsc_object_get_string_property (error_object,
							 "message", NULL);
	gint type = JSC_ERROR_UNKNOWN;
  	if (g_strcmp0 ("TypeError", name)) {
		type = JSC_ERROR_TYPE_ERROR;
	}
	// TODO: implement all error type

	g_set_error(error, JSC_ERROR, type, "%s: %s", name, message);
	g_free (name);
  	g_free (message);
}
