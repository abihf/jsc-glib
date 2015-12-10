/***************************************************************************
 *            jsc-error.h
 *
 *  Wed December 09 15:44:43 2015
 *  Copyright  2015  Abi Hafshin
 *  <user@host>
 ****************************************************************************/
/*
 * jsc-error.h
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

#ifndef _JSC_ERROR_H_
#define _JSC_ERROR_H_

#include <glib.h>

G_BEGIN_DECLS

#define JSC_ERROR jsc_error_quark()


GQuark       jsc_error_quark      (void);

typedef enum {
	JSC_ERROR_UNKNOWN,
	JSC_ERROR_INVALID_PROPERTY_VALUE,
	JSC_ERROR_PROPERTY_ERROR,
	JSC_ERROR_ARGUMENT_ERROR,
	JSC_ERROR_CONVERSION_ERROR,
	JSC_ERROR_TYPE_ERROR,
	JSC_ERROR_SYNTAX_ERROR,
	JSC_ERROR_PARSE_ERROR,
	JSC_ERROR_REFERENCE_ERROR
} JSCErrorEnum;


G_END_DECLS

#endif
