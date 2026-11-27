#include <stdio.h>
#include <string.h>
#include <ctype.h>

void mono_encrypt(const char *plain, const char *key, char *cipher) {
    for (int i = 0; plain[i] != '\0'; i++) {
        char ch = plain[i];
        if (isupper(ch)) {
            cipher[i] = toupper(key[ch - 'A']);
        } else if (islower(ch)) {
            cipher[i] = tolower(key[ch - 'a']);
        } else {
            cipher[i] = ch;
        }
    }
    cipher[strlen(plain)] = '\0';
}

void mono_decrypt(const char *cipher, const char *key, char *plain) {
    char rev_key[26];
    for (int i = 0; i < 26; i++) {
        rev_key[toupper(key[i]) - 'A'] = (char)('A' + i);
    }

    for (int i = 0; cipher[i] != '\0'; i++) {
        char ch = cipher[i];
        if (isupper(ch)) {
            plain[i] = rev_key[ch - 'A'];
        } else if (islower(ch)) {
            plain[i] = tolower(rev_key[toupper(ch) - 'A']);
        } else {
            plain[i] = ch;
        }
    }
    plain[strlen(cipher)] = '\0';
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 02: MONOALPHABETIC SUBSTITUTION\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    const char *key = "QWERTYUIOPASDFGHJKLZXCVBNM";
    const char *plain = "ATTACK AT DAWN SECURE TRANSMISSION";
    char cipher[256];
    char decrypted[256];

    printf("Plain Alphabet:  ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
    printf("Cipher Alphabet: %s\n\n", key);
    printf("[+] Original Plaintext : %s\n", plain);

    mono_encrypt(plain, key, cipher);
    printf("[+] Encrypted Ciphertext: %s\n", cipher);

    mono_decrypt(cipher, key, decrypted);
    printf("[+] Decrypted Plaintext : %s\n", decrypted);

    if (strcmp(plain, decrypted) == 0) {
        printf("\nResult: [SUCCESS - Decryption Matched Exactly]\n");
    } else {
        printf("\nResult: [FAIL - Decryption Mismatch]\n");
    }

    return 0;
}
