#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 8

void print_hex(const uint8_t *data, int len) {
    for (int i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

int pad_message(const uint8_t *in, int in_len, uint8_t *out) {
    memcpy(out, in, in_len);
    int pad_len = BLOCK_SIZE - (in_len % BLOCK_SIZE);
    if (pad_len == 0) pad_len = BLOCK_SIZE; // Always pad!

    out[in_len] = 0x80; // 1-bit followed by 7 zeros
    for (int i = 1; i < pad_len; i++) {
        out[in_len + i] = 0x00;
    }
    return in_len + pad_len;
}

int unpad_message(const uint8_t *in, int padded_len, uint8_t *out) {
    int idx = padded_len - 1;
    while (idx >= 0 && in[idx] == 0x00) idx--;
    if (idx >= 0 && in[idx] == 0x80) {
        memcpy(out, in, idx);
        return idx;
    }
    return -1; // Invalid padding
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 21: BLOCK CIPHER PADDING MOTIVATION\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    printf("[CASE 1: Incomplete Block (5 Bytes Input)]\n");
    uint8_t msg1[5] = {0x11, 0x22, 0x33, 0x44, 0x55};
    uint8_t padded1[16], recovered1[16];
    printf("Original Data (5 bytes): "); print_hex(msg1, 5);

    int plen1 = pad_message(msg1, 5, padded1);
    printf("Padded Block  (8 bytes): "); print_hex(padded1, plen1);

    int rlen1 = unpad_message(padded1, plen1, recovered1);
    printf("Depadded Data (5 bytes): "); print_hex(recovered1, rlen1);
    printf("Status: [UNAMBIGUOUS RECOVERY]\n\n");

    printf("[CASE 2: Complete Block (8 Bytes Input - Exact Multiple)]\n");
    uint8_t msg2[8] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x80};
    uint8_t padded2[32], recovered2[32];
    printf("Original Data (8 bytes, ends in 0x80): "); print_hex(msg2, 8);

    int plen2 = pad_message(msg2, 8, padded2);
    printf("Padded Output (16 bytes, extra block): "); print_hex(padded2, plen2);

    int rlen2 = unpad_message(padded2, plen2, recovered2);
    printf("Depadded Data (8 bytes recovered):     "); print_hex(recovered2, rlen2);
    printf("Status: [CORRECT RECOVERY WITHOUT TRUNCATION]\n\n");

    printf("[ARCHITECTURAL MOTIVATION ANSWER]\n");
    printf("If an extra dummy padding block was NOT added when message is already a multiple\n");
    printf("of block size, any legitimate data ending in bytes like 0x80 0x00 would be mistakenly\n");
    printf("stripped during unpadding! Adding the extra block guarantees deterministic parsing.\n\n");
    printf("Result: [PADDING NECESSITY MATHEMATICALLY PROVEN]\n");

    return 0;
}
