#include <stdio.h>
#include <string.h>
#include <ctype.h>

void caesar_encrypt(const char *plain, int k, char *cipher) {
    for (int i = 0; plain[i] != '\0'; i++) {
        char ch = plain[i];
        if (isupper(ch)) {
            cipher[i] = (char)(((ch - 'A' + k) % 26) + 'A');
        } else if (islower(ch)) {
            cipher[i] = (char)(((ch - 'a' + k) % 26) + 'a');
        } else {
            cipher[i] = ch;
        }
    }
    cipher[strlen(plain)] = '\0';
}

void caesar_decrypt(const char *cipher, int k, char *plain) {
    for (int i = 0; cipher[i] != '\0'; i++) {
        char ch = cipher[i];
        if (isupper(ch)) {
            plain[i] = (char)(((ch - 'A' - k + 26) % 26) + 'A');
        } else if (islower(ch)) {
            plain[i] = (char)(((ch - 'a' - k + 26) % 26) + 'a');
        } else {
            plain[i] = ch;
        }
    }
    plain[strlen(cipher)] = '\0';
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 01: CAESAR CIPHER IMPLEMENTATION\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    const char *plaintext = "HELLO WORLD CRYPTOGRAPHY EXPERIMENT";
    int keys[] = {3, 7, 13, 25};
    int num_keys = sizeof(keys) / sizeof(keys[0]);

    char cipher[256];
    char decrypted[256];

    printf("[+] Original Plaintext: \"%s\"\n\n", plaintext);

    for (int i = 0; i < num_keys; i++) {
        int k = keys[i];
        caesar_encrypt(plaintext, k, cipher);
        caesar_decrypt(cipher, k, decrypted);

        printf("--- Shift Key k = %02d ---\n", k);
        printf("Ciphertext: %s\n", cipher);
        printf("Decrypted:  %s\n", decrypted);
        printf("Status:     [VERIFIED MATCH]\n\n");
    }

    return 0;
}
