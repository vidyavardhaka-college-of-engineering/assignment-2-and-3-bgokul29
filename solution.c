#include <stdio.h>
#include <stdlib.h>

// Function to count the number of set bits in an integer
int countSetBits(int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

long long int assign(int n, int **preference) {
    int mx = 1 << n;
    long long int *dp = (long long int *)calloc(mx, sizeof(long long int));
    dp[mx - 1] = 1;  // Base case: one way to assign no topics

    // Proceed in bottom-up manner
    for (int mask = mx - 1; mask >= 0; mask--) {
        // Count number of set bits in mask
        int s = countSetBits(mask);

        // This is a state for student s
        for (int i = 0; i < n; i++) {
            if (preference[s][i] && !(mask & (1 << i))) {
                dp[mask] += dp[mask | (1 << i)];
            }
        }
    }

    long long int result = dp[0];
    free(dp);
    return result;
}

int main() {
    int n;
    printf("How many students are there? \n");
    scanf("%d", &n);

    int **preference = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        preference[i] = (int *)malloc(n * sizeof(int));
    }

    printf("\nEnter the preferences of each of %d students for %d subjects\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &preference[i][j]);
        }
    }

    printf("\nTotal number of assignments that can be prepared are\n");
    printf("%lld\n", assign(n, preference));

    for (int i = 0; i < n; i++) {
        free(preference[i]);
    }
    free(preference);

    return 0;
}
