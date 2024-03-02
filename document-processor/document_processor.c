#include <document_processor.h>
#include <wrapper.h>
#include <string.h>
#include <text_extractor.h>
#include <text_tokenizer.h>


Document Document_new(const char *path, const char *text) {
    Document document = Malloc(sizeof(struct SDocument));
    document->path = Malloc(strlen(path) + 1);
    strcpy(document->path, path);
    document->text = Malloc(strlen(text) + 1);
    strcpy(document->text, text);
    document->id = -1;
    return document;
}

void Document_free(Document document) {
    FREE_AND_NULL(document->path);
    FREE_AND_NULL(document->text);
    FREE_AND_NULL(document);
}

DocumentList DocumentList_new(size_t capacity) {
    DocumentList list = Malloc(sizeof(struct SDocumentList));
    list->documents = Malloc(st_mult(capacity, sizeof(Document)));
    list->size = 0;
    list->capacity = capacity;
    return list;
}

void DocumentList_free(DocumentList list) {
    for (size_t i = 0; i < list->size; i++) {
        Document_free(list->documents[i]);
    }
    FREE_AND_NULL(list->documents);
    FREE_AND_NULL(list);
}

void DocumentList_add_from_document(DocumentList list, Document document) {
    if (list->size == list->capacity) {
        st_mult(list->capacity, 2);
        list->documents = Realloc(list->documents, st_mult(list->capacity, sizeof(Document)));
    }
    document->id = list->size;
    list->documents[list->size++] = document;
}

void DocumentList_add_from_document_list(DocumentList list, DocumentList other) {
    for (size_t i = 0; i < other->size; i++) {
        DocumentList_add_from_document(list, other->documents[i]);
    }

    FREE_AND_NULL(other); // but keep the documents since we just move the pointers
}

Document Document_get_from_file(const char *path) {
    char *text = extract_raw_text(path);
    Document document = Document_new(path, text);
    FREE_AND_NULL(text);
    return document;
}

DocumentList DocumentList_get_from_file_list(const char **paths, size_t count) {
    DocumentList list = DocumentList_new(count);
    for (size_t i = 0; i < count; i++) {
        Document document = Document_get_from_file(paths[i]);
        DocumentList_add_from_document(list, document);
    }
    return list;
}

DocumentList DocumentList_get_from_directory(const char *path) {
    FilenameList filenames = FilenameList_get_from_directory(path);
    DocumentList list = DocumentList_new(filenames->size);
    for (size_t i = 0; i < filenames->size; i++) {
        char *full_path = Malloc(strlen(path) + strlen(filenames->filenames[i]) + 2);
        strcpy(full_path, path);
        strcat(full_path, "/");
        strcat(full_path, filenames->filenames[i]);
        Document document = Document_get_from_file(full_path);
        DocumentList_add_from_document(list, document);
        FREE_AND_NULL(full_path);
    }
    FilenameList_free(filenames);
    return list;
}


