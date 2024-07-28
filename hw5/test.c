#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "mytrie.h"


void run_tests() {
    trienode* root = NULL;  // Start with an empty trie

    // Test 1: Delete from empty trie
    assert(deletestr(&root, "hello") == false);

    // Test 2: Insert and then delete a word
    assert(trieinsert(&root, "hello") == true);
    assert(deletestr(&root, "hello") == true);
    assert(triesearch(root, "hello") == false);

    // Test 3: Delete a non-existent word
    assert(trieinsert(&root, "world") == true);
    assert(deletestr(&root, "hello") == false);
    assert(triesearch(root, "world") == true);

    // Test 4: Insert multiple words and delete one
    assert(trieinsert(&root, "hello") == true);
    assert(trieinsert(&root, "hell") == true);
    assert(trieinsert(&root, "help") == true);
    assert(deletestr(&root, "hell") == true);
    assert(triesearch(root, "hell") == false);
    assert(triesearch(root, "hello") == true);
    assert(triesearch(root, "help") == true);

    // Test 5: Delete a word that is a prefix of another word
    assert(deletestr(&root, "help") == true);
    assert(triesearch(root, "help") == false);
    assert(triesearch(root, "hello") == true);

    // Test 6: Delete a word and then reinsert it
    assert(deletestr(&root, "hello") == true);
    assert(triesearch(root, "hello") == false);
    assert(trieinsert(&root, "hello") == true);
    assert(triesearch(root, "hello") == true);

    // Test 7: Insert and delete an empty string
    assert(trieinsert(&root, "") == true);
    assert(deletestr(&root, "") == true);
    assert(triesearch(root, "") == false);

    // Test 8: Insert and delete a long word
    assert(trieinsert(&root, "supercalifragilisticexpialidocious") == true);
    assert(deletestr(&root, "supercalifragilisticexpialidocious") == true);
    assert(triesearch(root, "supercalifragilisticexpialidocious") == false);

    // Test 9: Free an empty trie
    trienode* empty_root = NULL;
    freetree(empty_root);
    assert(is_trie_empty(empty_root));

    // Test 10: Free a trie with one word
    trienode* single_word_root = NULL;
    assert(trieinsert(&single_word_root, "hello") == true);
    freetree(single_word_root);
    single_word_root = NULL;
    assert(is_trie_empty(single_word_root));

    // Test 11: Free a trie with multiple words
    trienode* multi_word_root = NULL;
    assert(trieinsert(&multi_word_root, "hello") == true);
    assert(trieinsert(&multi_word_root, "world") == true);
    assert(trieinsert(&multi_word_root, "hi") == true);
    freetree(multi_word_root);
    multi_word_root = NULL;
    assert(is_trie_empty(multi_word_root));

    // Test 12: Free a trie, then try to use it (should not crash)
    trienode* freed_root = NULL;
    assert(trieinsert(&freed_root, "test") == true);
    freetree(freed_root);
    freed_root = NULL;
    assert(triesearch(freed_root, "test") == false);
    assert(deletestr(&freed_root, "test") == false);
    assert(trieinsert(&freed_root, "new") == true);

    printf("All tests passed successfully!\n");
}

int main() {
    run_tests();
    return 0;
}