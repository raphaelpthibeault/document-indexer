#include <indexer.h>
#include <wrapper.h>
#include <string.h>


void Index_insert_fixup(Index index, Node new_node);
void left_rotate(Index index, Node node);
void right_rotate(Index index, Node node);


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

    Index_insert_fixup(index, new_node);
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


void Index_print_node(Node node, int depth) {
    if (node != NULL) {
        Index_print_node(node->right, depth + 1);
        printf("%s\n", node->key);
        Index_print_node(node->left, depth + 1);
    }
}

void Index_print(Index index) {
    printf("Index:\n");
    Index_print_node(index->root, 0);
    printf("\n");
}



void left_rotate(Index index, Node node) {
    Node right = node->right;
    node->right = right->left;
    if (right->left != NULL) {
        right->left->parent = node;
    }
    right->parent = node->parent;
    if (node->parent == NULL) {
        index->root = right;
    } else if (node == node->parent->left) {
        node->parent->left = right;
    } else {
        node->parent->right = right;
    }
    right->left = node;
    node->parent = right;
}

void right_rotate(Index index, Node node) {
    Node left = node->left;
    node->left = left->right;
    if (left->right != NULL) {
        left->right->parent = node;
    }
    left->parent = node->parent;
    if (node->parent == NULL) {
        index->root = left;
    } else if (node == node->parent->right) {
        node->parent->right = left;
    } else {
        node->parent->left = left;
    }
    left->right = node;
    node->parent = left;
}

void Index_insert_fixup(Index index, Node new_node) {
    while (new_node->parent != NULL && new_node->parent->color == RED) {
        if (new_node->parent == new_node->parent->parent->left) {
            Node uncle = new_node->parent->parent->right;
            if (uncle != NULL && uncle->color == RED) {
                new_node->parent->color = BLACK;
                uncle->color = BLACK;
                new_node->parent->parent->color = RED;
                new_node = new_node->parent->parent;
            } else {
                if (new_node == new_node->parent->right) {
                    new_node = new_node->parent;
                    left_rotate(index, new_node);
                }
                new_node->parent->color = BLACK;
                new_node->parent->parent->color = RED;
                right_rotate(index, new_node->parent->parent);
            }
        } else {
            Node uncle = new_node->parent->parent->left;
            if (uncle != NULL && uncle->color == RED) {
                new_node->parent->color = BLACK;
                uncle->color = BLACK;
                new_node->parent->parent->color = RED;
                new_node = new_node->parent->parent;
            } else {
                if (new_node == new_node->parent->left) {
                    new_node = new_node->parent;
                    right_rotate(index, new_node);
                }
                new_node->parent->color = BLACK;
                new_node->parent->parent->color = RED;
                left_rotate(index, new_node->parent->parent);
            }
        }
    }
    index->root->color = BLACK;
}

