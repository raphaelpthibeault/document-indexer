#include <stdio.h>
#include <text_extractor.h>
#include <text_tokenizer.h>
#include <wrapper.h>
#include <text_indexer.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    char *text = extract_raw_text(argv[1]);

    TokenList list = tokenize(text);

    Index index = Index_new();
    for (size_t i = 0; i < list->size; i++) {
        Occurrence occurrence = Occurrence_new(0, list->tokens[i]->position);
        Index_insert(index, list->tokens[i]->value, 0, list->tokens[i]->position);
    }

    for (size_t i = 0; i < list->size; i++) {
        OccurrenceList occurrences = Index_search(index, list->tokens[i]->value); // duplicates in the list, not in the index
        printf("%s: ", list->tokens[i]->value);
        for (size_t j = 0; j < occurrences->size; j++) {
            printf("%zu ", occurrences->occurrences[j]->position);
        }
        printf("\n");
    }


    Index_free(index);

    FREE_AND_NULL(text);
    TokenList_free(list);

    return 0;
}
