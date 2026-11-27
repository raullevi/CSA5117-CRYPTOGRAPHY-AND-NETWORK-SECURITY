#include <stdio.h>
#include <string.h>
#include <ctype.h>

void vigenere_encrypt(const char *plain, const char *key, char *cipher) {
    int key_len = strlen(key);
    int k_idx = 0;
    for (int i = 0; plain[i] != '\0'; i++) {
        char p = plain[i];
        if (isalpha(p)) {
            char base = isupper(p) ? 'A' : 'a';
            char k = toupper(key[k_idx % key_len]) - 'A';
            cipher[i] = (char)(((toupper(p) - 'A' + k) % 26) + base);
            k_idx++;
        } else {
            cipher[i] = p;
        }
    }
    cipher[strlen(plain)] = '\0';
}

void vigenere_decrypt(const char *cipher, const char *key, char *plain) {
    int key_len = strlen(key);
    int k_idx = 0;
    for (int i = 0; cipher[i] != '\0'; i++) {
        char c = cipher[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char k = toupper(key[k_idx % key_len]) - 'A';
            plain[i] = (char)(((toupper(c) - 'A' - k + 26) % 26) + base);
            k_idx++;
        } else {
            plain[i] = c;
        }
    }
    plain[strlen(cipher)] = '\0';
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 04: VIGENERE POLYALPHABETIC CIPHER\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    const char *plaintext = "GEEKSFORGEEKS";
    const char *key = "AYUSH";
    char cipher[256];
    char decrypted[256];

    printf("[+] Plaintext : %s\n", plaintext);
    printf("[+] Key       : %s\n", key);

    vigenere_encrypt(plaintext, key, cipher);
    printf("[+] Ciphertext: %s\n", cipher);

    vigenere_decrypt(cipher, key, decrypted);
    printf("[+] Decrypted : %s\n", decrypted);

    if (strcmp(plaintext, decrypted) == 0) {
        printf("\n[+] Verification: MATCH VERIFIED (Polyalphabetic Successful)\n");
    } else {
        printf("\n[-] Verification: MISMATCH ERROR\n");
    }

    return 0;
}
