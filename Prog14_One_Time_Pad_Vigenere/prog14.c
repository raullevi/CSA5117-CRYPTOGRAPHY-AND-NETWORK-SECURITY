#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 14: ONE-TIME PAD VIGENERE CIPHER\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    const char *p1 = "sendmoremoney";
    int k1[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int n = strlen(p1);

    printf("[PART A: Encrypt 'send more money']\n");
    printf("Plaintext 1 : %s\n", p1);
    printf("Key Stream  : ");
    for (int i = 0; i < n; i++) printf("%d ", k1[i]);
    printf("\n");

    char ciphertext[32];
    for (int i = 0; i < n; i++) {
        int p_val = p1[i] - 'a';
        int c_val = (p_val + k1[i]) % 26;
        ciphertext[i] = (char)(c_val + 'A');
    }
    ciphertext[n] = '\0';

    printf("Ciphertext  : ");
    for (int i = 0; i < n; i++) printf("%c ", ciphertext[i]);
    printf("(%s)\n\n", ciphertext);

    printf("[PART B: Find Key to Decrypt Ciphertext to 'cash not needed']\n");
    const char *p2 = "cashnotneeded";
    int k2[32];

    for (int i = 0; i < n; i++) {
        int c_val = ciphertext[i] - 'A';
        int p_target = p2[i] - 'a';
        k2[i] = (c_val - p_target + 26) % 26;
    }

    printf("Target Plaintext : %s\n", p2);
    printf("Calculated Key 2 : ");
    for (int i = 0; i < n; i++) printf("%d ", k2[i]);
    printf("\n\n");

    printf("[Verification: Decrypting Ciphertext using Key 2]\n");
    char p2_recovered[32];
    for (int i = 0; i < n; i++) {
        int c_val = ciphertext[i] - 'A';
        int dec_val = (c_val - k2[i] + 26) % 26;
        p2_recovered[i] = (char)(dec_val + 'a');
    }
    p2_recovered[n] = '\0';

    printf("Decrypted with Key 2: %s\n", p2_recovered);
    if (strcmp(p2, p2_recovered) == 0) {
        printf("Result: [SUCCESS - PERFECT SECRECY PROPERTY DEMONSTRATED]\n");
    }
    return 0;
}
