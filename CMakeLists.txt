cmake_minimum_required(VERSION 3.27)
project(document_indexer C)

set(CMAKE_C_STANDARD 23)

include_directories(
        text-extractor
        text-tokenizer
        util
)

add_executable(document_indexer main.c
        text-extractor/text_extractor.c
        util/error_handling.c
        util/util.h
        util/wrapper.c
        text-tokenizer/text_tokenizer.c
        text-tokenizer/text_tokenizer.h)
