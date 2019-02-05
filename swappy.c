#define _GNU_SOURCE

#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <dirent.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mount.h>


#define e(n,f) if (-1 == (f)) { perror(n); return 1; }
#define SRC "/glibc"

int main(int argc, char * const argv[])
{
    if (argc < 2)
    {
        // drop the rights suid gave us
        e("setuid", setreuid(getuid(), getuid()));
        e("setuid", setregid(getgid(), getgid()));

        printf("Usage: swappy program [args]\n");
        return 1;
    }

    // we remove ourselves from the parent's mount.
    e("unshare", unshare(CLONE_NEWNS));

    unsigned long flags = MS_BIND | MS_NOATIME | MS_NOSUID;

    e("mount", mount(SRC "/usr",  "/usr", NULL, flags, NULL));

    // drop the rights suid gave us
    e("setuid", setreuid(getuid(), getuid()));
    e("setuid", setregid(getgid(), getgid()));

    const char *prog = argv[1];
    e("exec", execvp(prog, ++argv));
}
