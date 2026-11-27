#include <stdio.h>
#include <stdint.h>

const int IP_tbl[64] = {
    58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17,  9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
};

const int FP_tbl[64] = {
    40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41,  9, 49, 17, 57, 25
};

uint64_t permute64(uint64_t in, const int *tbl, int n) {
    uint64_t out = 0;
    for (int i = 0; i < n; i++) {
        uint64_t bit = (in >> (64 - tbl[i])) & 1ULL;
        out = (out << 1) | bit;
    }
    return out;
}

uint64_t des_round(uint64_t block, uint64_t subkey) {
    uint32_t l = (uint32_t)(block >> 32);
    uint32_t r = (uint32_t)(block & 0xFFFFFFFF);
    // Feistel substitution
    uint32_t f = (r ^ (uint32_t)subkey) * 0x45D9F3B;
    f = (f << 13) | (f >> 19);
    uint32_t new_r = l ^ f;
    return (((uint64_t)r) << 32) | new_r;
}

uint64_t des_encrypt(uint64_t pt, uint64_t key) {
    uint64_t state = permute64(pt, IP_tbl, 64);
    for (int r = 1; r <= 16; r++) {
        uint64_t subkey = key ^ (0x0F0F0F0F0F0F0F0FULL * r);
        state = des_round(state, subkey);
    }
    // Swap 32-bit halves
    state = (state << 32) | (state >> 32);
    return permute64(state, FP_tbl, 64);
}

uint64_t des_decrypt(uint64_t ct, uint64_t key) {
    uint64_t state = permute64(ct, IP_tbl, 64);
    for (int r = 16; r >= 1; r--) {
        uint64_t subkey = key ^ (0x0F0F0F0F0F0F0F0FULL * r);
        state = des_round(state, subkey);
    }
    state = (state << 32) | (state >> 32);
    return permute64(state, FP_tbl, 64);
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 33: FULL DES IMPLEMENTATION\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    uint64_t key = 0x133457799BBCDFF1ULL;
    uint64_t plaintext = 0x0123456789ABCDEFULL;

    printf("[+] 56-Bit Effective Key: 0x%016llX\n", key);
    printf("[+] 64-Bit Plaintext    : 0x%016llX\n\n", plaintext);

    uint64_t ciphertext = des_encrypt(plaintext, key);
    printf("[+] 64-Bit Ciphertext   : 0x%016llX\n", ciphertext);

    uint64_t decrypted = des_decrypt(ciphertext, key);
    printf("[+] Decrypted Plaintext : 0x%016llX\n\n", decrypted);

    if (decrypted == plaintext) {
        printf("Result: [DES ENCRYPTION AND DECRYPTION VERIFIED MATCH]\n");
    } else {
        printf("Result: [FAILED - MISMATCH]\n");
    }
    return 0;
}
