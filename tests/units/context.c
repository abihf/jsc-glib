/* context.c
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



#include "shared.h"


void
test_context_evaluate(TestFixture *fixture, gconstpointer data)
{
	JSCContext *context = fixture->context;
	
	GError *error = NULL;
	JSCValue *result = jsc_context_evaluate_script(context, "1 + 2", &error);
	g_assert_no_error(error);
	g_assert_cmpfloat(jsc_value_get_number(result, NULL), ==, 3.0);
}

void
test_context_global_object(TestFixture *fixture, gconstpointer data)
{
	JSCContext *context = fixture->context;
	
	GError *error = NULL;
	JSCValue *result = jsc_context_evaluate_script(context, "var TEST = 100;", &error);
	g_assert_no_error(error);

	JSCObject *global = jsc_context_get_global_object (context);
	g_assert_nonnull (global);
	
	double test_var = jsc_object_get_number_property (global, "TEST", &error);
	g_assert_no_error(error);

	g_assert_cmpfloat (test_var, ==, 100);
	g_object_unref (global);
}
