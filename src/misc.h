/* createrepo_c - Library of routines for manipulation with repodata
 * Copyright (C) 2012  Tomas Mlcoch
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
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef __C_CREATEREPOLIB_MISC_H__
#define __C_CREATEREPOLIB_MISC_H__

#include <glib.h>
#include <curl/curl.h>
#include "constants.h"

#define UNUSED(x) (void)(x) // Used to suppress compiler warning about unused param


const char *flag_to_string(gint64 flags);

struct VersionStruct {
    char *epoch;
    char *version;
    char *release;
};

/*
 * BE CAREFULL! Returned structure had all strings malloced!!!
 * Be so kind and don't forget use free() for all its element, before end of structure lifecycle.
 */
struct VersionStruct string_to_version(const char *string, GStringChunk *chunk);

inline int is_primary(const char *filename);
char *compute_file_checksum(const char *filename, ChecksumType type);

struct HeaderRangeStruct {
    unsigned int start;
    unsigned int end;
};
struct HeaderRangeStruct get_header_byte_range(const char *filename);

const char *get_checksum_name_str(ChecksumType type);

char *get_filename(const char *filepath);


#define CR_COPY_OK              0
#define CR_COPY_ERR             1

void download(CURL *handle, const char *url, const char *in_dst, char **error);
int copy_file(const char *src, const char *dst);
int better_copy_file(const char *src, const char *dst);
int remove_dir(const char *path);

// return new allocated string with normalized path or NULL
char *normalize_dir_path(const char *path);

#endif /* __C_CREATEREPOLIB_MISC_H__ */
