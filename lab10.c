//Matheus Lima
//LAB 10 - COP3502 - Section 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int count; // to store the number of occurrences
};

// Initializes a trie node
struct TrieNode *createNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node) {
        node->count = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            node->children[i] = NULL;
        }
    }
    return node;
}

// Inserts the word into the trie structure
void insert(struct TrieNode *root, char *word) {
    struct TrieNode *current = root;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    current->count++; // Increment the count for the last node of the word
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct TrieNode *root, char *word) {
    struct TrieNode *current = root;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            return 0; // Word not found
        }
        current = current->children[index];
    }
    return current->count; // Return the count of the last node
}

// Deallocates the trie structure
void deallocateTrie(struct TrieNode *root) {
    if (!root) {
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        deallocateTrie(root->children[i]);
    }
    free(root);
}

// Reads the dictionary from file and stores words in pInWords
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int numWords = 0;
    char buffer[100]; // Assuming maximum word length is 100 characters

    while (fscanf(file, "%s", buffer) != EOF && numWords < 256) {
        pInWords[numWords] = strdup(buffer);
        numWords++;
    }

    fclose(file);
    return numWords;
}

int main(void) {
    char *inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }

    // Create a trie and insert words into it
    struct TrieNode *root = createNode();
    for (int i = 0; i < numWords; i++) {
        insert(root, inWords[i]);
    }

    // Check occurrences of some words
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(root, pWords[i]));
    }

    // Deallocate the trie
    deallocateTrie(root);

    return 0;
}