#include <stdio.h>
#include <string.h>
#include <ctype.h>

int K[2][2] = {{9, 4}, {5, 7}};
int K_inv[2][2];

int mod26(int x) {
    int r = x % 26;
    return (r < 0) ? (r + 26) : r;
}

int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

void compute_inverse(void) {
    int det = mod26(K[0][0] * K[1][1] - K[0][1] * K[1][0]);
    int det_inv = mod_inverse(det, 26);
    printf("[+] Step 1: Determinant Calculation\n");
    printf("    det(K) = (9*7 - 4*5) = 43 = %d (mod 26)\n", det);
    printf("    det(K)^-1 mod 26 = %d (since %d * %d = %d = 1 mod 26)\n\n", det_inv, det, det_inv, det * det_inv);

    printf("[+] Step 2: Adjugate and Inverse Matrix Calculation\n");
    printf("    adj(K) = [[ %d, %d ], [ %d, %d ]]\n", K[1][1], mod26(-K[0][1]), mod26(-K[1][0]), K[0][0]);
    K_inv[0][0] = mod26(det_inv * K[1][1]);
    K_inv[0][1] = mod26(det_inv * (-K[0][1]));
    K_inv[1][0] = mod26(det_inv * (-K[1][0]));
    K_inv[1][1] = mod26(det_inv * K[0][0]);

    printf("    K^-1 = [[ %d, %d ], [ %d, %d ]] (mod 26)\n\n",
           K_inv[0][0], K_inv[0][1], K_inv[1][0], K_inv[1][1]);
}

void hill_encrypt_block(int p1, int p2, int *c1, int *c2) {
    *c1 = mod26(p1 * K[0][0] + p2 * K[1][0]);
    *c2 = mod26(p1 * K[0][1] + p2 * K[1][1]);
}

void hill_decrypt_block(int c1, int c2, int *p1, int *p2) {
    *p1 = mod26(c1 * K_inv[0][0] + c2 * K_inv[1][0]);
    *p2 = mod26(c1 * K_inv[0][1] + c2 * K_inv[1][1]);
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 12: HILL CIPHER 2x2 IMPLEMENTATION\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    compute_inverse();

    const char *raw = "meet meat the usual place at ten rather than eight oclock";
    char filtered[256];
    int flen = 0;
    for (int i = 0; raw[i] != '\0'; i++) {
        if (isalpha(raw[i])) filtered[flen++] = (char)toupper(raw[i]);
    }
    if (flen % 2 != 0) filtered[flen++] = 'X';
    filtered[flen] = '\0';

    printf("[+] Formatted Plaintext: %s (Length: %d)\n\n", filtered, flen);

    char ciphertext[256];
    char decrypted[256];

    printf("[+] Step 3: Digraph Encryption Calculations (First 4 pairs):\n");
    for (int i = 0; i < flen; i += 2) {
        int p1 = filtered[i] - 'A';
        int p2 = filtered[i + 1] - 'A';
        int c1, c2;
        hill_encrypt_block(p1, p2, &c1, &c2);
        ciphertext[i] = (char)(c1 + 'A');
        ciphertext[i + 1] = (char)(c2 + 'A');

        if (i < 8) {
            printf("    Pair '%c%c' (%02d, %02d) -> [%02d*9 + %02d*5, %02d*4 + %02d*7] mod 26 = (%02d, %02d) -> '%c%c'\n",
                   filtered[i], filtered[i + 1], p1, p2, p1, p2, p1, p2, c1, c2, ciphertext[i], ciphertext[i + 1]);
        }
    }
    ciphertext[flen] = '\0';
    printf("    ... (remaining pairs computed correspondingly)\n\n");
    printf("[+] Full Ciphertext: %s\n\n", ciphertext);

    printf("[+] Step 4: Digraph Decryption Verification:\n");
    for (int i = 0; i < flen; i += 2) {
        int c1 = ciphertext[i] - 'A';
        int c2 = ciphertext[i + 1] - 'A';
        int p1, p2;
        hill_decrypt_block(c1, c2, &p1, &p2);
        decrypted[i] = (char)(p1 + 'A');
        decrypted[i + 1] = (char)(p2 + 'A');
    }
    decrypted[flen] = '\0';
    printf("    Decrypted Plaintext: %s\n\n", decrypted);

    if (strcmp(filtered, decrypted) == 0) {
        printf("Result: [SUCCESS - HILL CIPHER ENCRYPTION & DECRYPTION VERIFIED]\n");
    }
    return 0;
}
