#include <stdio.h>

// Hash function as defined in the problem
int h1(int key) {
    int x = (key + 7) * (key + 7);
    x = x / 16;
    x = x + key;
    x = x % 11;
    return x;
}

int main() {
    // Keys to be inserted
    int keys[] = {43, 23, 1, 0, 15, 31, 4, 7, 11, 3};
    int tableSize = 11;
    int hashTable[11]; // Initialize hash table
    int numKeys = sizeof(keys) / sizeof(keys[0]);

    // Initialize the hash table with -1 (indicating empty slots)
    for (int i = 0; i < tableSize; i++) {
        hashTable[i] = -1;
    }

    // Insert keys into hash table
    for (int i = 0; i < numKeys; i++) {
        int key = keys[i];
        int homeSlot = h1(key);
        int hash = homeSlot;
        int j = 0;

        // Linear probing
        while (hashTable[hash] != -1) {
            hash = (homeSlot + ++j) % tableSize;
        }
        hashTable[hash] = key;
    }

    // Print final hash table
    printf("Final Hash Table:\n");
    for (int i = 0; i < tableSize; i++) {
        if (hashTable[i] != -1) {
            printf("Slot %d: %d\n", i, hashTable[i]);
        } else {
            printf("Slot %d: (empty)\n", i);
        }
    }

    return 0;
}
