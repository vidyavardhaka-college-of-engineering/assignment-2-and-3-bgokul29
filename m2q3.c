#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Node for linked list in chaining
typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

// Hash table entry for chaining
typedef struct {
    Node* head;
} HashTableEntry;

// Hash table for chaining
typedef struct {
    HashTableEntry* entries;
} HashTableChaining;

// Hash table for quadratic probing
typedef struct {
    int* keys;
    int* values;
    int size;
} HashTableProbing;

// Hash function
int hash(int key) {
    return key % TABLE_SIZE;
}

// Initialize hash table for chaining
HashTableChaining* createChainingHashTable() {
    HashTableChaining* table = (HashTableChaining*)malloc(sizeof(HashTableChaining));
    table->entries = (HashTableEntry*)malloc(TABLE_SIZE * sizeof(HashTableEntry));
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->entries[i].head = NULL;
    }
    return table;
}

// Initialize hash table for quadratic probing
HashTableProbing* createProbingHashTable() {
    HashTableProbing* table = (HashTableProbing*)malloc(sizeof(HashTableProbing));
    table->keys = (int*)malloc(TABLE_SIZE * sizeof(int));
    table->values = (int*)malloc(TABLE_SIZE * sizeof(int));
    table->size = TABLE_SIZE;
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->keys[i] = -1; // -1 indicates an empty slot
    }
    return table;
}

// Insert into hash table with chaining
void insertChaining(HashTableChaining* table, int key, int value) {
    int hashIndex = hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = table->entries[hashIndex].head;
    table->entries[hashIndex].head = newNode;
}

// Insert into hash table with quadratic probing
void insertProbing(HashTableProbing* table, int key, int value) {
    int hashIndex = hash(key);
    int i = 0;
    while (table->keys[(hashIndex + i * i) % table->size] != -1) {
        i++;
    }
    int finalIndex = (hashIndex + i * i) % table->size;
    table->keys[finalIndex] = key;
    table->values[finalIndex] = value;
}

// Search in hash table with chaining
int searchChaining(HashTableChaining* table, int key) {
    int hashIndex = hash(key);
    Node* current = table->entries[hashIndex].head;
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1; // Key not found
}

// Search in hash table with quadratic probing
int searchProbing(HashTableProbing* table, int key) {
    int hashIndex = hash(key);
    int i = 0;
    while (table->keys[(hashIndex + i * i) % table->size] != key) {
        if (table->keys[(hashIndex + i * i) % table->size] == -1) {
            return -1; // Key not found
        }
        i++;
    }
    int finalIndex = (hashIndex + i * i) % table->size;
    return table->values[finalIndex];
}

// Print hash table with chaining
void printChainingHashTable(HashTableChaining* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        Node* current = table->entries[i].head;
        while (current != NULL) {
            printf("-> (Key: %d, Value: %d) ", current->key, current->value);
            current = current->next;
        }
        printf("\n");
    }
}

// Print hash table with quadratic probing
void printProbingHashTable(HashTableProbing* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table->keys[i] != -1) {
            printf("Index %d: (Key: %d, Value: %d)\n", i, table->keys[i], table->values[i]);
        } else {
            printf("Index %d: Empty\n", i);
        }
    }
}

int main() {
    // Chaining example
    HashTableChaining* chainingTable = createChainingHashTable();
    insertChaining(chainingTable, 1, 10);
    insertChaining(chainingTable, 11, 20);
    insertChaining(chainingTable, 21, 30);
    printf("Chaining Hash Table:\n");
    printChainingHashTable(chainingTable);
    printf("Search for key 11: %d\n", searchChaining(chainingTable, 11));

    // Probing example
    HashTableProbing* probingTable = createProbingHashTable();
    insertProbing(probingTable, 1, 10);
    insertProbing(probingTable, 11, 20);
    insertProbing(probingTable, 21, 30);
    printf("Probing Hash Table:\n");
    printProbingHashTable(probingTable);
    printf("Search for key 11: %d\n", searchProbing(probingTable, 11));

    return 0;
}
