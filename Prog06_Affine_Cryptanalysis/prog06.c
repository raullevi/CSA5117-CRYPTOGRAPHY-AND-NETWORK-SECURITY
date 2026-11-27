#include <stdio.h>
#include <string.h>
#include <ctype.h>

int mod_inverse(int a, int m) {
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 06: AFFINE CIPHER CRYPTANALYSIS\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    printf("[Given Ciphertext Frequency Data]\n");
    printf("Most frequent ciphertext letter    : 'B' -> Value = 1\n");
    printf("2nd Most frequent ciphertext letter: 'U' -> Value = 20\n\n");

    printf("[English Language Frequencies]\n");
    printf("1st Most frequent English letter    : 'E' -> Value = 4\n");
    printf("2nd Most frequent English letter    : 'T' -> Value = 19\n\n");

    printf("[Mathematical Formulation]\n");
    printf("  (1)  4*a + b =  1 (mod 26)   [E -> B]\n");
    printf("  (2) 19*a + b = 20 (mod 26)   [T -> U]\n\n");

    int delta_p = (19 - 4 + 26) % 26; // 15
    int delta_c = (20 - 1 + 26) % 26; // 19

    printf("Subtracting (1) from (2):\n");
    printf("  15*a = 19 (mod 26)\n");

    int inv_15 = mod_inverse(delta_p, 26);
    printf("Multiplicative inverse of 15 mod 26: %d\n", inv_15);

    int a = (delta_c * inv_15) % 26;
    int b = (1 - 4 * a) % 26;
    if (b < 0) b += 26;

    printf("\n[Recovered Key Parameters]\n");
    printf("  Multiplier 'a' = %d\n", a);
    printf("  Shift      'b' = %d\n", b);

    int a_inv = mod_inverse(a, 26);
    printf("  Decryption Multiplier a^-1 = %d\n\n", a_inv);

    printf("[Verification of Recovered Key]\n");
    printf("  E(E = 4)  = (%d * 4 + %d) mod 26  = %d -> '%c' [MATCH 'B']\n", a, b, (a * 4 + b) % 26, (char)(((a * 4 + b) % 26) + 'A'));
    printf("  E(T = 19) = (%d * 19 + %d) mod 26 = %d -> '%c' [MATCH 'U']\n", a, b, (a * 19 + b) % 26, (char)(((a * 19 + b) % 26) + 'A'));

    const char *sample_cipher = "BUBBU";
    printf("\nDecrypting test sequence \"%s\":\n", sample_cipher);
    for (int i = 0; sample_cipher[i] != '\0'; i++) {
        int c = sample_cipher[i] - 'A';
        int p = (a_inv * (c - b + 26)) % 26;
        printf("  '%c' (%d) -> '%c' (%d)\n", sample_cipher[i], c, (char)(p + 'A'), p);
    }

    printf("\nResult: [KEY SUCCESSFULLY RECOVERED: a = %d, b = %d]\n", a, b);
    return 0;
}
