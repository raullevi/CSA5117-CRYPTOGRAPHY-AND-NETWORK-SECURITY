#include <stdio.h>
#include <stdint.h>

// Mock block cipher encryption
uint32_t block_encrypt(uint32_t block, uint32_t key) {
    return (block ^ key ^ 0x5A5A5A5A);
}

uint32_t cbc_mac(const uint32_t *blocks, int n, uint32_t key) {
    uint32_t tag = 0;
    for (int i = 0; i < n; i++) {
        tag = block_encrypt(blocks[i] ^ tag, key);
    }
    return tag;
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 30: CBC-MAC EXTENSION ATTACK\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    uint32_t secret_key = 0xCAFEBABE;
    uint32_t X = 0x12345678; // One block message

    printf("[STEP 1: Legitimate One-Block Message]\n");
    printf("  Message Block X1 = 0x%08X\n", X);
    uint32_t T = cbc_mac(&X, 1, secret_key);
    printf("  Authentic Tag  T = MAC(K, X1) = 0x%08X\n\n", T);

    printf("[STEP 2: Adversary Constructs Two-Block Message Without Key]\n");
    uint32_t M2_block2 = X ^ T;
    uint32_t forged_message[2] = {X, M2_block2};
    printf("  Forged Block 1: X           = 0x%08X\n", forged_message[0]);
    printf("  Forged Block 2: X ^ T       = 0x%08X\n\n", forged_message[1]);

    printf("[STEP 3: Receiver Verifies MAC of Forged Message]\n");
    uint32_t forged_tag = cbc_mac(forged_message, 2, secret_key);
    printf("  Computed Tag for Forged Message: 0x%08X\n", forged_tag);
    printf("  Target Tag Predicted by Attacker: 0x%08X\n\n", T);

    if (forged_tag == T) {
        printf("Security Verdict:\n");
        printf("  TAGS MATCH EXACTLY! FORGERY SUCCESSFUL!\n");
        printf("  Adversary produced a valid MAC for a new message M without knowing key K.\n");
        printf("  This proves basic CBC-MAC is insecure for variable-length messages.\n");
        printf("  Mitigation: Use CMAC or include message length in block 1.\n\n");
        printf("Result: [CBC-MAC EXTENSION FORGERY MATHEMATICALLY VERIFIED]\n");
    }
    return 0;
}
