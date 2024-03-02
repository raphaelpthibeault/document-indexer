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
    printf("Document path: %s\n", document->path);
    printf("Document text: %s\n", document->text);

    Document_free(document);

    return 0;
}
