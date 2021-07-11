/* This file is part of the KDE project
   Copyright (C) 2003-2004 Jaroslaw Staniek <staniek@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#define _WIN32_WINNT 0x0500
#include <kdewin_export.h>
#include <windows.h>

#include <direct.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

/* BEGIN stat.c */
KDEWIN_EXPORT int lstat(const char *path, struct stat *sb)
{
  return _stat(path,(struct _stat*)sb);
}

KDEWIN_EXPORT int fchmod(int __fd, mode_t __mode)
{
  return 0;
}
/* END stat.c */

KDEWIN_EXPORT int getgroups(int size, gid_t list[])
{
    /* TODO */
    return 0;
}

KDEWIN_EXPORT int readlink(const char *__path, char *__buf, int __buflen)
{
    if (!__path) {
      errno = EINVAL;
      return -1;
    }
    if ( (__buflen < 0) || ((int)strlen(__path)>(__buflen-1)) )
    {
      errno = ENAMETOOLONG;
      return -1;
    }
    if (access(__path, R_OK) == 0) {
      /* ok, copy to buf */
      strncpy(__buf,__path,__buflen);
      errno = 0;
      return 0;
    }
    errno = ENOENT;
    return -1;
}

KDEWIN_EXPORT int symlink(const char *__name1, const char *__name2)
{
#ifdef _WIN32_WCE
    const wchar_t * w__name1 = wce_mbtowc(__name1);
    const wchar_t * w__name2 = wce_mbtowc(__name2);
    if(!CopyFileW(w__name1, w__name2, FALSE)) {
#else
  if(!CopyFileA(__name1, __name2, FALSE)) {
#endif
        switch(GetLastError()) {
            case ERROR_FILE_EXISTS:
                errno = EEXIST;
                break;
            case ERROR_CANNOT_MAKE:
                errno = EACCES;
                break;
            default:
                errno = EFAULT;
                break;
        }
        return -1; 
    }
#ifdef _WIN32_WCE
    free(w__name1);
    free(w__name2);
#endif
    return 0;
}

KDEWIN_EXPORT int link(const char *__name1, const char *__name2)
{
    return symlink(__name1, __name2);
}

KDEWIN_EXPORT int chown(const char *__path, uid_t __owner, gid_t __group)
{ 
  return 0; 
}

KDEWIN_EXPORT int fchown(int __fd, uid_t __owner, gid_t __group )
{
  return 0; 
}

/* Get the real user ID of the calling process.  */
KDEWIN_EXPORT uid_t getuid()
{
  return -2;    /* keep in sync with Qt! */
}

/* Get the effective user ID of the calling process.  */
KDEWIN_EXPORT uid_t geteuid (void)
{
  return -2;    /* keep in sync with Qt! */
}

/* Get the real group ID of the calling process.  */
KDEWIN_EXPORT gid_t getgid (void)
{
  return -2;    /* keep in sync with Qt! */
}

/* Get the effective group ID of the calling process.  */
KDEWIN_EXPORT gid_t getegid (void)
{
  return -2;    /* keep in sync with Qt! */
}

KDEWIN_EXPORT int pipe(int *fd)
{
  /** @todo */
  /*FIXME: wince does not have pipes */
#ifndef _WIN32_WCE
  return _pipe( fd, 256, O_BINARY ); /* OK? */
#else
  return -1;
#endif
}

#ifndef KDEWIN_HAVE_FORK
KDEWIN_EXPORT pid_t fork(void)
{
  /** @todo */
  return -1;
}
#endif

KDEWIN_EXPORT pid_t setsid(void)
{
  /** @todo */
  return -1;
}

KDEWIN_EXPORT unsigned alarm(unsigned __secs )
{
  /** @todo */
  return 1;
}

/*#define INCL_WINSOCK_API_PROTOTYPES 0
#include <winsock2.h>*/

/* using winsock gethostname(), which would be taken normally requires WSAStartup called before  */
/* which will not be done in every case */
/*http://msdn.microsoft.com/library/default.asp?url=/library/en-us/winsock/winsock/gethostname_2.asp */

KDEWIN_EXPORT int kde_gethostname(char *__name, size_t __len)
{
#ifndef _WIN32_WCE
  DWORD len = __len;
  if (0==GetComputerNameA(__name, &len))
    return -1;
#else
  const wchar_t dir[] = L"Ident";
  const wchar_t name[] = L"Name";
  HKEY root_key;
  HKEY key_handle;
  DWORD nbytes;
  DWORD n1;
  DWORD type;
  wchar_t *wres = NULL;
  char *res = NULL;

  root_key = HKEY_LOCAL_MACHINE;
  if (RegOpenKeyExW (root_key, dir, 0, KEY_READ, &key_handle))
    return -1;

  if (RegQueryValueExW (key_handle, name, 0, &type, NULL, &nbytes))
    {
      RegCloseKey (key_handle);
      return -1;
    }
  n1 = ((nbytes + sizeof(wchar_t) - 1) / sizeof (wchar_t)) + 1;
  nbytes = n1 * sizeof (wchar_t);
  wres = malloc (nbytes);
  if (!wres)
    {
      RegCloseKey (key_handle);
      return -1;
    }
  if (RegQueryValueExW (key_handle, name, 0, &type, wres, &nbytes))
    {
      RegCloseKey (key_handle);
      free (wres);
      return -1;
    }
  RegCloseKey (key_handle);
  wres[n1 - 1] = 0;

  res = wce_wctomb(wres);
  strncpy(__name,res,__len);
  free(res);
  free (wres);
#endif
    return 0;
}

#define getlogin_buf_size 255
char getlogin_buf[getlogin_buf_size+1];

KDEWIN_EXPORT char* getlogin()
{
/*! @todo make this reentrant!*/
/*FIXME: wince does not have users */
    size_t size = sizeof(getlogin_buf);
    *getlogin_buf = 0;
#ifndef _WIN32_WCE
    if (!GetUserNameA(getlogin_buf, (LPDWORD)&size))
        return 0;
#endif
    return getlogin_buf;
}

#ifndef KDEWIN_HAVE_USLEEP
KDEWIN_EXPORT int usleep(unsigned int usec)
{
    Sleep(usec/1000);
    return 0;
}
#endif

#ifndef KDEWIN_HAVE_SLEEP
KDEWIN_EXPORT int sleep(unsigned int sec)
{
    Sleep(sec*1000);
    return 0;
}
#endif

KDEWIN_EXPORT int setreuid(uid_t ruid, uid_t euid)
{
    /*! @todo */
    return 0;
}


/* this is based on code taken from the GNU libc, distributed under the LGPL license */

/* Generate a unique temporary file name from TEMPLATE.

   TEMPLATE has the form:

   <path>/ccXXXXXX<suffix>

   SUFFIX_LEN tells us how long <suffix> is (it can be zero length).

   The last six characters of TEMPLATE before <suffix> must be "XXXXXX";
   they are replaced with a string that makes the filename unique.

   Returns a file descriptor open on the file for reading and writing.  */

KDEWIN_EXPORT int mkstemps (char* _template, int suffix_len)
{
  static const char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  char *XXXXXX;
  int len;
  int count;
  int value;

  len = strlen (_template);

  if ((int) len < 6 + suffix_len || strncmp (&_template[len - 6 - suffix_len], "XXXXXX", 6))
      return -1;

  XXXXXX = &_template[len - 6 - suffix_len];

  value = rand();
  for (count = 0; count < 256; ++count)
  {
      int v = value;
      int fd;

      /* Fill in the random bits.  */
      XXXXXX[0] = letters[v % 62];
      v /= 62;
      XXXXXX[1] = letters[v % 62];
      v /= 62;
      XXXXXX[2] = letters[v % 62];
      v /= 62;
      XXXXXX[3] = letters[v % 62];
      v /= 62;
      XXXXXX[4] = letters[v % 62];
      v /= 62;
      XXXXXX[5] = letters[v % 62];

      fd = open (_template, O_RDWR|O_CREAT|O_EXCL, 0600);
      if (fd >= 0)
        /* The file does not exist.  */
        return fd;

      /* This is a random value.  It is only necessary that the next
     TMP_MAX values generated by adding 7777 to VALUE are different
     with (module 2^32).  */
      value += 7777;
    }
  /* We return the null string if we can't find a unique file name.  */
  _template[0] = '\0';
  return -1;
}

#ifndef _WIN32_WCE
/* from kdecore/fakes.c */
KDEWIN_EXPORT int mkstemp (char* _template)
{
  return mkstemps( _template, 0 );
}
#endif

/* from kdecore/fakes.c */
int seteuid(uid_t euid)
{
    return setreuid(-1, euid); /* Well, if you have neither you are in trouble :) */
}

/* from kdecore/fakes.c */
/* Generate a unique temporary directory name from TEMPLATE.

   TEMPLATE has the form:

   <path>/ccXXXXXX


   The last six characters of TEMPLATE must be "XXXXXX";
   they are replaced with a string that makes the filename unique.

   Returns a file descriptor open on the file for reading and writing.  */

KDEWIN_EXPORT char* mkdtemp (char* _template)
{
  static const char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  char *XXXXXX;
  int len;
  int count;
  int value;

  len = strlen (_template);

  if ((int) len < 6 || strncmp (&_template[len - 6], "XXXXXX", 6))
      return 0;

  XXXXXX = &_template[len - 6];

  value = rand();
  for (count = 0; count < 256; ++count)
  {
      int v = value;

      /* Fill in the random bits.  */
      XXXXXX[0] = letters[v % 62];
      v /= 62;
      XXXXXX[1] = letters[v % 62];
      v /= 62;
      XXXXXX[2] = letters[v % 62];
      v /= 62;
      XXXXXX[3] = letters[v % 62];
      v /= 62;
      XXXXXX[4] = letters[v % 62];
      v /= 62;
      XXXXXX[5] = letters[v % 62];

      /* This is a random value.  It is only necessary that the next
     TMP_MAX values generated by adding 7777 to VALUE are different
     with (module 2^32).  */
      value += 7777;

      if (!mkdir(_template))
        return _template;    
    }
    return 0;
}

KDEWIN_EXPORT int revoke(const char *tty)
{
        errno = ENOTSUP;
        return -1;
}

/* getpagesize for windows */
/*static  */
KDEWIN_EXPORT long getpagesize (void)
{
    static long g_pagesize = 0;
    if (! g_pagesize) {
        SYSTEM_INFO system_info;
        GetSystemInfo (&system_info);
        g_pagesize = system_info.dwPageSize;
    }
    return g_pagesize;
}

#ifndef __MINGW32__
/* XGetopt.cpp  Version 1.2 */
/* */
/* Author:  Hans Dietrich */
/*          hdietrich2@hotmail.com */
/* */
/* Description: */
/*     XGetopt.cpp implements getopt(), a function to parse command lines. */
/* */
/* History */
/*     Version 1.2 - 2003 May 17 */
/*     - Added Unicode support */
/* */
/*     Version 1.1 - 2002 March 10 */
/*     - Added example to XGetopt.cpp module header  */
/* */
/* This software is released into the public domain. */
/* You are free to use it in any way you like. */
/* */
/* This software is provided "as is" with no expressed */
/* or implied warranty.  I accept no liability for any */
/* damage or loss of business that this software may cause. */
/* */
/* CE: from http://www.codeproject.com/cpp/xgetopt.asp */
/*     removed unicode support to compile with mingw */
char *optarg = NULL;    /* global argument pointer */
int   optind = 0;     /* global argv index */
int   opterr = 0;     

KDEWIN_EXPORT int getopt(int argc, char **argv, const char *optstring)
{
    static char *next = NULL;
    char c = '?';
    char *cp = NULL;
    if (optind == 0)
        next = NULL;

    optarg = NULL;

    if (next == NULL || *next == '\0')
    {
        if (optind == 0)
            optind++;

        if (optind >= argc || argv[optind][0] != '-' || argv[optind][1] == '\0')
        {
            optarg = NULL;
            if (optind < argc)
                optarg = argv[optind];
            return -1;
        }

        if (strcmp(argv[optind], "--") == 0)
        {
            optind++;
            optarg = NULL;
            if (optind < argc)
                optarg = argv[optind];
            return -1;
        }

        next = argv[optind];
        next++;        /* skip past - */
        optind++;
    }

    c = *next++;
    cp = strchr(optstring, c);

    if (cp == NULL || c == ':')
        return '?';

    cp++;
    if (*cp == ':')
    {
        if (*next != '\0')
        {
            optarg = next;
            next = NULL;
        }
        else if (optind < argc)
        {
            optarg = argv[optind];
            optind++;
        }
        else
        {
            return '?';
        }
    }

    return c;
}
#endif  /* __MINGW32__ */

#ifndef KDEWIN_HAVE_TRUNCATE
int truncate(const char *path, off_t length)
{
    
#ifndef _WIN32_WCE
    HANDLE hFile;
    LARGE_INTEGER fileSize;
#endif
    OutputDebugString(TEXT("ERROR broken function truncate from kdewin!"));    
#ifndef _WIN32_WCE

    if( length < 0 )
    {
        errno = EINVAL;
        return -1;
    }

    hFile = CreateFileA( path, GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );

    if( hFile == INVALID_HANDLE_VALUE )
    {
        DWORD dwLastErr = GetLastError();
        errno = EACCES;
        return -1;
    }

    if( GetFileSizeEx( hFile, &fileSize ) == 0 )
    {
        DWORD dwLastErr = GetLastError();
        CloseHandle( hFile );
        errno = EACCES;
        return -1;
    }

    if( fileSize.QuadPart < length)
    {
        CloseHandle( hFile );
        errno = EINVAL;
        return -1;
    }

    fileSize.QuadPart = length;

    if( SetFilePointerEx( hFile, fileSize, 0, FILE_BEGIN ) == 0 )
    {
        DWORD dwLastErr = GetLastError();
        CloseHandle( hFile );
        errno = EACCES;
        return -1;
    }

    CloseHandle( hFile );
#endif
    return 0;
}
#endif

#ifndef __MINGW32__
/* TODO (js) consider using _chsize_s */
int ftruncate(int fd, off_t length)
{    
#ifndef _WIN32_WCE
  return _chsize (fd, length);
#else
  OutputDebugString(TEXT("ERROR not implemented function ftruncate from kdewin!"));
  return 0;
#endif
}
#endif  /* __MINGW32__ */

