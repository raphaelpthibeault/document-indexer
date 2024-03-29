#include <text_tokenizer.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wrapper.h>


static void skip_delimiters(const char *text, size_t *i);

TokenList TokenList_new(size_t capacity) {
    TokenList list = Malloc(sizeof(struct STokenList));
    list->tokens = Malloc(st_mult(capacity, sizeof(Token)));
    list->size = 0;
    list->capacity = capacity;
    return list;
}

void TokenList_add(TokenList list, Token token) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->tokens = Realloc(list->tokens, st_mult(list->capacity, sizeof(Token)));
    }
    list->tokens[list->size++] = token;
}

Token Token_new(char *value, size_t position) {
    Token token = Malloc(sizeof(struct SToken));
    token->value = Malloc(strlen(value) + 1);
    strcpy(token->value, value);
    token->position = position;
    return token;
}

void Token_free(Token token) {
    FREE_AND_NULL(token->value);
    FREE_AND_NULL(token);
}

void TokenList_free(TokenList list) {
    for (size_t i = 0; i < list->size; i++) {
        Token_free(list->tokens[i]);
    }
    FREE_AND_NULL(list->tokens);
    FREE_AND_NULL(list);
}

TokenList tokenize(const char *text) {
    TokenList list = TokenList_new(10); // arbitrary initial capacity

    size_t i = 0;
    while (text[i] != '\0') {
        skip_delimiters(text, &i);
        if (text[i] != '\0') {
            size_t start = i;
            while (text[i] != '\0' && !(isspace((unsigned char)text[i]) || (ispunct((unsigned char)text[i]) && text[i] != '\''))) {
                i++;
            }

            char *value = Malloc(i - start + 1);
            for (size_t j = start; j < i; ++j)
                value[j - start] = tolower((unsigned char) text[j]);

            value[i - start] = '\0';
            TokenList_add(list, Token_new(value, start));
            FREE_AND_NULL(value); // value is copied into the token
        }
    }
    return list;
}

static void skip_delimiters(const char *text, size_t *i) {
    if (!text || !i) {
        return;
    }

    while (text[*i] != '\0' && (isspace((unsigned char)text[*i]) || ispunct((unsigned char)text[*i]))) {
        (*i)++;
    }
}
