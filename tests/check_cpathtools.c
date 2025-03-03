#include <stdio.h>
#include <stdlib.h>

#include <check.h>
#include "cpathtools.h"

#define I (size_t)11
#define P (size_t)2
#define L (size_t)11

static int indices[I] = {0, 1, 2, 3, 4, 5, -1, -2, -3, -4, -5};

static char paths[P + 1][L] = {
    "  a/b/c", 
    "  a/b/c/", 
    "_"
//     "  a/b/c/  ", 
//     "  a/b/c/ d", 
//    "  /a/b/c", 
//      "/a/b/c/", 
//    "  /a/b/c/ ", 
//    "  /a ", 
//    "  /a/ ", 
//     "  a/ ", 
//      "  / ",
//    "  /a/ ",
//    "  /a/ /"
};

static char answers[P][I][L] = {
    {"  a/b/c", "  a/", "  a/b/", "  a/b/c", "  a/b/c", "  a/b/c", "  a/b/", "  a/", "  a/", "  a/", "  a/"},
    {"  a/b/c/", "  a/", "  a/b/", "  a/b/c/", "  a/b/c/", "  a/b/c/", "  a/b/", "  a/", "  a/", "  a/", "  a/"},
};

static int test_GetPath_imp(int i)
{
    size_t p;
    char *path;
    
    p = 0;
    while (strcmp(paths[p], "_"))
    {
        path = GetPath(paths[p], indices[i]);
        if (!path)
        {
            ck_assert_msg(path != NULL, "\nMemory allocation error in GetPath.\n");
        }

        ck_assert_str_eq(path, answers[p][i]);
        fprintf(stdout, "\nIteration p: %i, i: %i\n", (int)p, i);
        free(path);
        ++p;
    }

    return 0;
}

START_TEST(test_GetPath)
{
    ck_assert_int_eq(test_GetPath_imp(_i), 0);
}
END_TEST

Suite * cpathtools_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("cpathtools");
    tc_core = tcase_create("Core");
    tcase_add_loop_test(tc_core, test_GetPath, 0, I);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(int argc, char *argv[])
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = cpathtools_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}