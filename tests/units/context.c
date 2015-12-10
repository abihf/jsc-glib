/*
 * context.c
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

#include "shared.h"


void
test_context_evaluate(TestFixture *fixture, gconstpointer data)
{
	JSCContext *context = fixture->context;
	
	GError *error = NULL;
	JSCValue *result = jsc_context_evaluate_script(context, "1+2", &error);
	g_assert_cmpfloat(jsc_value_get_number(result, NULL), ==, 3.0);
	g_assert_no_error(error);
}
