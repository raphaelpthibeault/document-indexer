#include <stdio.h>
#include <text_extractor.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    char *text = extract_raw_text(argv[1]);
    printf("%s\n", text);

    return 0;
}
