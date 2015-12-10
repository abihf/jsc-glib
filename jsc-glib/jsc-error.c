/***************************************************************************
 *            jsc-error.c
 *
 *  Wed December 09 15:44:43 2015
 *  Copyright  2015  Abi Hafshin
 *  <user@host>
 ****************************************************************************/
/*
 * jsc-error.c
 *
 * Copyright (C) 2015 - Abi Hafshin
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
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
	if (!error || *error) return;
	JSContextRef ctx = jsc_context_to_native (context);
	JSCObject *error_object = jsc_object_new_from_native (context, JSValueToObject (ctx, exception, NULL));
	gchar *message = jsc_object_get_string_property (error_object, "message", NULL);
	g_set_error_literal(error, JSC_ERROR, JSC_ERROR_UNKNOWN, message);
	g_free(message);
}