/* jsc-error.h
 * 
 * This file is part of JSC-GLib
 * Copyright (C) 2015  Abi Hafshin
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 *
 * Author:
 *   Abi Hafshin    <abi@hafs.in>
 */



#ifndef _JSC_ERROR_H_
#define _JSC_ERROR_H_

#include <glib.h>

G_BEGIN_DECLS

/**
 * JSC_ERROR:
 * 
 * Error Quark for JSCError
 * 
 * See also: #jsc_error_quark
 */
#define JSC_ERROR jsc_error_quark()


GQuark       jsc_error_quark      (void);

/**
 * JSCError:
 * @JSC_ERROR_UNKNOWN: Unknown Error
 * @JSC_ERROR_INVALID_PROPERTY_VALUE: 
 * 
 * Error Quark for JSCError

 */
typedef enum
{
	JSC_ERROR_UNKNOWN,
	JSC_ERROR_INVALID_PROPERTY_VALUE,
	JSC_ERROR_PROPERTY_ERROR,
	JSC_ERROR_ARGUMENT_ERROR,
	JSC_ERROR_CONVERSION_ERROR,
	JSC_ERROR_TYPE_ERROR,
	JSC_ERROR_SYNTAX_ERROR,
	JSC_ERROR_PARSE_ERROR,
	JSC_ERROR_REFERENCE_ERROR,
	JSC_ERROR_ERROR_EXCEPTION    = 0xff
} JSCError;


G_END_DECLS

#endif

