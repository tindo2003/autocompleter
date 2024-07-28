#ifndef MYTRIE_H
#define MYTRIE_H

#include <stdbool.h>

#define NUM_CHARS 256  

// Forward declaration of the trienode structure
typedef struct trienode trienode;

// Define the trienode structure
struct trienode {
  trienode* children[NUM_CHARS];
  bool terminal;
};

// Function prototypes
trienode* createnode();
bool trieinsert(trienode** root, char* str);
bool deletestr(trienode** root, char* str);
bool triesearch(trienode* root, char* str);


#endif 