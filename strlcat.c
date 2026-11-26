/******************************************************************************
 *
 *    strlcat.c
 *
 *    New original implementation, added 2026 for this archive after the
 *    previous third-party strlcat source was omitted. This file is not
 *    derived from that source.
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published
 *    by the Free Software Foundation; either version 2.1 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but without any warranty whatsoever.
 *
 *****************************************************************************/

#include "str_lib.h"

size_t
strlcat(char *dst, const char *src, size_t siz)
{
	size_t dlen = 0;

	while (dlen < siz && dst[dlen] != '\0')
		dlen++;
	return dlen + strlcpy(dst + dlen, src, siz - dlen);
}
