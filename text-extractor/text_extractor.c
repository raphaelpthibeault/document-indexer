#include <text_extractor.h>
#include <string.h>
#include <error_handling.h>
#include <wrapper.h>

char *parse_txt_file(const char *file_path);


char *extract_raw_text(const char *file_path) {
    char *extension = strrchr(file_path, '.');
    if (extension == NULL) {
        app_error("File has no extension");
    }

    if (strcmp(extension, ".txt") == 0) {
        return parse_txt_file(file_path);
    } else {
        app_error("Unsupported file type");
    }

    return NULL;
}

char *parse_txt_file(const char *file_path) {
    FILE* file = Fopen(file_path, "r");
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    char *text = Malloc(file_size + 1);
    size_t read = Fread(text, 1, file_size, file);
    Fclose(file);
    if (read != file_size) {
        app_error("Fread error");
    }

    text[file_size] = '\0';
    return text;
}