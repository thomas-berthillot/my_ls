#include <sys/stat.h>
#include "lib.h"

static void filetypemark(files_t *files, char *permissions)
{
    if (S_ISDIR(files->mode)) {
        permissions[0] = 'd';
    } else if (S_ISLNK(files->mode)) {
        permissions[0] = 'l';
    } else {
        permissions[0] = '-';
    }
}

static void userperm(mode_t mode, char *permissions)
{
    if (mode & S_IRUSR)
        permissions[1] = 'r';
    if (mode & S_IWUSR)
        permissions[2] = 'w';
    if (mode & S_IXUSR)
        permissions[3] = 'x';
}

static void grouperm(mode_t mode, char *permissions)
{
    if (mode & S_IRGRP)
        permissions[4] = 'r';
    if (mode & S_IWGRP)
        permissions[5] = 'w';
    if (mode & S_IXGRP)
        permissions[6] = 'x';
}

static void otherperm(mode_t mode, char *permissions)
{
    if (mode & S_IROTH)
        permissions[7] = 'r';
    if (mode & S_IWOTH)
        permissions[8] = 'w';
    if (mode & S_IXOTH)
        permissions[9] = 'x';
}

void printpermissions(files_t *files)
{
    char permissions[] = "----------";

    filetypemark(files, permissions);
    userperm(files->mode, permissions);
    grouperm(files->mode, permissions);
    otherperm(files->mode, permissions);
    my_putstr(permissions);
    my_putchar(' ');
}
