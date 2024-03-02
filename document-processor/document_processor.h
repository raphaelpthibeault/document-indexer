#ifndef DOCUMENT_INDEXER_DOCUMENT_PROCESSOR_H
#define DOCUMENT_INDEXER_DOCUMENT_PROCESSOR_H

#include <stdlib.h>

typedef struct SDocument {
    char *path;
    char *text;
    size_t id;
} *Document;

typedef struct SDocumentList {
    Document *documents;
    size_t size;
    size_t capacity;
} *DocumentList;

Document Document_new(const char *path, const char *text);
void Document_free(Document document);

DocumentList DocumentList_new(size_t capacity);
void DocumentList_free(DocumentList list);
void DocumentList_add_from_document(DocumentList list, Document document);
void DocumentList_add_from_document_list(DocumentList list, DocumentList other);

Document Document_get_from_file(const char *path);
DocumentList DocumentList_get_from_file_list(const char **paths, size_t count);
DocumentList DocumentList_get_from_directory(const char *path);



#endif //DOCUMENT_INDEXER_DOCUMENT_PROCESSOR_H
