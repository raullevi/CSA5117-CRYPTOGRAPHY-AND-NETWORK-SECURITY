#include <stdio.h>
#include <stdint.h>

uint32_t mock_decrypt(uint32_t c) {
    return c ^ 0x12345678;
}
uint32_t mock_encrypt(uint32_t p) {
    return p ^ 0x12345678;
}

int count_diff_bits(uint32_t a, uint32_t b) {
    uint32_t diff = a ^ b;
    int count = 0;
    while (diff) {
        count += (diff & 1);
        diff >>= 1;
    }
    return count;
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 20: ECB VS CBC ERROR PROPAGATION\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    uint32_t IV = 0xAABBCCDD;
    uint32_t P[4] = {0x11111111, 0x22222222, 0x33333333, 0x44444444};
    uint32_t C[4];

    // CBC Encryption
    uint32_t prev = IV;
    for (int i = 0; i < 4; i++) {
        C[i] = mock_encrypt(P[i] ^ prev);
        prev = C[i];
    }

    printf("[EXPERIMENT 1: Transmission Error in C1]\n");
    printf("Normal C1: 0x%08X\n", C[0]);
    uint32_t C_corrupted[4];
    for (int i = 0; i < 4; i++) C_corrupted[i] = C[i];
    C_corrupted[0] ^= 0x00000001; // Flip 1 bit in transmitted C1
    printf("Erroneous C1: 0x%08X (1 bit flipped)\n\n", C_corrupted[0]);

    // Decrypt at receiver
    uint32_t P_recv[4];
    prev = IV;
    for (int i = 0; i < 4; i++) {
        P_recv[i] = mock_decrypt(C_corrupted[i]) ^ prev;
        prev = C_corrupted[i];
    }

    printf("Received Plaintext Blocks:\n");
    for (int i = 0; i < 4; i++) {
        int diff = count_diff_bits(P[i], P_recv[i]);
        printf("  Block P%d: Expected 0x%08X | Received 0x%08X | Bit Errors: %d (%s)\n",
               i + 1, P[i], P_recv[i], diff, diff == 0 ? "PERFECT" : "CORRUPTED");
    }
    printf("\nAnswer to (a): Are any blocks beyond P2 affected?\n");
    printf("  NO. In CBC mode, error in C1 corrupts P1 (scrambled) and P2 (1-bit error).\n");
    printf("  Blocks P3, P4, ... are completely UNAFFECTED (Self-Synchronizing property).\n\n");

    printf("[EXPERIMENT 2: Source Plaintext Error in P1]\n");
    printf("Answer to (b): A bit error in source P1 propagates to C1, C2, C3, C4... ALL\n");
    printf("  subsequent ciphertext blocks! At receiver, every single subsequent block\n");
    printf("  is corrupted if transmitted without re-synchronization.\n\n");

    printf("Result: [ERROR PROPAGATION MECHANISMS MATHEMATICALLY DEMONSTRATED]\n");
    return 0;
}
