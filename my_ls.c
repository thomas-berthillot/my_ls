#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include "lib.h"
#include <stdlib.h>
#include <unistd.h>

static void print_error_flag(char c)
{
    write(2, "my_ls: invalid option -- '", 26);
    write(2, &c, 1);
    write(2, "'\n", 2);
}

static int find_flag(char *arg, t_options_t *options)
{
    char c;

    for (int i = 1; arg[i] != '\0'; i++) {
        c = arg[i];
        if (c == 'a')
            options->a = 1;
        if (c == 'l')
            options->l = 1;
        if (c == 'R')
            options->R = 1;
        if (c == 'd')
            options->d = 1;
        if (c == 't')
            options->t = 1;
        if (c != 't' && c != 'd' && c != 'R' && c != 'l' && c != 'a') {
            print_error_flag(c);
            return 84;
        }
    }
    return 0;
}

static void makepath(char *filepath, struct dirent *entry, char *argv)
{
    int j = 0;
    int k = 0;

    for (; argv[j] != '\0' && j < 1020; j++) {
        filepath[j] = argv[j];
    }
    if (j > 0 && filepath[j - 1] != '/') {
        filepath[j] = '/';
        j++;
    }
    while (entry->d_name[k] != '\0' && j < 1023) {
        filepath[j] = entry->d_name[k];
        j++;
        k++;
    }
    filepath[j] = '\0';
}

int yaunprobleme(char *argv, struct stat *info)
{
    DIR *dir;

    if (stat(argv, info) == -1) {
        return 1;
    }
    dir = opendir(argv);
    if (dir == NULL) {
        return 1;
    }
    closedir(dir);
    return 0;
}

files_t *stockagefolder(char *argv, struct stat *info, files_t **files)
{
    DIR *dir;
    char filepath[1024];
    struct dirent *entry;
    struct stat file_info;

    if (yaunprobleme(argv, info)) {
        perror(argv);
        exit(84);
    }
    dir = opendir(argv);
    entry = readdir(dir);
    while (entry != NULL) {
        filepath[0] = '\0';
        makepath(filepath, entry, argv);
        if (stat(filepath, &file_info) == 0)
            *files = addnode(*files, &file_info, entry->d_name, 0);
        entry = readdir(dir);
    }
    closedir(dir);
    return *files;
}

files_t *addingnodeparseur(int i, int argc, char **argv, t_options_t *options)
{
    int flagd = 0;
    struct stat info;
    files_t *files = NULL;

    for (; i != argc; i++) {
        if (argv[i][0] == '-')
            continue;
        flagd = 1;
        if (stat(argv[i], &info) == -1) {
            perror(argv[i]);
            exit(84);
        }
        if (S_ISDIR(info.st_mode) && options->d == 0) {
            files = stockagefolder(argv[i], &info, &files);
        } else
            files = addnode(files, &info, argv[i], flagd);
    }
    return files;
}

files_t *findpath(int argc, char **argv, t_options_t *options)
{
    struct stat info;
    files_t *files = NULL;
    int has_path = 0;

    for (int j = 1; j < argc; j++) {
        if (argv[j][0] != '-')
            has_path = 1;
    }
    if (has_path == 0) {
        stat(".", &info);
        if (options->d == 1)
            files = addnode(files, &info, ".", 1);
        else
            files = stockagefolder(".", &info, &files);
    } else
        files = addingnodeparseur(1, argc, argv, options);
    return files;
}

static int flagloop(int i, t_options_t *options, char **argv)
{
    if (argv[i][0] == '-' && argv[i][1] != '\0') {
        if (find_flag(argv[i], options) == 84)
            return (84);
    }
    return 0;
}

int my_ls(int argc, char **argv)
{
    t_options_t options = {0, 0, 0, 0, 0};
    int i = 1;
    files_t *pointeur = NULL;

    while (i < argc) {
        if (flagloop(i, &options, argv) == 84)
            return (84);
        i++;
    }
    pointeur = findpath(argc, argv, &options);
    executeflags(&options, pointeur);
    return 0;
}
