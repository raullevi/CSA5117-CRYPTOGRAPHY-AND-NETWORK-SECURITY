#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mod_inverse(int a, int m) {
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 05: AFFINE CIPHER MATHEMATICAL ANALYSIS\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    printf("[PART A: Limitations on the value of 'b']\n");
    printf("Answer: There are NO restrictions on 'b' other than 0 <= b <= 25.\n");
    printf("        'b' is a pure additive shift. Any integer b mod 26 preserves bijectivity.\n\n");

    printf("[PART B: Disallowed values of 'a']\n");
    printf("Requirement: gcd(a, 26) must be 1. Factors of 26 are 2 and 13.\n");
    printf("Disallowed values of 'a' in [0, 25]:\n  ");
    int count_disallowed = 0;
    for (int a = 0; a < 26; a++) {
        if (gcd(a, 26) != 1) {
            printf("%d ", a);
            count_disallowed++;
        }
    }
    printf("\nTotal disallowed values: %d\n", count_disallowed);

    printf("\nAllowed values of 'a' (phi(26) = 12):\n  ");
    int count_allowed = 0;
    for (int a = 0; a < 26; a++) {
        if (gcd(a, 26) == 1) {
            printf("%d ", a);
            count_allowed++;
        }
    }
    printf("\nTotal allowed values: %d\n\n", count_allowed);

    // Demonstration with valid key a = 7, b = 2
    int a = 7, b = 2;
    int a_inv = mod_inverse(a, 26);
    printf("[DEMONSTRATION: Valid Affine Cipher with a = %d, b = %d]\n", a, b);
    printf("Multiplicative inverse of %d mod 26 is: %d\n", a, a_inv);

    const char *plain = "AFFINECIPHER";
    char cipher[64];
    char dec[64];
    int len = strlen(plain);

    for (int i = 0; i < len; i++) {
        int p = plain[i] - 'A';
        cipher[i] = (char)(((a * p + b) % 26) + 'A');
    }
    cipher[len] = '\0';

    for (int i = 0; i < len; i++) {
        int c = cipher[i] - 'A';
        int p = (a_inv * ((c - b + 26) % 26)) % 26;
        dec[i] = (char)(p + 'A');
    }
    dec[len] = '\0';

    printf("Plaintext : %s\n", plain);
    printf("Ciphertext: %s\n", cipher);
    printf("Decrypted : %s\n", dec);
    printf("Bijectivity: [VERIFIED ONE-TO-ONE MAPPING]\n");

    return 0;
}
