#include <stdio.h>

// Standard DES Permuted Choice 2 (PC-2) table (1-indexed bits 1 to 56)
const int PC2[48] = {
    14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 18: DES SUBKEY BIT INDEPENDENCE\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    printf("[+] Formal Structure of DES Subkey Schedule:\n");
    printf("    PC-1 splits the 56-bit key into two 28-bit disjoint halves:\n");
    printf("      C_i : Bits [ 1 .. 28 ]\n");
    printf("      D_i : Bits [ 29 .. 56 ]\n\n");

    printf("[+] Verifying First 24 Bits of Subkey (Left Half):\n    Bits: ");
    int left_valid = 1;
    for (int i = 0; i < 24; i++) {
        printf("%d ", PC2[i]);
        if (PC2[i] < 1 || PC2[i] > 28) left_valid = 0;
    }
    printf("\n    Verification: %s (All bits strictly in range [1, 28])\n\n", left_valid ? "PASSED" : "FAILED");

    printf("[+] Verifying Second 24 Bits of Subkey (Right Half):\n    Bits: ");
    int right_valid = 1;
    for (int i = 24; i < 48; i++) {
        printf("%d ", PC2[i]);
        if (PC2[i] < 29 || PC2[i] > 56) right_valid = 0;
    }
    printf("\n    Verification: %s (All bits strictly in range [29, 56])\n\n", right_valid ? "PASSED" : "FAILED");

    printf("[+] Set-Theoretic Disjoint Independence:\n");
    printf("    Let Left_Bits  = { PC2[0] .. PC2[23] } subset of C_i\n");
    printf("    Let Right_Bits = { PC2[24] .. PC2[47] } subset of D_i\n");
    printf("    Left_Bits INTERSECTION Right_Bits = EMPTY SET (Phi)\n");
    printf("    No bit from C_i ever enters the right 24 bits of any subkey.\n");
    printf("    No bit from D_i ever enters the left 24 bits of any subkey.\n\n");

    if (left_valid && right_valid) {
        printf("Result: [STRUCTURAL BIT INDEPENDENCE RIGOROUSLY PROVEN]\n");
    }
    return 0;
}
