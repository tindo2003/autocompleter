#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "mytrie.h"

trienode* createnode() {
  trienode* newnode = malloc(sizeof *newnode);
  for (int i = 0; i < NUM_CHARS; i++) {
    newnode->children[i] = NULL;
  }
  newnode->terminal = false;
  return newnode;
}

bool trieinsert(trienode** root, char* signedtext) {
  /**
   * Inserts a word into the trie.
   *
   * @param root A pointer to the root node pointer of the trie.
   * @param signedtext The word to be inserted into the trie.
   * @return true if the word was successfully inserted (i.e., it wasn't already in the trie),
   *         false if the word was already present in the trie.
   *
   */
  if (*root == NULL) {
    *root = createnode();
  }

  unsigned char* text = (unsigned char*) signedtext;
  trienode* tmp = *root;
  int length = strlen(signedtext);
   
  for (int i = 0; i < length; i++) {
    unsigned char cur_char = text[i];
    if (tmp->children[cur_char] == NULL) {
      tmp->children[cur_char] = createnode();
    }
    tmp = tmp->children[cur_char];
  }

  if (tmp->terminal) {
    return false;
  } else {
    tmp->terminal = true;
    return true;
  }
} 

bool has_children(trienode* cur_node) {
  for (int i = 0; i < NUM_CHARS; i++) {
    if (cur_node->children[i] != NULL) {
      return true;
    } 
  }
  return false;
}

trienode* deletestr_rec(trienode* cur_node, unsigned char* cur_char, bool* deleted) {
  if (cur_node == NULL) return cur_node;
  // cases:
  // 1: if string not in the trie
  // 2: string is in the trie -> clean up
  if (*cur_char == '\0') {
    *deleted = true;
    cur_node->terminal = false;
    if (has_children(cur_node) == false) {
      free(cur_node);
      cur_node = NULL;
    }
    return cur_node;
  }

  cur_node->children[*cur_char] = deletestr_rec(cur_node->children[*cur_char], cur_char + 1, deleted);
  if (*deleted && has_children(cur_node) == false && cur_node->terminal == false) {
    free(cur_node);
    cur_node = NULL;
  }
  return cur_node;
}

bool deletestr(trienode** root, char* signedtext) {
  unsigned char* text = (unsigned char*) signedtext;
  bool result = false;

  if (*root == NULL) return false;

  *root = deletestr_rec(*root, text, &result);
  return result;
}

void printtrie_rec(trienode* node, unsigned char* prefix, int length) {
  /** 
  * print the all words in alphabetical order recursively
  */
  unsigned char newprefix[length + 2];
  memcpy(newprefix, prefix, length);
  newprefix[length + 1] = 0;

  // base case
  if (node->terminal) {
    printf("WORD: %s\n", prefix);
    return; 
  }

  for (int i = 0; i < NUM_CHARS; i++) {
    if (node->children[i] != NULL) {
      newprefix[length] = i; 
      printtrie_rec(node->children[i], newprefix, length + 1);
    }
  }

}

void printtrie(trienode* root) {
  if (root == NULL) {
    printf("empty trie");
    return;
  }
  printtrie_rec(root, NULL, 0);
}

bool triesearch(trienode* root, char* signedtext) {
  if (root == NULL) return false;

  unsigned char* text = (unsigned char*) signedtext;
  int length = strlen(signedtext);

  trienode* tmp = root;
  
  for (int i = 0; i < length; i++) {
    unsigned char cur_char = text[i];
    if (tmp->children[cur_char] == NULL) {
      return false;
    } 
    tmp = tmp->children[cur_char];
  }
  return tmp->terminal;
}
