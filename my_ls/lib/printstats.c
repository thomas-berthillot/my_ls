/*
** EPITECH PROJECT, 2026
** Epitech my_ls
** File description:
** printstats.c
*/

#include <stdio.h>
#include <dirent.h>
#include "lib.h"
#include <stdlib.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>

static void printusers(struct passwd *pw, files_t *files, struct group *gr)
{
    if (pw != NULL) {
        my_putstr(pw->pw_name);
        my_putchar(' ');
    } else {
        my_putnbr(files->uid);
        my_putchar(' ');
    }
    if (gr != NULL) {
        my_putstr(gr->gr_name);
        my_putchar(' ');
    } else {
        my_putnbr(files->gid);
        my_putchar(' ');
    }
}

static void printsizes(int size, int space)
{
    int len = 0;
    int temp = size;

    if (temp == 0) {
        len = 1;
    } else {
        for (; temp > 0; len++)
            temp /= 10;
    }
    for (int i = 0; i < space - len; i++) {
        my_putchar(' ');
    }
    my_putnbr(size);
    my_putchar(' ');
}

void printstats(files_t *files, int count)
{
    struct passwd *pw = getpwuid(files->uid);
    struct group *gr = getgrgid(files->gid);

    printpermissions(files);
    my_putnbr(files->st_nlink);
    my_putchar(' ');
    printusers(pw, files, gr);
    printsizes(files->size, count);
    my_putchar(' ');
    printime(files->mtime);
    my_putstr(files->name);
    my_putchar('\n');
}
