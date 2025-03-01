#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpathtools.h"

#define __UTF8INVERSESLASH__ 92 // Equal \ in utf8
#define __UTF8SLASH__ 47        // Equal / in utf8
#define __UTF8SPACE__ 32        // Equal space in utf8

/**
 * Return pointer on __str without spaces in the beginig
 *
 * @warning NOT SAFE. FOR INTERNAL USE ONLY.
 */
static char *__skipstartspaces(char *__str)
{
    if (!strchr(__str, __UTF8SPACE__))
    {
        return __str;
    }

    while (1)
    {
        if (*__str == __UTF8SPACE__)
        {
            ++__str;
            continue;
        }

        break;
    }

    return __str;
}

/**
  * GetPath function.
  *
  * Used to get parent paths.
  *
  * @param __path Any string (expected string should be similar to path for any platform).
  * @param __depth Integer (long long) indicating the slash index.
  * @return String (part of __path) up to the slash pointed to by the index.
  In this case, allocated memory for return value;
  NULL if an empty string (or NULL) is passed or in case of a memory allocation error.
  * @warning Be careful, may be memory leak (see below).
  */
char *GetPath(char *__path, long long __depth)
{
    size_t slash_pos, slashs_count;
    char *path;
    char *result;
    size_t *slashs;

    // Check for NULL or end symboll in start of __path
    if (!__path ||
        (__path && !*__path))
    {
        fprintf(stderr, "WARNING: Invalid argument \'__path\' in %s function.\
            \n%s must not be NULL or have zero length.",
                __func__, __path);
        return NULL;
    }

    // Check slash and inverse slash in __path
    if (!strchr(__path, __UTF8SLASH__) &&
        !strchr(__path, __UTF8INVERSESLASH__))
    {
        fprintf(stderr, "WARNING: Invalid argument \'__path\' in %s function.\
            \n%s is not path.",
                __func__, __path);
        return NULL;
    }

    // Skip whitespaces in begin of __path
    path = __skipstartspaces(__path);
    if (!__depth)
    {
        slash_pos = strlen(__path);
        goto finally;
        // return path;
    }

    slash_pos = path - __path;
    if (*path == __UTF8SLASH__ || *path == __UTF8INVERSESLASH__)
    {
        ++path;
        ++slash_pos;
    }

    slashs_count = (size_t)0;
    slashs = (size_t *)malloc(sizeof(size_t));
    if (!slashs)
    {
        fprintf(stderr, "ERROR: Malloc failed in %s function.", __func__);
        return NULL;
    }
    while (*path)
    {
        char *sl = strchr(path, __UTF8SLASH__);
        char *isl = strchr(path, __UTF8INVERSESLASH__);
        if (sl != NULL && isl != NULL)
        {
            if (sl > isl)
            {
                slash_pos += isl - path;
                path = isl;
            }
            else
            {
                slash_pos += sl - path;
                path = sl;
            }
        }
        else if (sl != NULL)
        {
            slash_pos += sl - path;
            path = sl;
        }
        else if (isl != NULL)
        {
            slash_pos += isl - path;
            path = isl;
        }
        else
        {
            char *tmp_path = __skipstartspaces(path);
            if (strlen(__path) == slash_pos + (tmp_path - path))
            { // Cases: '  /  ', '/.../.../   '
                slashs_count = slashs_count ? slashs_count - 1 : slashs_count;
            }

            break;
        }

        ++path;
        ++slash_pos;
        ++slashs_count;
        size_t *tmp_slashs = realloc(slashs, sizeof(*slashs) * slashs_count);
        if (!tmp_slashs)
        {
            free(slashs);
            fprintf(stderr, "ERROR: Realloc failed in %s function.", __func__);
            return NULL;
        }

        slashs = tmp_slashs;
        slashs[slashs_count - 1] = slash_pos;
        if (*path == '\0')
        { // if true then go out from loop
            --slashs_count;
        }
    };

    if (!slashs_count)
    {
        free(slashs);
        slash_pos = strlen(__path);
        goto finally;
        // return __path;
    }

    if (slashs_count > 0x7fffffffffffffff)
    { // 2^63 - 1
        free(slashs);
        fprintf(stderr, "ERROR: Too much slashes in '__path' argument from %s function.\
                 Slashes must not be more than 2^63 - 1",
                __func__);
        return NULL;
    }

    ++slashs_count; // x = slashs_count >= 2
    if (__depth >= (long long)slashs_count)
    { // __depth >= x
        slash_pos = strlen(__path);
        // return __path;
    }
    else if (__depth > 0)
    { // x > __depth > 0
        slash_pos = *(slashs + __depth - 1);
    }
    else if (-__depth < (long long)slashs_count)
    { // 0 > __depth > -x
        slash_pos = *(slashs + slashs_count + __depth - 1);
    }
    // else if (-__depth >= (long long)slashs_count) { // __depth = x
    //     slash_pos = *slashs;
    // }
    else
    { // -x >= __depth
        /*free(slashs);
        return NULL;*/
        slash_pos = *slashs;
    }

    free(slashs);
    goto finally;

finally:
    result = (char *)calloc(slash_pos + 1, sizeof(char));
    if (!result)
    {
        fprintf(stderr, "ERROR: Malloc failed in %s function.", __func__);
        return NULL;
    }

    result = memmove(result, __path, slash_pos * sizeof(char));
    return result;
}