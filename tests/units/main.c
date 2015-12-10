/*
 * main.c
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

#define ADD_TEST(name, func) \
g_test_add (name, TestFixture, name, \
fixture_set_up, func, fixture_tear_down)

static void
fixture_set_up (TestFixture *fixture,
                gconstpointer user_data)
{
	fixture->context = jsc_context_new();

}

static void
fixture_tear_down (TestFixture *fixture,
                   gconstpointer user_data)
{
	//g_clear_object (fixture->context);
}

void
test_context_evaluate(TestFixture *fixture, gconstpointer data);

int
main (int argc, char *argv[])
{
	//setlocale (LC_ALL, "");

	g_test_init (&argc, &argv, NULL);
	g_test_bug_base ("http://github.com/abihf/issues");

	ADD_TEST ("/context/evaluate", test_context_evaluate);

	// Define the tests.
	/*g_test_add ("/my-object/test1", MyObjectFixture, "some-user-data",
	            my_object_fixture_set_up, test_my_object_test1,
	            my_object_fixture_tear_down);
	g_test_add ("/my-object/test2", MyObjectFixture, "some-user-data",
	            my_object_fixture_set_up, test_my_object_test2,
	            my_object_fixture_tear_down);*/

	return g_test_run ();
}