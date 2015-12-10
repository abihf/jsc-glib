/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 4 -*-  */
/*
 * jsc-enums.h
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

#ifndef _JSC_ENUMS_H_
#define _JSC_ENUMS_H_

#include <glib-object.h>

G_BEGIN_DECLS


/**
 * JSCPropertyAttributeFlags:
 * @JSC_PROPERTY_ATTRIBUTE_NONE: No flags.
 * @JSC_PROPERTY_ATTRIBUTE_RO: Property is read only.
 * @JSC_PROPERTY_ATTRIBUTE_NO_ENUM: Property is not enumerable.
 * @JSC_PROPERTY_ATTRIBUTE_NO_DELETE: Property is not deletable.
 *
 * Flags used when setting property of #JSCObject
 */
typedef enum {
  JSC_PROPERTY_ATTRIBUTE_NONE       = 0,        /*< nick=none >*/
  JSC_PROPERTY_ATTRIBUTE_RO         = (1 << 0), /*< nick=ro >*/
  JSC_PROPERTY_ATTRIBUTE_NO_ENUM    = (1 << 1), /*< nick=no-enum >*/
  JSC_PROPERTY_ATTRIBUTE_NO_DELETE  = (1 << 2)  /*< nick=no-delete >*/
} JSCPropertyAttributeFlags;

typedef enum {
	JSC_VALUE_TYPE_UNDEFINED,
	JSC_VALUE_TYPE_NULL,
	JSC_VALUE_TYPE_BOOLEAN,
	JSC_VALUE_TYPE_NUMBER,
	JSC_VALUE_TYPE_STRING,
	JSC_VALUE_TYPE_OBJECT
} JSCValueType;

G_END_DECLS

#endif /* _JSC_ENUMS_H_ */

