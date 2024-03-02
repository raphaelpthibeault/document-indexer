#include <wrapper.h>
#include <error_handling.h>
#include <string.h>

/* static function declarations */
static void check_memory_limit(size_t size);

/* HEADER FUNCTIONS */
void *Malloc(size_t size) {
    void *ret;
    check_memory_limit(size);

    ret = malloc(size);
    if (!ret && !size) {
        ret = malloc(1);
    }
    if (!ret) {
        unix_error("Malloc error");
    }

#ifdef MALLOC_POISON // for debugging
    memset(ret, 0xA5, size);
#endif
    return ret;

}

void *Alloc_array(void **ptr, size_t size, size_t elem_size) {
    *ptr = Malloc(st_mult(size, elem_size)); // abort on overflow
    return *ptr;
}

void *Realloc(void *ptr, size_t size) {
    void *ret;
    check_memory_limit(size);

    ret = realloc(ptr, size);
    if (!ret && !size) {
        ret = malloc(1);
    }
    if (!ret) {
        unix_error("Realloc error");
    }
    return ret;
}

FILE *Fopen(const char *filename, const char *mode){
    FILE *fp;
    if ((fp = fopen(filename, mode)) == NULL)
        unix_error("Fopen error");
    return fp;
}

void Fclose(FILE *fp)
{
    if (fclose(fp) != 0)
        unix_error("Fclose error");
}

size_t Fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t n;
    if (((n = fread(ptr, size, nmemb, stream)) < nmemb) && ferror(stream))
        unix_error("Fread error");
    return n;
}

DIR *Opendir(const char *name)
{
    DIR *dir;
    if ((dir = opendir(name)) == NULL)
        unix_error("Opendir error");
    return dir;
}

void Closedir(DIR *dir)
{
    if (closedir(dir) < 0)
        unix_error("Closedir error");
}

FilenameList FilenameList_new(size_t capacity) {
    FilenameList list = Malloc(sizeof(struct SFilenameList));
    list->filenames = Malloc(st_mult(capacity, sizeof(char *)));
    list->size = 0;
    list->capacity = capacity;
    return list;
}

void FilenameList_free(FilenameList list) {
    for (size_t i = 0; i < list->size; i++) {
        FREE_AND_NULL(list->filenames[i]);
    }
    FREE_AND_NULL(list->filenames);
    FREE_AND_NULL(list);
}

void FilenameList_add(FilenameList list, const char *filename) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->filenames = Realloc(list->filenames, st_mult(list->capacity, sizeof(char *)));
    }
    list->filenames[list->size] = Malloc(strlen(filename) + 1);
    strcpy(list->filenames[list->size], filename);
    list->size++;
}

FilenameList FilenameList_get_from_directory(const char *path) {
    FilenameList list = FilenameList_new(10); // arbitrary initial capacity
    DIR *dir = Opendir(path);

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        FilenameList_add(list, entry->d_name);
    }

    Closedir(dir);

    return list;
}


/* STATIC FUNCTIONS */
static void check_memory_limit(size_t size) {
    ulong max_memory = 1024 * 1024 * 1024; // 1GB ; completely arbitrary and subject to change
    if (size > max_memory) {
        unix_error("Memory limit exceeded");
    }
}


