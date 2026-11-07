#include <stdio.h>
#include <dirent.h>
#include "lib.h"
#include <stdlib.h>
#include <criterion/criterion.h>

Test(my_ls_tests, test_invalid_option_z)
{
    char *argv[] = {"./my_ls", "-z", NULL};
    int argc = 2;

    int result = my_ls(argc, argv);
    cr_assert_eq(result, 84);
}

Test(my_ls_tests, test_invalid_option_k)
{
    char *argv[] = {"./my_ls", "-k", NULL};
    int argc = 2;

    int result = my_ls(argc, argv);
    cr_assert_eq(result, 84);
}

Test(my_ls_tests, test_fichier_random)
{
    char *argv[] = {"./my_ls", "gloubiboulga_jacqueschirac", NULL};
    int argc = 2;

    int result = my_ls(argc, argv);
    cr_assert_eq(result, 84);
}

Test(my_ls_tests, test_dossier_qui_marche)
{
    char *argv[] = {"./my_ls", ".", NULL};
    int argc = 2;

    int result = my_ls(argc, argv);
    cr_assert_eq(result, 0);
}

Test(my_ls_tests, test_beaucoup_flags)
{
    char *argv[] = {"./my_ls", "-lR", ".", NULL};
    int argc = 3;
    int result = my_ls(argc, argv);
    cr_assert_eq(result, 0);
}

Test(my_ls_tests, test_flags_and_files)
{
    char *argv[] = {"./my_ls", ".", "-l", NULL};
    int argc = 3;
    int result = my_ls(argc, argv);
    cr_assert_eq(result, 0);
}
