#include <stdio.h>
#include <stdint.h>

const int enc_shifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
const int dec_shifts[16] = {0, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

uint32_t rotl28(uint32_t val, int shift) {
    val &= 0x0FFFFFFF;
    return ((val << shift) | (val >> (28 - shift))) & 0x0FFFFFFF;
}

uint32_t rotr28(uint32_t val, int shift) {
    if (shift == 0) return val & 0x0FFFFFFF;
    val &= 0x0FFFFFFF;
    return ((val >> shift) | (val << (28 - shift))) & 0x0FFFFFFF;
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 17: DES DECRYPTION KEY SCHEDULE\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    uint32_t C0 = 0x0F0F0F0;
    uint32_t D0 = 0x0AAAAAA;

    uint32_t C_enc[17], D_enc[17];
    C_enc[0] = C0; D_enc[0] = D0;

    printf("[+] Step 1: Forward Encryption Key Schedule (Circular Left Shifts)\n");
    printf("Round | Left Shift | C_i (28-bit) | D_i (28-bit)\n");
    printf("------------------------------------------------\n");
    for (int r = 1; r <= 16; r++) {
        C_enc[r] = rotl28(C_enc[r - 1], enc_shifts[r - 1]);
        D_enc[r] = rotl28(D_enc[r - 1], enc_shifts[r - 1]);
        printf(" %2d   |     %d      |  0x%07X   |  0x%07X\n", r, enc_shifts[r - 1], C_enc[r], D_enc[r]);
    }
    printf("\n");

    printf("[+] Step 2: Reverse Decryption Key Schedule (Circular Right Shifts)\n");
    printf("Starting state for decryption: (C16, D16) = (0x%07X, 0x%07X)\n\n", C_enc[16], D_enc[16]);
    printf("Dec Round | Right Shift | Dec C_i   | Expected C_(17-i) | Status\n");
    printf("----------------------------------------------------------------\n");

    uint32_t cur_C = C_enc[16];
    uint32_t cur_D = D_enc[16];
    int all_matched = 1;

    for (int r = 1; r <= 16; r++) {
        cur_C = rotr28(cur_C, dec_shifts[r - 1]);
        cur_D = rotr28(cur_D, dec_shifts[r - 1]);
        int exp_idx = 17 - r;

        int match = (cur_C == C_enc[exp_idx]) && (cur_D == D_enc[exp_idx]);
        if (!match) all_matched = 0;

        printf("   %2d     |      %d      | 0x%07X |     0x%07X      | %s\n",
               r, dec_shifts[r - 1], cur_C, C_enc[exp_idx], match ? "VERIFIED" : "MISMATCH");
    }
    printf("----------------------------------------------------------------\n\n");

    if (all_matched) {
        printf("Result: [DES REVERSE DECRYPTION KEY SCHEDULE PERFECTLY VERIFIED]\n");
    } else {
        printf("Result: [FAILED - SCHEDULE MISMATCH]\n");
    }
    return 0;
}
