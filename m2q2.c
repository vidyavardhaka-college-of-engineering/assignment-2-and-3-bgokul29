#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 10

typedef enum { EMPTY, OCCUPIED, TOMBSTONE } CellStatus;

typedef struct {
    int key;
    CellStatus status;
} HashTableEntry;

typedef struct {
    HashTableEntry table[TABLE_SIZE];
} HashTable;

int hash(int key) {
    return key % TABLE_SIZE;
}

void initTable(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i].status = EMPTY;
    }
}

void insert(HashTable *ht, int key) {
    int index = hash(key);
    int firstTombstone = -1;

    while (ht->table[index].status == OCCUPIED) {
        if (ht->table[index].status == TOMBSTONE && firstTombstone == -1) {
            firstTombstone = index;
        }
        index = (index + 1) % TABLE_SIZE;
    }

    if (firstTombstone != -1) {
        index = firstTombstone;
    }

    ht->table[index].key = key;
    ht->table[index].status = OCCUPIED;
}

bool search(HashTable *ht, int key) {
    int index = hash(key);

    while (ht->table[index].status != EMPTY) {
        if (ht->table[index].status == OCCUPIED && ht->table[index].key == key) {
            return true;
        }
        index = (index + 1) % TABLE_SIZE;
    }

    return false;
}

void delete(HashTable *ht, int key) {
    int index = hash(key);

    while (ht->table[index].status != EMPTY) {
        if (ht->table[index].status == OCCUPIED && ht->table[index].key == key) {
            ht->table[index].status = TOMBSTONE;
            return;
        }
        index = (index + 1) % TABLE_SIZE;
    }
}

void printTable(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        if (ht->table[i].status == EMPTY) {
            printf("EMPTY\n");
        } else if (ht->table[i].status == OCCUPIED) {
            printf("Key %d\n", ht->table[i].key);
        } else {
            printf("TOMBSTONE\n");
        }
    }
}

int main() {
    HashTable ht;
    initTable(&ht);

    insert(&ht, 1);
    insert(&ht, 2);
    insert(&ht, 3);
    insert(&ht, 12);  // Collision with 2
    insert(&ht, 22);  // Collision with 2 and 12

    printTable(&ht);

    delete(&ht, 2);
    delete(&ht, 12);

    printf("After deletion:\n");
    printTable(&ht);

    insert(&ht, 32);  // Should go into the first tombstone slot (index of 2)
    printf("After insertion of 32:\n");
    printTable(&ht);

    return 0;
}
