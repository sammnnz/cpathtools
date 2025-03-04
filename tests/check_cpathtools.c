#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <check.h>
#include "cpathtools.h"

#define I (size_t)11
#define P (size_t)14
#define L (size_t)25

#define PI (size_t) 3
#define LI (size_t) 8

#define MULTI_INDEX_COUNT(bs, bs_len) _get_max_index(bs, bs_len)
#define MULTI_INDEX_TEST(bs, bs_len, ...) _set_multi_index(bs, bs_len, (size_t)_i, __VA_ARGS__);

static int indices[I] = {0, 1, 2, 3, 4, 5, -1, -2, -3, -4, -5};

static char paths[P][L] = {
    "  a/b/c", 
    "  a/b/c/", 
    "  a/b/c/  ", 
    "  a/b/c/ d", 
    "  /a/b/c", 
    "/a/b/c/", 
    "  /a/b/c/ ", 
    "  /a ", 
    "  /a/ ", 
    "  a/ ", 
    "  / ",
    "  /a/ ",
    "  /a/ /",
    " C:\\fo1\\fo2/../fo3\\fi.c "
};

static char paths_invalid[PI][LI] ={
    "\0",
    "  text ",
    ""
};

static char answers[P][I][L] = {
    {"  a/b/c", "  a/", "  a/b/", "  a/b/c", "  a/b/c", "  a/b/c", "  a/b/", "  a/", "  a/", "  a/", "  a/"},
    {"  a/b/c/", "  a/", "  a/b/", "  a/b/c/", "  a/b/c/", "  a/b/c/", "  a/b/", "  a/", "  a/", "  a/", "  a/"},
    {"  a/b/c/  ", "  a/", "  a/b/", "  a/b/c/  ", "  a/b/c/  ", "  a/b/c/  ", "  a/b/", "  a/", "  a/", "  a/", "  a/"},
    {"  a/b/c/ d", "  a/", "  a/b/", "  a/b/c/", "  a/b/c/ d", "  a/b/c/ d", "  a/b/c/", "  a/b/", "  a/", "  a/", "  a/"},
    {"  /a/b/c", "  /a/", "  /a/b/", "  /a/b/c", "  /a/b/c", "  /a/b/c", "  /a/b/", "  /a/", "  /a/", "  /a/", "  /a/"},
    {"/a/b/c/", "/a/", "/a/b/", "/a/b/c/", "/a/b/c/", "/a/b/c/", "/a/b/", "/a/", "/a/", "/a/", "/a/"},
    {"  /a/b/c/ ", "  /a/", "  /a/b/", "  /a/b/c/ ", "  /a/b/c/ ", "  /a/b/c/ ", "  /a/b/", "  /a/", "  /a/", "  /a/", "  /a/"},
    {"  /a ", "  /a ", "  /a ", "  /a ", "  /a ", "  /a ", "  /a ", "  /a ", "  /a ", "  /a ", "  /a "},
    {"  /a/ ", "  /a/ ", "  /a/ ", "  /a/ ", "  /a/ ", "  /a/ ", "  /a/ ", "  /a/ ", "  /a/ ", "  /a/ ", "  /a/ "},
    {"  a/ ", "  a/ ", "  a/ ", "  a/ ", "  a/ ", "  a/ ", "  a/ ", "  a/ ", "  a/ ", "  a/ ", "  a/ "},
    {"  / ", "  / ", "  / ", "  / ", "  / ", "  / ", "  / ", "  / ", "  / ", "  / ", "  / "},
    {"  /a/ ", "  /a/ ", "  /a/ ", "  /a/ ", "  /a/ ", "  /a/ ", "  /a/ ", "  /a/ ", "  /a/ ", "  /a/ ", "  /a/ "},
    {"  /a/ /", "  /a/", "  /a/ /", "  /a/ /", "  /a/ /", "  /a/ /", "  /a/", "  /a/", "  /a/", "  /a/", "  /a/"},
    {
        " C:\\fo1\\fo2/../fo3\\fi.c ", " C:\\", " C:\\fo1\\", " C:\\fo1\\fo2/", " C:\\fo1\\fo2/../", " C:\\fo1\\fo2/../fo3\\",
        " C:\\fo1\\fo2/../fo3\\", " C:\\fo1\\fo2/../", " C:\\fo1\\fo2/", " C:\\fo1\\", " C:\\",
    }
};

/**
 * @warning Not safe! For internal use only.
 */
static size_t _get_max_index(size_t const * const bs, size_t bs_len)
{
    size_t re;

    re = 1;
    while(bs_len)
    {
        --bs_len;
        re *= bs[bs_len];
    }

    return re;
}

/**
 * @warning Not safe! For internal use only.
 */
static void _set_multi_index(size_t const * const bs, size_t bs_len, size_t const ind, ...)
{
    size_t div;
    va_list args;

    div = ind;
    va_start(args, ind);
    while(bs_len)
    {
        size_t *arg = va_arg(args, size_t*);
        --bs_len;
        *arg = div % bs[bs_len];
        div = div / bs[bs_len];
    }

    va_end(args);
}

static int test_GetPath_valid_imp(size_t const p, size_t const i)
{
    char *path;

    path = GetPath(paths[p], indices[i]);
    if (!path && answers[p][i])
    {
        ck_abort_msg("\nMemory allocation error in GetPath.\n");
    }

    ck_assert_str_eq(path, answers[p][i]);
    // fprintf(stdout, "\nIteration p: %lli, i: %lli\n", p, i);
    free(path);

    return 0;
}

static int test_GetPath_invalid_imp(size_t const pi)
{
    char *path;

    path = GetPath(paths_invalid[pi], 0);
    ck_assert_ptr_null(path);
    free(path);

    return 0;
}

START_TEST(test_GetPath_valid)
{
    size_t p, i;
    size_t bs[2] = {P,I};

    MULTI_INDEX_TEST(bs, 2, &i, &p)
    ck_assert_int_eq(test_GetPath_valid_imp(p, i), 0);
}
END_TEST

START_TEST(test_GetPath_invalid)
{
    size_t pi;
    size_t bs[1] = {PI};

    MULTI_INDEX_TEST(bs, 1, &pi)
    ck_assert_int_eq(test_GetPath_invalid_imp(pi), 0);
}
END_TEST

Suite *cpathtools_suite(void)
{
    size_t bs[2] = {P,I};
    Suite *s;
    TCase *tc_core;

    s = suite_create("cpathtools");
    tc_core = tcase_create("Core");
    tcase_add_loop_test(tc_core, test_GetPath_valid, 0, MULTI_INDEX_COUNT(bs, 2));
    tcase_add_loop_test(tc_core, test_GetPath_invalid, 0, PI);
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
