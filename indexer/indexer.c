#include <indexer.h>
#include <wrapper.h>
#include <text_tokenizer.h>
#include <string.h>

Occurrence Occurrence_new(size_t document_id, size_t position) {
    Occurrence occurrence = Malloc(sizeof(struct SOccurrence));
    occurrence->document_id = document_id;
    occurrence->position = position;
    return occurrence;
}

void Occurrence_free(Occurrence occurrence) {
    FREE_AND_NULL(occurrence);
}

OccurrenceList OccurrenceList_new(size_t capacity) {
    OccurrenceList list = Malloc(sizeof(struct SOccurrenceList));
    list->occurrences = Malloc(st_mult(capacity, sizeof(Occurrence)));
    list->size = 0;
    list->capacity = capacity;
    return list;
}

void OccurrenceList_free(OccurrenceList list) {
    for (size_t i = 0; i < list->size; i++) {
        Occurrence_free(list->occurrences[i]);
    }
    FREE_AND_NULL(list->occurrences);
    FREE_AND_NULL(list);
}

void OccurrenceList_add(OccurrenceList list, Occurrence occurrence) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->occurrences = Realloc(list->occurrences, st_mult(list->capacity, sizeof(Occurrence)));
    }
    list->occurrences[list->size++] = occurrence;
}

Node Node_new(char *key, Occurrence occurrence) {
    Node node = Malloc(sizeof(struct SNode));
    node->key = Malloc(strlen(key) + 1);
    strcpy(node->key, key);
    node->occurrences = OccurrenceList_new(10); // arbitrary initial capacity
    OccurrenceList_add(node->occurrences, occurrence);
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->color = RED;
    return node;
}

void Node_free(Node node) {
    FREE_AND_NULL(node->key);
    OccurrenceList_free(node->occurrences);
    FREE_AND_NULL(node);
}

Index Index_new(void) {
    Index index = Malloc(sizeof(struct SIndex));
    index->root = NULL;
    return index;
}

void Index_free(Index index) {
    FREE_AND_NULL(index);
}

void Index_insert(Index index, char *key, size_t document_id, size_t position) {
    Node node = index->root;
    Node parent = NULL;
    while (node != NULL) {
        parent = node;
        int cmp = strcmp(key, node->key);
        if (cmp == 0) {
            OccurrenceList_add(node->occurrences, Occurrence_new(document_id, position));
            return;
        } else if (cmp < 0) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    Node new_node = Node_new(key, Occurrence_new(document_id, position));
    new_node->parent = parent;
    if (parent == NULL) {
        index->root = new_node;
    } else if (strcmp(key, parent->key) < 0) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
}

OccurrenceList Index_search(Index index, char *key) {
    Node node = index->root;
    while (node != NULL) {
        int cmp = strcmp(key, node->key);
        if (cmp == 0) {
            return node->occurrences;
        } else if (cmp < 0) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return NULL;
}

/* TODO Index_search_fuzzy */

