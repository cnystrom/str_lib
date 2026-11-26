/******************************************************************************
 *
 *    str_lib.h
 *
 *    Copyright (C) 2002, 2005  Chris Nystrom
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU Lessor General Public License as published
 *    by the Free Software Foundation; either version 2.1 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but without any warranty whatsoever.
 *
 *    For more license information see:
 *
 *      http://www.gnu.org/copyleft/lessor.html
 *
 *    Contact Author at:
 *
 *    Chris Nystrom
 *
 *    E-Mail: cnystrom@gmail.com
 *
 *    Soli Deo Gloria
 *
 */

#ifndef _STR_LIB_H
#define _STR_LIB_H

#ifdef WIN32
#include <stddef.h>
#endif				/*  */

#ifndef _SYS_TYPES_H
#include <sys/types.h>
#endif				/*  */

#ifndef PRIVATE
#define PRIVATE static
#endif				/*  */

#ifndef PUBLIC
#define PUBLIC
#endif				/*  */

PUBLIC void strclean(char *s);
PUBLIC char *str_null_terminated(char *s, int num);
PUBLIC int str_len(char *s);

// From OpenBSD 
PUBLIC size_t strlcpy(char *dst, const char *src, size_t siz);
PUBLIC size_t strlcat(char *dst, const char *src, size_t siz);

#endif				// _STR_LIB_H
