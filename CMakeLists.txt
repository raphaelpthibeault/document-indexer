cmake_minimum_required(VERSION 3.27)
project(document_indexer C)

set(CMAKE_C_STANDARD 11)

include_directories(
        text-extractor
        text-tokenizer
        indexer
        document-processor
        util
)

add_executable(document_indexer
        text-extractor/text_extractor.c
        util/error_handling.c
        util/util.h
        util/wrapper.c
        text-tokenizer/text_tokenizer.c
        text-tokenizer/text_tokenizer.h
        indexer/indexer.c
        indexer/indexer.h
        document-processor/document_processor.c
        document-processor/document_processor.h
)
