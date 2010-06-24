/*
   This file is part of the KDE libraries
   Copyright (C) 2003-2008 Jaroslaw Staniek <staniek@kde.org>

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
#include <tlhelp32.h>

#include <sys/types.h>
#include <errno.h>
#include <signal.h>

/* used in kill() */
int handle_kill_result(HANDLE h)
{
  if (GetLastError() == ERROR_ACCESS_DENIED)
    errno = EPERM;
  else if (GetLastError() == ERROR_NO_MORE_FILES)
    errno = ESRCH;
  else
    errno = EINVAL;
  CloseHandle(h);
  return -1;
}

KDEWIN_EXPORT int kill(pid_t pid, int sig)
{
  HANDLE h;
  HANDLE h_thread;
  DWORD thread_id;
  PROCESSENTRY32 pe32;
  if (pid <= 0 || sig < 0) {
    errno = EINVAL;
    return -1;
  }
  if (sig == 0) { /* we just wanted to know if the process exists  */
    h = CreateToolhelp32Snapshot(0, pid);
    if (h == INVALID_HANDLE_VALUE) {
      errno = ESRCH;
      return -1;
    }
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First( h, &pe32 ))
      return handle_kill_result(h);
// One is not supposed to use CloseHandle on that handle, says:
// http://msdn.microsoft.com/en-us/library/ms885189.aspx
#ifndef _WIN32_WCE
    CloseHandle(h);
#else
    CloseToolhelp32Snapshot(h);
#endif
    return 0;
  }
  h = OpenProcess(
    sig == 0 ? PROCESS_QUERY_INFORMATION|PROCESS_VM_READ : PROCESS_ALL_ACCESS, 
    FALSE, (DWORD)pid);
  if (!h) {
    CloseHandle(h);
    errno = ESRCH;
    return -1;
  }
  switch (sig) {
#ifndef _WIN32_WCE
  case SIGINT:
    if (!GenerateConsoleCtrlEvent(CTRL_C_EVENT, (DWORD)pid))
      return handle_kill_result(h);
    break;
  case SIGQUIT:
    if (!GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, (DWORD)pid))
      return handle_kill_result(h);
    break;
#endif
  case SIGKILL:
    if (!TerminateProcess(h, sig))
      return handle_kill_result(h);
    break;
#ifndef _WIN32_WCE
  default:
    h_thread = CreateRemoteThread(
      h, NULL, 0,
      (LPTHREAD_START_ROUTINE)(GetProcAddress(GetModuleHandleA("KERNEL32.DLL"), "ExitProcess")),
      0, 0, &thread_id);
    if (h_thread)
      WaitForSingleObject(h_thread, 5);
    else
      return handle_kill_result(h);
#endif
   }
#ifndef _WIN32_WCE
   CloseHandle(h);
#else
  CloseToolhelp32Snapshot(h);
#endif
  return 0;
}

KDEWIN_EXPORT pid_t waitpid(pid_t p, int *a, int b)
{
  HANDLE h = OpenProcess(PROCESS_TERMINATE, FALSE, (DWORD)p);
  if( h ) {
    DWORD dw;
    WaitForSingleObject(h,INFINITE);
    GetExitCodeProcess(h,&dw);
    CloseHandle(h);
    return 0;
  }
  errno = ECHILD;
  return -1;
}

KDEWIN_EXPORT sighandler_t kdewin32_signal(int signum, sighandler_t handler)
{
  if (signum==SIGABRT
#ifndef _WIN32_WCE
    || signum==SIGFPE
    || signum==SIGILL
    || signum==SIGINT
#endif
    || signum==SIGSEGV
#ifndef _WIN32_WCE
    || signum==SIGTERM)
#else
    )
#endif
    return signal(signum, handler);
  return SIG_ERR;
}
