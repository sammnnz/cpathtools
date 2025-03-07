#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>

#include <check.h>
#include "cpathtools.h"

#define I (unsigned int)11
#define P (unsigned int)14
#define L (unsigned int)25

#define PI (unsigned int)3
#define LI (unsigned int)8

#define MULTI_INDEX_COUNT(bs, bs_len) _get_max_int_index(bs, bs_len)
#define MULTI_INDEX_TEST(bs, bs_len, ...) _set_int_multi_index(bs, bs_len, (unsigned int)_i, __VA_ARGS__);

static short indices[I] = {0, 1, 2, 3, 4, 5, -1, -2, -3, -4, -5};

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
 * @warning For internal use only.
 */
static int _get_max_int_index(unsigned int const * const bs, size_t bs_len)
{
    int __line;
    unsigned long long re;

    re = 1;
    while(bs_len)
    {
        --bs_len;
        re *= bs[bs_len]; __line = __LINE__;
        if (re > INT_MAX)
        {
            fprintf(stderr, "\n\
                %s: line %i:\n\
                WARNING: Buffer overflow in `%s` function. Index may be differ from expected.\n", 
                __FILE__, __line, __func__);
            return INT_MAX;
        }
    }

    return (int)re;
}

/**
 * @warning For internal use only.
 */
static int _set_int_multi_index(unsigned int const * const bs, size_t bs_len, unsigned int const ind, ...)
{
    int __line;
    unsigned int div, mod;
    va_list args;

    __line = -1;
    div = ind;
    va_start(args, ind);
    while(bs_len)
    {
        int *arg = va_arg(args, int*);
        --bs_len;
        mod = div % bs[bs_len]; __line == __LINE__;
        if (mod > INT_MAX)
        {
            va_end(args);
            fprintf(stderr, "\n\
                %s: line %i:\n\
                ERROR: Buffer overflow in `%s` function. Valid index is required.\n", 
                __FILE__, __line, __func__);

            return -1;
        }

        *arg =  (int)mod;
        div = div / bs[bs_len];
    }

    va_end(args);

    return 0;
}

static int test_GetPath_valid_imp(int const p, int const i)
{
    char *path;

    path = GetPath(paths[p], indices[i]);
    if (!path)
    {
        ck_abort_msg("\nMemory allocation error in GetPath.\n");
    }

    ck_assert_str_eq(path, answers[p][i]);
    // fprintf(stdout, "\nIteration p: %lli, i: %lli\n", p, i);
    free(path);

    return 0;
}

static int test_GetPath_invalid_imp(int const pi)
{
    char *path;

    path = GetPath(paths_invalid[pi], 0);
    ck_assert_ptr_null(path);
    free(path);

    return 0;
}

START_TEST(test_GetPath_valid)
{
    int p, i;
    unsigned int bs[2] = {P,I};

    MULTI_INDEX_TEST(bs, 2, &i, &p)
    ck_assert_int_eq(test_GetPath_valid_imp(p, i), 0);
}
END_TEST

START_TEST(test_GetPath_invalid)
{
    int pi;
    unsigned int bs[1] = {PI};

    MULTI_INDEX_TEST(bs, 1, &pi)
    ck_assert_int_eq(test_GetPath_invalid_imp(pi), 0);
}
END_TEST

Suite *cpathtools_suite(void)
{
    unsigned int bs[2] = {P,I};
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
