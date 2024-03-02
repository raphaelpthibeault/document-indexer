#include <error_handling.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

void unix_error(char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

void app_error(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(0);
}
