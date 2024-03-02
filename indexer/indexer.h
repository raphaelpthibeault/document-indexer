#ifndef DOCUMENT_INDEXER_INDEXER_H
#define DOCUMENT_INDEXER_INDEXER_H
#include <stdlib.h>


typedef struct SOccurrence {
    size_t document_id;
    size_t position;
} *Occurrence;

typedef struct SOccurrenceList {
    Occurrence *occurrences;
    size_t size;
    size_t capacity;
} *OccurrenceList;

typedef enum { RED, BLACK } Color;

typedef struct SNode {
    char *key;
    OccurrenceList occurrences;
    struct SNode *left;
    struct SNode *right;
    struct SNode *parent;
    Color color;
} *Node;

typedef struct SIndex {
    Node root;
} *Index;

Occurrence Occurrence_new(size_t document_id, size_t position);
void Occurrence_free(Occurrence occurrence);

OccurrenceList OccurrenceList_new(size_t capacity);
void OccurrenceList_free(OccurrenceList list);
void OccurrenceList_add(OccurrenceList list, Occurrence occurrence);

Node Node_new(char *key, Occurrence occurrence);
void Node_free(Node node);

Index Index_new(void);
void Index_free(Index index);
void Index_insert(Index index, char *key, size_t document_id, size_t position);
OccurrenceList Index_search(Index index, char *key);



#endif //DOCUMENT_INDEXER_INDEXER_H
