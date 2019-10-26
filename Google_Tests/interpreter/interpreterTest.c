#include <stdio.h>
#include "dirent.h"

void testLiteral() {
    struct dirent *de;

    const char *buffer = "Google_Tests/Test_Files/straight-line";
    DIR *dr = opendir(buffer);

    if (dr == NULL) {
        printf("Could not open current directory");
    }

    while ((de = readdir(dr)) != NULL) {
        printf("%s\n", de->d_name);
        closedir(dr);
    }

}