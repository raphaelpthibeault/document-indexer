# Document Indexer
A document indexing library implemented in C. The library is designed to be used in a document management system. 

## Usage
Create a new instance of the indexer using the `Indexer_new` function. The function takes no arguments and returns a pointer to the new instance. 
After the instance is created, documents can be added to the index using the `Index_insert` function. 
The function takes a pointer to the index, a pointer to a raw string of the document, the document's id, and the position of the string in the document.
```c
Index index = Index_new();
Index_insert(index, str, document_id, str_pos);
```
We can then search the index using the `Index_search` function. The function takes a pointer to the index and a pointer to a raw string of the query. The function returns a pointer to a list of document ids that contain the query.
```c
OccurrenceList occurences = Index_search(index, query_str);
```

Note: the library also contains text processing functions that can be used to preprocess the documents and queries before adding them to the index or searching the index.
These can be found in the document-processor, text-extractor and text-tokenizer modules.