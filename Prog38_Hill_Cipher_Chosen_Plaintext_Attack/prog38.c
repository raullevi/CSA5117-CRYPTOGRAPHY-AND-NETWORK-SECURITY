#include <stdio.h>

int K_secret[2][2] = {{9, 4}, {5, 7}};

void oracle_encrypt(int p1, int p2, int *c1, int *c2) {
    *c1 = (p1 * K_secret[0][0] + p2 * K_secret[1][0]) % 26;
    *c2 = (p1 * K_secret[0][1] + p2 * K_secret[1][1]) % 26;
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 38: HILL CIPHER CHOSEN PLAINTEXT ATTACK\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    printf("[ATTACK MODEL: CHOSEN PLAINTEXT ORACLE]\n");
    printf("Attacker sends chosen basis vectors to encryption black box:\n\n");

    int c00, c01, c10, c11;

    // Chosen Block 1: 'BA' = (1, 0)
    printf("[+] Step 1: Query Oracle with Basis Vector e1 = (1, 0) ['BA']\n");
    oracle_encrypt(1, 0, &c00, &c01);
    printf("    Oracle returns: C1 = (%d, %d)\n", c00, c01);
    printf("    Mathematical fact: (1, 0) * K = (K00, K01) -> Key Row 0: [%d, %d]\n\n", c00, c01);

    // Chosen Block 2: 'AB' = (0, 1)
    printf("[+] Step 2: Query Oracle with Basis Vector e2 = (0, 1) ['AB']\n");
    oracle_encrypt(0, 1, &c10, &c11);
    printf("    Oracle returns: C2 = (%d, %d)\n", c10, c11);
    printf("    Mathematical fact: (0, 1) * K = (K10, K11) -> Key Row 1: [%d, %d]\n\n", c10, c11);

    int K_cracked[2][2] = {{c00, c01}, {c10, c11}};

    printf("[+] Step 3: Extracted Secret Key Matrix K:\n");
    printf("    K = [[ %d, %d ], [ %d, %d ]]\n\n",
           K_cracked[0][0], K_cracked[0][1], K_cracked[1][0], K_cracked[1][1]);

    int match = (K_cracked[0][0] == K_secret[0][0]) &&
                (K_cracked[0][1] == K_secret[0][1]) &&
                (K_cracked[1][0] == K_secret[1][0]) &&
                (K_cracked[1][1] == K_secret[1][1]);

    if (match) {
        printf("Verification: [KEY MATRIX CRACKED EXACTLY WITH ZERO COMPUTATION]\n");
        printf("Result: [CHOSEN PLAINTEXT ATTACK DEMONSTRATED TOTAL BREAK OF HILL CIPHER]\n");
    }
    return 0;
}
