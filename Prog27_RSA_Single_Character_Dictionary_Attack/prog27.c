#include <stdio.h>
#include <string.h>
#include <ctype.h>

long long mod_exp(long long base, long long exp, long long mod) {
    long long res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 27: RSA CHARACTER DICTIONARY ATTACK\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    long long n = 10403; // Large modulus (p=101, q=103)
    long long e = 31;

    printf("[TARGET SETUP]\n");
    printf("  Public Modulus n = %lld\n", n);
    printf("  Public Exp     e = %lld\n\n", e);

    const char *secret_msg = "CONFIDENTIAL";
    int msg_len = strlen(secret_msg);

    long long ciphertext[32];
    printf("[ALICE'S INSECURE ENCRYPTION]\n");
    for (int i = 0; i < msg_len; i++) {
        long long m = toupper(secret_msg[i]) - 'A';
        ciphertext[i] = mod_exp(m, e, n);
        printf("  '%c' (%02lld) -> C = %lld\n", secret_msg[i], m, ciphertext[i]);
    }
    printf("\n");

    printf("[EVE'S PRECOMPUTED DICTIONARY ATTACK (26 Exponentiations)]\n");
    long long dict[26];
    for (int m = 0; m < 26; m++) {
        dict[m] = mod_exp(m, e, n);
    }
    printf("  Dictionary of 26 symbols precomputed in < 1 millisecond.\n\n");

    printf("[EVE RECOVERS SECRET MESSAGE VIA DIRECT LOOKUP]\n");
    char cracked[32];
    for (int i = 0; i < msg_len; i++) {
        long long c = ciphertext[i];
        char found = '?';
        for (int m = 0; m < 26; m++) {
            if (dict[m] == c) {
                found = (char)('A' + m);
                break;
            }
        }
        cracked[i] = found;
        printf("  Ciphertext %lld matches Table -> Plaintext '%c'\n", c, found);
    }
    cracked[msg_len] = '\0';

    printf("\nOriginal Message: %s\n", secret_msg);
    printf("Cracked  Message: %s\n\n", cracked);
    printf("Verdict: IS THIS SECURE? -> ABSOLUTELY INSECURE!\n");
    printf("Defense: Use randomized padding like RSA-OAEP before encryption.\n\n");
    printf("Result: [DICTIONARY ATTACK CRACKED ALL CIPHERTEXT CHARACTERS INSTANTLY]\n");

    return 0;
}
