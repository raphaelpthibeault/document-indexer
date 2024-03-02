#include <stdio.h>
#include <text_extractor.h>
#include <text_tokenizer.h>
#include <wrapper.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    char *text = extract_raw_text(argv[1]);
    //printf("%s\n", text);

    TokenList list = tokenize(text);
    for (size_t i = 0; i < list->size; i++) {
        printf("%s\n", list->tokens[i]->value);
    }

    FREE_AND_NULL(text);
    TokenList_free(list);

    return 0;
}
