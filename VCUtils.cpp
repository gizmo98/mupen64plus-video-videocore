// mupen64plus-video-videocore/VCUtils.cpp
//
// Copyright (c) 2016 The mupen64plus-video-videocore Authors

#include <stdlib.h>
#include <string.h>

char *xstrsep(char **stringp, const char* delim) {
    char *start = *stringp;
    char *p = (start != NULL) ? strpbrk(start, delim) : NULL;
    if (p == NULL) {
        *stringp = NULL;
    } else {
        *p = '\0';
        *stringp = p + 1;
    }
    return start;
}

