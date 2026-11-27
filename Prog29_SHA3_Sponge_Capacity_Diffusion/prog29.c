#include <stdio.h>
#include <stdint.h>

#define ROTL64(x, y) (((x) << (y)) | ((x) >> (64 - (y))))

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 29: SHA-3 CAPACITY DIFFUSION\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    printf("[+] SHA-3 SPONGE STATE GEOMETRY (r = 1024 bits, c = 576 bits)\n");
    printf("    Total State = 1600 bits = 25 lanes (5x5 matrix of 64-bit words)\n");
    printf("    Rate     r  = 16 lanes (first 16 lanes of message block P0)\n");
    printf("    Capacity c  =  9 lanes (remaining 9 lanes initialized to 0)\n\n");

    uint64_t state[5][5] = {{0}};

    // Initialize: first 16 lanes nonzero, last 9 lanes zero
    int rate_count = 0;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            if (rate_count < 16) {
                state[x][y] = 0xAAAAAAAAAAAAAAAAULL ^ (rate_count + 1);
                rate_count++;
            } else {
                state[x][y] = 0x0000000000000000ULL; // Capacity lane
            }
        }
    }

    printf("[+] Initial State Matrix (0 = Zero Capacity Lane, Non-Zero = Rate Lane):\n");
    for (int y = 0; y < 5; y++) {
        printf("    Row %d: ", y);
        for (int x = 0; x < 5; x++) {
            printf("%s ", state[x][y] == 0 ? "[0000 ZERO]" : "[NON-ZERO] ");
        }
        printf("\n");
    }
    printf("\n");

    // Apply Step Theta
    uint64_t C[5];
    for (int x = 0; x < 5; x++) {
        C[x] = state[x][0] ^ state[x][1] ^ state[x][2] ^ state[x][3] ^ state[x][4];
    }

    uint64_t D[5];
    for (int x = 0; x < 5; x++) {
        D[x] = C[(x + 4) % 5] ^ ROTL64(C[(x + 1) % 5], 1);
    }

    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            state[x][y] ^= D[x];
        }
    }

    printf("[+] State Matrix AFTER 1 ROUND OF THETA STEP:\n");
    
    for (int y = 0; y < 5; y++) {
        printf("    Row %d: ", y);
        for (int x = 0; x < 5; x++) {
            
            printf("%s ", state[x][y] == 0 ? "[0000 ZERO]" : "[NON-ZERO] ");
        }
        printf("\n");
    }
    printf("\n");

    printf("Analysis Conclusion:\n");
    printf("  How long before all capacity lanes have at least one nonzero bit?\n");
    printf("  ANSWER: EXACTLY 1 ROUND.\n");
    printf("  The Theta (theta) transformation diffuses column parities across all rows,\n");
    printf("  causing every single capacity lane to absorb nonzero bits in the very first round!\n\n");
    printf("Result: [DIFFUSION PROVEN IN EXACTLY 1 ROUND]\n");

    return 0;
}
