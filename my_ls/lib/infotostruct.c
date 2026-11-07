/*
** EPITECH PROJECT, 2026
** Epitech my_ls
** File description:
** infotostruct.c
*/

#include <sys/stat.h>
#include "lib.h"
#include <sys/sysmacros.h>

char *checkfiletype(struct stat *info)
{
    char *filetype;

    if (S_ISDIR(info->st_mode)) {
        filetype = "folder";
        return filetype;
    }
    if (S_ISREG(info->st_mode))
        filetype = "file";
    else if (S_ISLNK(info->st_mode))
        filetype = "symbolik link";
    else
        filetype = "other";
    return filetype;
}

void infotostruct(struct stat *info, char *name, files_t *files)
{
    files->name = name;
    files->size = info->st_size;
    files->inod = info->st_ino;
    files->st_nlink = info->st_nlink;
    files->st_blocks = info->st_blocks;
    files->uid = info->st_uid;
    files->gid = info->st_gid;
    if (S_ISCHR(info->st_mode) || S_ISBLK(info->st_mode)) {
        files->major = major(info->st_rdev);
        files->minor = minor(info->st_rdev);
    }
    files->type = checkfiletype(info);
}
