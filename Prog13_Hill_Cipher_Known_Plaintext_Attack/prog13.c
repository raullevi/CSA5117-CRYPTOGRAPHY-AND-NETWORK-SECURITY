#include <stdio.h>

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

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 13: HILL CIPHER CRYPTANALYSIS\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    // Secret Key Matrix (unknown to attacker)
    int K_secret[2][2] = {{9, 4}, {5, 7}};

    printf("[PART 1: Known Plaintext Attack (KPA)]\n");
    // Attacker knows plaintext "HILL" -> P = [[7, 8], [11, 11]]
    int P[2][2] = {{7, 8}, {11, 11}};
    int C[2][2];

    // Generate known ciphertext blocks
    for (int i = 0; i < 2; i++) {
        C[i][0] = mod26(P[i][0] * K_secret[0][0] + P[i][1] * K_secret[1][0]);
        C[i][1] = mod26(P[i][0] * K_secret[0][1] + P[i][1] * K_secret[1][1]);
    }

    printf("Known Plaintext Matrix P:  [[ %d, %d ], [ %d, %d ]]\n", P[0][0], P[0][1], P[1][0], P[1][1]);
    printf("Observed Ciphertext Matrix C: [[ %d, %d ], [ %d, %d ]]\n\n", C[0][0], C[0][1], C[1][0], C[1][1]);

    int detP = mod26(P[0][0] * P[1][1] - P[0][1] * P[1][0]);
    int detP_inv = mod_inverse(detP, 26);
    printf("det(P) = %d, det(P)^-1 mod 26 = %d\n", detP, detP_inv);

    int P_inv[2][2];
    P_inv[0][0] = mod26(detP_inv * P[1][1]);
    P_inv[0][1] = mod26(detP_inv * (-P[0][1]));
    P_inv[1][0] = mod26(detP_inv * (-P[1][0]));
    P_inv[1][1] = mod26(detP_inv * P[0][0]);

    int K_recovered[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            K_recovered[i][j] = mod26(P_inv[i][0] * C[0][j] + P_inv[i][1] * C[1][j]);
        }
    }

    printf("Recovered Key Matrix via P^-1 * C:\n");
    printf("  K_rec = [[ %d, %d ], [ %d, %d ]]\n\n",
           K_recovered[0][0], K_recovered[0][1], K_recovered[1][0], K_recovered[1][1]);

    printf("[PART 2: Chosen Plaintext Attack (CPA)]\n");
    printf("Attacker chooses basis vectors (Identity Matrix):\n");
    printf("  Block 1: 'BA' -> (1, 0)\n");
    printf("  Block 2: 'AB' -> (0, 1)\n");
    printf("Since C = I * K mod 26 = K mod 26, the ciphertext directly equals the key!\n");
    printf("  C_block1 = (1*K00 + 0*K10, 1*K01 + 0*K11) = (%d, %d)\n", K_secret[0][0], K_secret[0][1]);
    printf("  C_block2 = (0*K00 + 1*K10, 0*K01 + 1*K11) = (%d, %d)\n\n", K_secret[1][0], K_secret[1][1]);

    printf("Result: [HILL CIPHER COMPLETELY BROKEN UNDER KPA AND CPA]\n");
    return 0;
}
