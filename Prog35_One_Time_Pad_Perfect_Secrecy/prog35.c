#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 35: ONE-TIME PAD PERFECT SECRECY\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    const char *orig_plain = "ATTACKATDAWN";
    int orig_key[12] = {3, 19, 5, 22, 11, 8, 14, 2, 20, 7, 15, 1};
    int len = strlen(orig_plain);

    char ciphertext[16];
    printf("[+] Step 1: Encryption with Random Keystream\n");
    printf("Plaintext : %s\n", orig_plain);
    printf("Keystream : ");
    for (int i = 0; i < len; i++) printf("%d ", orig_key[i]);
    printf("\n");

    for (int i = 0; i < len; i++) {
        int p = orig_plain[i] - 'A';
        int c = (p + orig_key[i]) % 26;
        ciphertext[i] = (char)(c + 'A');
    }
    ciphertext[len] = '\0';
    printf("Ciphertext: %s\n\n", ciphertext);

    printf("[+] Step 2: Perfect Secrecy Demonstration (Shannon Equi-Probability)\n");
    printf("Given Ciphertext \"%s\", an adversary tests different possible plaintexts:\n\n", ciphertext);

    const char *candidates[3] = {
        "DONOTSTRIKE",
        "RETREATATSIX",
        "ATTACKATDAWN"
    };

    for (int c_idx = 0; c_idx < 3; c_idx++) {
        const char *cand = candidates[c_idx];
        printf("  Hypothetical Plaintext: \"%s\"\n  Required Valid Keystream: ", cand);
        for (int i = 0; i < len; i++) {
            int c_val = ciphertext[i] - 'A';
            int p_val = cand[i] - 'A';
            int k_needed = (c_val - p_val + 26) % 26;
            printf("%d ", k_needed);
        }
        printf("(Equally Probable: P(K) = 1/26^%d)\n\n", len);
    }

    printf("Theoretical Proof:\n");
    printf("  H(M | C) = H(M) -> Conditional entropy equals unconditioned entropy.\n");
    printf("  Intercepting the ciphertext yields zero information about the true plaintext.\n\n");
    printf("Result: [PERFECT SECRECY MATHEMATICALLY DEMONSTRATED]\n");

    return 0;
}
