#include <stdio.h>
#include <string.h>
#include "dirent.h"

void runTests() {
    struct dirent *de;


    const char *buffer = "Google_Tests/Test_Files/straight-line";
    DIR *dr = opendir(buffer);

    if (dr == NULL) {
        printf("Could not open current directory");
    }

    while ((de = readdir(dr)) != NULL) {
        freopen(strcat("Google_Tests/Test_Files/straight-line/", de->d_name), "r", stdin);

    }

    closedir(dr);

}