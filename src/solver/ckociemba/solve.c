#include <stdio.h>
#include <stdlib.h>
#include "search.h"

// Extracted function
char* solve_cube(int argc, char **argv) {
    if (argc > 1) {
        char patternized[64];
        char* facelets = argv[1];
        if (argc > 2) {
            patternize(facelets, argv[2], patternized);
            facelets = patternized;
        }
        char *sol = solution(
            facelets,
            24,
            1000,
            0,
            "cache"
        );
        return sol;
    }
    return NULL;
}
