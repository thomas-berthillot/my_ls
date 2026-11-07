#include <stdio.h>
#include <dirent.h>
#include "lib.h"
#include <stdlib.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>

int getbiggest(files_t *files)
{
    int biggest = 0;
    int actual = 0;
    int count;

    while (files != NULL) {
        actual = files->size;
        if (actual > biggest)
            biggest = actual;
        files = files->next;
    }
    for (count = 0; biggest > 0; count++) {
        biggest = biggest / 10;
    }
    return count;
}

int calculatetotal(files_t *files, t_options_t *options)
{
    int count = 0;

    while (files != NULL) {
        if (files->name[0] == '.' && options->a == 0 && files->flagd == 0) {
            files = files->next;
            continue;
        }
        count += files->st_blocks;
        files = files->next;
    }
    return count / 2;
}

static void printname(files_t *files)
{
    my_putstr(files->name);
    my_putchar(' ');
    my_putchar(' ');
}

static void printotal(int cont, files_t *files)
{
    if (files->next != NULL || S_ISDIR(files->mode)) {
        my_putstr("total ");
        my_putnbr(cont);
        my_putchar('\n');
    }
}

int executeflags(t_options_t *options, files_t *files)
{
    if (options->t == 1)
        sort_files_time(files);
    if (files == NULL)
        return 84;
    if (options->l == 1 && options->d == 0)
        printotal(calculatetotal(files, options), files);
    while (files != NULL) {
        if (files->name[0] == '.' && options->a == 0 && files->flagd == 0) {
            files = files->next;
            continue;
        }
        if (options->l == 1) {
            printstats(files, getbiggest(files));
        } else {
            printname(files);
            my_putchar('\n');
        }
        files = files->next;
    }
    return 0;
}
