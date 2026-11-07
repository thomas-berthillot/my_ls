#include "lib.h"
#include <stdlib.h>
#include <time.h>

static void swapthisa(files_t *a, files_t *b)
{
    time_t tmp_mtime = a->mtime;
    char *tmp_name = a->name;
    int tmp_size = a->size;
    mode_t tmp_mode = a->mode;
    ino_t tmp_inod = a->inod;

    a->mtime = b->mtime;
    a->name = b->name;
    a->size = b->size;
    a->mode = b->mode;
    a->inod = b->inod;
    b->mtime = tmp_mtime;
    b->name = tmp_name;
    b->size = tmp_size;
    b->mode = tmp_mode;
    b->inod = tmp_inod;
}

static void swapthisb(files_t *a, files_t *b)
{
    nlink_t tmp_nlink = a->st_nlink;
    uid_t tmp_uid = a->uid;
    gid_t tmp_gid = a->gid;
    int tmp_flagd = a->flagd;
    char *tmp_type = a->type;

    a->st_nlink = b->st_nlink;
    a->uid = b->uid;
    a->gid = b->gid;
    a->flagd = b->flagd;
    a->type = b->type;
    b->st_nlink = tmp_nlink;
    b->uid = tmp_uid;
    b->gid = tmp_gid;
    b->flagd = tmp_flagd;
    b->type = tmp_type;
}

static void swapthiscore(files_t *a, files_t *b)
{
    swapthisa(a, b);
    swapthisb(a, b);
}

static files_t *interieurdeboucle(files_t *ptr, int *swap)
{
    if (ptr->mtime < ptr->next->mtime) {
        swapthiscore(ptr, ptr->next);
        *swap = 1;
    }
    return (ptr->next);
}

int sort_files_time(files_t *files)
{
    int swap = 1;
    files_t *ptr;

    if (files == NULL)
        return (0);
    while (swap) {
        swap = 0;
        ptr = files;
        while (ptr->next != NULL) {
            ptr = interieurdeboucle(ptr, &swap);
        }
    }
    return (0);
}
