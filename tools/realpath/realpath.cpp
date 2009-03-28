#ifdef _MSC_VER
#include <msvc/stdlib.h>
#else
#include <mingw/stdlib.h>
#endif
#include <stdio.h>
#include <windows.h>

char *realpath(const char *path,char *resolved_path)
{
    int i;
    // no error checking... :(
    resolved_path[0] = '\0';
    GetFullPathNameA(path, MAX_PATH, resolved_path, NULL);
    fprintf(stderr, "ret1: %s\n", resolved_path);
    for( i = 0; resolved_path[i] != '\0'; ++i ) {
        if(resolved_path[i] == '\\')
            resolved_path[i] = '/';
    }
    fprintf(stderr, "ret2: %s\n", resolved_path);
    return resolved_path;
}

int main(int argc, char** argv)
{
    char buf[500];
    char *out;
    out = realpath("c:/blib/../windows/test.txt", buf);
    fprintf(stderr, "out: %s\n", buf);
    GetFullPathName("c:\\blib/../windows/test.txt", 500, buf, NULL);
    fprintf(stderr, "out: %s\n", buf);
    int ret = GetFullPathName("../windows/test.txt", 0, buf, NULL);
    fprintf(stderr, "ret: %d\n", ret);
    GetFullPathName("../windows/test.txt", 500, buf, NULL);
    fprintf(stderr, "out: %s\n", buf);
}
