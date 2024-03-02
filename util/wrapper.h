#ifndef WRAPPER_H
#define WRAPPER_H

#include <util.h>
#include <stdio.h>
#include <dirent.h>

void *Malloc(size_t size);
void *Alloc_array(void **ptr, size_t size, size_t elem_size);
void *Realloc(void *ptr, size_t size);
#define ALLOC_ARRAY(ptr, count) Alloc_array((void **)&(ptr), (count), sizeof(*(ptr)))
#define FREE_AND_NULL(p) do { free(p); (p) = NULL; } while (0)


FILE *Fopen(const char *filename, const char *mode);
void Fclose(FILE *fp);
size_t Fread(void *ptr, size_t size, size_t nmemb, FILE *stream);

DIR *Opendir(const char *name);
void Closedir(DIR *dir);

// not a wrapper but for modularity I'll put it here
typedef struct SFilenameList {
    char **filenames;
    size_t size;
    size_t capacity;
} *FilenameList;

FilenameList FilenameList_new(size_t capacity);
void FilenameList_free(FilenameList list);
void FilenameList_add(FilenameList list, const char *filename);
FilenameList FilenameList_get_from_directory(const char *path);

#endif // WRAPPER_H
