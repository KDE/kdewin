/*
   This file is part of the KDE libraries
   Copyright (C) 2004 Jaroslaw Staniek <staniek@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include <kdewin_export.h>
#include <windows.h>

#include <direct.h>
#include <stdarg.h>
#include <sys/stat.h>

#include <kde_file_win.h>

/*if retval != 0 it must be freed */
char *customize_file_name(const char *file_name)
{
	char *fixed_file_name;
	int len = strlen(file_name);
	if ((len==2 || len==3) && file_name[1]==':' && isalpha(file_name[0])) {
		/* 1) */
		if (len==3)
			return 0;

		fixed_file_name=malloc(4);
		fixed_file_name[0]=file_name[0];
		fixed_file_name[1]=':';
		fixed_file_name[2]='\\';
		fixed_file_name[3]=0;
		return fixed_file_name;
	}
	if (len>1 && (file_name[len-1]=='\\' || file_name[len-1]=='/')) {
		/* 2) */
		fixed_file_name = strndup(file_name, len);
		fixed_file_name[len-1]=0;
		return fixed_file_name;
	}
	/*TODO "/" case? */
	return 0;
}


KDEWIN_EXPORT int kdewin32_stat(const char *file_name, struct stat *buf)
{
	char *fixed_file_name = customize_file_name(file_name);
	int result = stat(fixed_file_name?fixed_file_name:file_name, buf);
	free(fixed_file_name);
	/* be in sync with Qt4 */
	buf->st_uid = -2;
	buf->st_gid = -2;
	return result;
}

#ifdef _MSC_VER
KDEWIN_EXPORT int kdewin32_stat64(const char *file_name, struct _stat64 *buf)
{
	char *fixed_file_name = customize_file_name(file_name);
	int result = _stat64(fixed_file_name?fixed_file_name:file_name, buf);
	free(fixed_file_name);
	/* be in sync with Qt4 */
	buf->st_uid = -2;
	buf->st_gid = -2;
	return result;
}
#endif

KDEWIN_EXPORT int kdewin32_lstat(const char *file_name, struct stat *buf)
{
	return kdewin32_stat(file_name, buf);
}

/** @internal */
int kdewin32_fix_flags(int flags)
{
	if ((flags & O_TEXT) == 0 && (flags & O_BINARY) == 0)
		return flags | O_BINARY;
	return flags;
}

/*KDEWIN_EXPORT int kdewin32_open(const char *path, int flags)
{
	return open(path, kdewin32_fix_flags(flags));
}*/

KDEWIN_EXPORT int kdewin32_open(const char *path, int flags, ... /*mode_t mode*/)
{
	mode_t mode = 0;
	if (flags & O_CREAT) {
		va_list list;
		va_start(list, flags);
		mode = (mode_t)va_arg(list, int);
		va_end(list);
	}
	return open(path, kdewin32_fix_flags(flags), mode);
}

/** @internal */
int kdewin32_fix_mode_string(char *fixed_mode, const char *mode)
{
	if (strlen(mode)<1 || strlen(mode)>3)
		return 1;
	
	strncpy(fixed_mode, mode, 3);
	if (fixed_mode[0]=='b' || fixed_mode[1]=='b' || fixed_mode[0]=='t' || fixed_mode[1]=='t') {
		fixed_mode[strlen(mode)] = 0;
		return 0;
	}
	/* no 't' or 'b': append 'b' */
	if (fixed_mode[1]=='+') {
		fixed_mode[1]='b';
		fixed_mode[2]='+';
		fixed_mode[3]=0;
	}
	else {
		fixed_mode[1]='b';
		fixed_mode[2]=0;
	}
	return 0;
}

KDEWIN_EXPORT FILE *kdewin32_fopen(const char *path, const char *mode)
{
	char fixed_mode[4];
	if (0!=kdewin32_fix_mode_string(fixed_mode, mode))
		return 0;
	return fopen(path, fixed_mode);
}

KDEWIN_EXPORT FILE *kdewin32_fdopen(int fd, const char *mode)
{
	char fixed_mode[4];
	if (0!=kdewin32_fix_mode_string(fixed_mode, mode))
		return 0;
	return fdopen(fd, fixed_mode);
}

KDEWIN_EXPORT FILE *kdewin32_freopen(const char *path, const char *mode, FILE *stream)
{
	char fixed_mode[4];
	if (0!=kdewin32_fix_mode_string(fixed_mode, mode))
		return 0;
	return freopen(path, fixed_mode, stream);
}

KDEWIN_EXPORT int kdewin32_rename(const char *src, const char *dest)
{
	if (0==access(dest, 0/*exists*/)
		&& 0 != remove(dest))
		return -1;
	return rename(src, dest);
}

KDEWIN_EXPORT int kdewin32_mkdir(const char *path, mode_t mode)
{
#ifndef _WIN32_WCE
 	return mkdir(path);
#else
    return mkdir(path,0);
#endif
}
