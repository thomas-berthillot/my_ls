/*
** EPITECH PROJECT, 2026
** Epitech my_ls
** File description:
** addnode.c
*/

#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include "lib.h"
#include <sys/sysmacros.h>
#include <stdlib.h>

char *my_strdup(char *str)
{
    int len;
    char *strdup;

    for (len = 0; str[len] != '\0'; len++);
    strdup = malloc(sizeof(char) * (len + 1));
    for (int i = 0; str[i] != '\0'; i++) {
        strdup[i] = str[i];
    }
    strdup[len + 1] = '\0';
    return strdup;
}

void copy(struct stat *info, files_t *new, char *name, int flagd)
{
    new->name = my_strdup(name);
    new->size = info->st_size;
    new->inod = info->st_ino;
    new->st_nlink = info->st_nlink;
    new->st_blocks = info->st_blocks;
    new->uid = info->st_uid;
    new->gid = info->st_gid;
    new->mode = info->st_mode;
    new->mtime = info->st_mtime;
    new->flagd = flagd;
    if (S_ISCHR(info->st_mode) || S_ISBLK(info->st_mode)) {
        new->major = major(info->st_rdev);
        new->minor = minor(info->st_rdev);
    }
    new->type = checkfiletype(info);
    new->next = NULL;
}

files_t *addnode(files_t *head, struct stat *info, char *name, int flagd)
{
    files_t *new = malloc(sizeof(files_t));
    files_t *tmp = head;

    copy(info, new, name, flagd);
    if (head == NULL)
        return new;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = new;
    return head;
}
