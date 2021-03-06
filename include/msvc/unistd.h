/* This file is part of the KDE project
   Copyright (C) 2003-2004 Jarosław Staniek <staniek@kde.org>

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

#ifndef NO_KDEWIN

#ifndef KDEWIN_UNISTD_H
#define KDEWIN_UNISTD_H

// include everywhere
#include <sys/types.h>

#include <direct.h>
#include <io.h> /* access(), etc.*/
#include <process.h> /* getpid(), etc.*/

/* include most headers here to avoid redefining gethostname() */
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/mman.h>

#include <winsock2.h>
#include "fixwinh.h"

#include <sys/stat.h>

#define environ _environ

#ifdef __cplusplus
extern "C" {
#endif

#define	F_OK	0
#define	R_OK	4
#define	W_OK	2
#define	X_OK	1 

#ifndef STDIN_FILENO
#define STDIN_FILENO 0
#endif

#ifndef STDOUT_FILENO
#define STDOUT_FILENO 1
#endif

#ifndef STDERR_FILENO
#define STDERR_FILENO 2
#endif

KDEWIN_EXPORT int chown(const char *__path, uid_t __owner, gid_t __group);

KDEWIN_EXPORT int fchown(int __fd, uid_t __owner, gid_t __group );

/* Get the real user ID of the calling process.  */
KDEWIN_EXPORT uid_t getuid (void);

/* Get the effective user ID of the calling process.  */
KDEWIN_EXPORT uid_t geteuid (void);

/* Get the real group ID of the calling process.  */
KDEWIN_EXPORT gid_t getgid (void);

/* Get the effective group ID of the calling process.  */
KDEWIN_EXPORT gid_t getegid (void);

KDEWIN_EXPORT int getgroups(int size, gid_t list[]);

/* On win32 we do not have fs-links, so simply 0 (success) is returned
   when __path is accessible. It is then just copied to __buf.
*/
KDEWIN_EXPORT int readlink(const char *__path, char *__buf, int __buflen);

/* just copies __name1 to __name2 */
KDEWIN_EXPORT int symlink(const char *__name1, const char *__name2);

/* just copies __name1 to __name2 */
KDEWIN_EXPORT int link(const char *__name1, const char *__name2);

KDEWIN_EXPORT int pipe(int *fd);

KDEWIN_EXPORT pid_t fork(void);

KDEWIN_EXPORT pid_t setsid(void);

#undef gethostname
#define gethostname kde_gethostname

KDEWIN_EXPORT int kde_gethostname(char *__name, size_t __len);

KDEWIN_EXPORT unsigned alarm(unsigned __secs ); 

KDEWIN_EXPORT char* getlogin();

KDEWIN_EXPORT int fsync (int fd);

KDEWIN_EXPORT int usleep(useconds_t useconds);

KDEWIN_EXPORT int sleep(unsigned int sec);

KDEWIN_EXPORT int setreuid(uid_t ruid, uid_t euid);

KDEWIN_EXPORT int mkstemps(char* _template, int suffix_len);

KDEWIN_EXPORT int initgroups(const char *name, int basegid);

// from kdecore/fakes.c

KDEWIN_EXPORT int seteuid(uid_t euid);

#ifndef _WIN32_WCE
KDEWIN_EXPORT int mkstemp (char* _template);
#endif

KDEWIN_EXPORT char* mkdtemp (char* _template);

KDEWIN_EXPORT int revoke(const char *tty);

KDEWIN_EXPORT long getpagesize(void);

KDEWIN_EXPORT int getopt(int argc, char **argv, const char *optstring);

extern KDEWIN_EXPORT char *optarg;

extern KDEWIN_EXPORT int optind, opterr;/*, optopt */

KDEWIN_EXPORT int truncate(const char *path, off_t length);

KDEWIN_EXPORT int ftruncate(int fd, off_t length);

#ifdef __cplusplus
}
#endif

#endif // KDEWIN_UNISTD_H
#endif /* NO_KDEWIN */