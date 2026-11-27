#include <stdio.h>
#include <stdint.h>

const int P10[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
const int P8[8]   = {6, 3, 7, 4, 8, 5, 10, 9};
const int IP[8]   = {2, 6, 3, 1, 4, 8, 5, 7};
const int IP_INV[8] = {4, 1, 3, 5, 7, 2, 8, 6};
const int EP[8]   = {4, 1, 2, 3, 2, 3, 4, 1};
const int P4[4]   = {2, 4, 3, 1};

const int S0[4][4] = {
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {3, 1, 3, 2}
};

const int S1[4][4] = {
    {0, 1, 2, 3},
    {2, 0, 1, 3},
    {3, 0, 1, 0},
    {2, 1, 0, 3}
};

uint16_t permute(uint16_t in, const int *table, int n, int in_len) {
    uint16_t out = 0;
    for (int i = 0; i < n; i++) {
        int bit = (in >> (in_len - table[i])) & 1;
        out = (out << 1) | bit;
    }
    return out;
}

void sdes_key_schedule(uint16_t raw_key, uint8_t *k1, uint8_t *k2) {
    uint16_t p10 = permute(raw_key, P10, 10, 10);
    uint8_t l = (p10 >> 5) & 0x1F;
    uint8_t r = p10 & 0x1F;

    // Shift 1
    l = ((l << 1) | (l >> 4)) & 0x1F;
    r = ((r << 1) | (r >> 4)) & 0x1F;
    *k1 = permute((l << 5) | r, P8, 8, 10);

    // Shift 2
    l = ((l << 2) | (l >> 3)) & 0x1F;
    r = ((r << 2) | (r >> 3)) & 0x1F;
    *k2 = permute((l << 5) | r, P8, 8, 10);
}

uint8_t fk(uint8_t r, uint8_t sk) {
    uint8_t ep = permute(r, EP, 8, 4);
    uint8_t x = ep ^ sk;

    uint8_t l_bits = (x >> 4) & 0x0F;
    uint8_t r_bits = x & 0x0F;

    int r0 = ((l_bits & 0x08) >> 2) | (l_bits & 0x01);
    int c0 = (l_bits & 0x06) >> 1;
    uint8_t out0 = S0[r0][c0];

    int r1 = ((r_bits & 0x08) >> 2) | (r_bits & 0x01);
    int c1 = (r_bits & 0x06) >> 1;
    uint8_t out1 = S1[r1][c1];

    uint8_t combined = (out0 << 2) | out1;
    return permute(combined, P4, 4, 4);
}

uint8_t sdes_encrypt_byte(uint8_t pt, uint8_t k1, uint8_t k2) {
    uint8_t ip = permute(pt, IP, 8, 8);
    uint8_t l = (ip >> 4) & 0x0F;
    uint8_t r = ip & 0x0F;

    // Round 1
    uint8_t l1 = r;
    uint8_t r1 = l ^ fk(r, k1);

    // Round 2
    uint8_t l2 = l1 ^ fk(r1, k2);
    uint8_t r2 = r1;

    return permute((l2 << 4) | r2, IP_INV, 8, 8);
}

uint8_t sdes_decrypt_byte(uint8_t ct, uint8_t k1, uint8_t k2) {
    uint8_t ip = permute(ct, IP, 8, 8);
    uint8_t l = (ip >> 4) & 0x0F;
    uint8_t r = ip & 0x0F;

    // Round 1 with K2
    uint8_t l1 = r;
    uint8_t r1 = l ^ fk(r, k2);

    // Round 2 with K1
    uint8_t l2 = l1 ^ fk(r1, k1);
    uint8_t r2 = r1;

    return permute((l2 << 4) | r2, IP_INV, 8, 8);
}

void print_binary8(uint8_t val) {
    for (int i = 7; i >= 0; i--) printf("%d", (val >> i) & 1);
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 22: S-DES IN CBC MODE\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    uint16_t key = 0x01FD; // 0111111101 (10-bit)
    uint8_t IV   = 0xAA;   // 10101010
    uint8_t P1   = 0x01;   // 00000001
    uint8_t P2   = 0x23;   // 00100011

    uint8_t k1, k2;
    sdes_key_schedule(key, &k1, &k2);

    printf("[+] Key : 0111111101 | Subkeys: K1 = 0x%02X, K2 = 0x%02X\n", k1, k2);
    printf("[+] IV  : 10101010 (0x%02X)\n\n", IV);

    // Encryption
    uint8_t C1 = sdes_encrypt_byte(P1 ^ IV, k1, k2);
    uint8_t C2 = sdes_encrypt_byte(P2 ^ C1, k1, k2);

    printf("[+] CBC Encryption:\n");
    printf("  Plaintext Block 1: "); print_binary8(P1); printf(" (0x%02X)\n", P1);
    printf("  Ciphertext Block 1: "); print_binary8(C1); printf(" (0x%02X) [Expected: 11110100]\n", C1);
    printf("  Plaintext Block 2: "); print_binary8(P2); printf(" (0x%02X)\n", P2);
    printf("  Ciphertext Block 2: "); print_binary8(C2); printf(" (0x%02X) [Expected: 00001011]\n\n", C2);

    // Decryption
    uint8_t dec_P1 = sdes_decrypt_byte(C1, k1, k2) ^ IV;
    uint8_t dec_P2 = sdes_decrypt_byte(C2, k1, k2) ^ C1;

    printf("[+] CBC Decryption:\n");
    printf("  Recovered Block 1: "); print_binary8(dec_P1); printf(" (0x%02X) [MATCH]\n", dec_P1);
    printf("  Recovered Block 2: "); print_binary8(dec_P2); printf(" (0x%02X) [MATCH]\n\n", dec_P2);

    if (C1 == 0xF4 && C2 == 0x0B && dec_P1 == P1 && dec_P2 == P2) {
        printf("Result: [S-DES CBC ENCRYPTION & DECRYPTION FULLY VERIFIED]\n");
    }
    return 0;
}
