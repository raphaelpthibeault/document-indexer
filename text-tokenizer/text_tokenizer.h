#ifndef DOCUMENT_INDEXER_TEXT_TOKENIZER_H
#define DOCUMENT_INDEXER_TEXT_TOKENIZER_H

#include <stdlib.h>

typedef struct SToken {
    char *value;
    size_t position;

} *Token;

typedef struct STokenList {
    Token *tokens;
    size_t size;
    size_t capacity;
} *TokenList;


Token Token_new(char *value, size_t position);
void Token_free(Token token);

TokenList TokenList_new(size_t capacity);
void TokenList_free(TokenList list);
void TokenList_add(TokenList list, Token token);

TokenList tokenize(const char *text);

#endif //DOCUMENT_INDEXER_TEXT_TOKENIZER_H
