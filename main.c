#include <stdio.h>
#include <text_extractor.h>
#include <text_tokenizer.h>
#include <wrapper.h>
#include <indexer.h>
#include <document_processor.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }


    Document document = Document_get_from_file(argv[1]);

    DocumentList list = DocumentList_new(1);
    DocumentList_add_from_document(list, document);

    Index index = Index_new();
    for (size_t i = 0; i < list->size; i++) {
        Document doc = list->documents[i];
        char *text = doc->text;
        TokenList tokens = tokenize(text);
        for (size_t j = 0; j < tokens->size; j++) {
            Token token = tokens->tokens[j];
            Index_insert(index, token->value, doc->id, token->position);
        }

        TokenList_free(tokens);
    }

    Index_print(index);

    return 0;
}
