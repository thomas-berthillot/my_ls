/*
** EPITECH PROJECT, 2026
** Epitech my_ls
** File description:
** Libmy
*/

#ifndef MY_LIB
    #define MY_LIB

    #include <sys/stat.h>

typedef struct files {
    char *name;
    int size;
    int inod;
    int st_nlink;
    int st_blocks;
    int uid;
    int gid;
    unsigned int major;
    unsigned int minor;
    char *type;
    time_t mtime;
    int flagd;
    struct files *next;
    mode_t mode;
} files_t;
typedef struct s_options {
    int a;
    int l;
    int R;
    int d;
    int t;
} t_options_t;

files_t *addnode(files_t *head, struct stat *info, char *name, int flagd);
int executeflags(t_options_t *options, files_t *files);
int main(int argc, char **argv);
void printpermissions(files_t *files);
char *checkfiletype(struct stat *info);
int my_ls(int argc, char **argv);
void my_putchar(char c);
void my_putstr(char const *str);
int sort_files_time(files_t *files);
void my_putnbr(int nb);
void printime(time_t mtime);
void printstats(files_t *files, int count);
#endif
