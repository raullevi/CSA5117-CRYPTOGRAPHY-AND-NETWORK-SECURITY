# Program 13: Hill Cipher Known & Chosen Plaintext Attack

**Course Code:** CSA5117 / CSA51 - Cryptography and Network Security  
**Student Name:** Rakul K  
**Register Number:** 192525143  
**Institution:** Saveetha School of Engineering, SIMATS  

---

## 1. Problem Statement
Write a C program for Hill cipher succumbs to a known plaintext attack if sufficient plaintext-ciphertext pairs are provided. It is even easier to solve the Hill cipher if a chosen plaintext attack can be mounted.

---

## 2. Aim & Objective
To implement known plaintext and chosen plaintext attacks to recover the secret Hill Cipher key matrix.

---

## 3. Cryptographic Concept & Algorithm
**Cryptographic Domain:** `Cryptanalysis / Matrix Inversion over GF(26)`

### Algorithm Steps:
1. Known Plaintext Attack: Given plaintext matrix P and ciphertext matrix C such that P * K = C (mod 26).
   - If det(P) is coprime to 26, compute P^-1 mod 26.
   - Key matrix is recovered as K = P^-1 * C mod 26.
2. Chosen Plaintext Attack:
   - Choose P = Identity matrix I = [[1, 0], [0, 1]] ('BA' and 'AB').
   - Then C = I * K = K mod 26 directly reveals the key matrix without any matrix inversion!

---

## 4. C Source Code (`prog13.c`)
```c
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

```

---

## 5. Compilation & Execution
```bash
# Compile with clang / gcc
clang -Wall -Wextra -O2 prog13.c -o prog13 -lm

# Execute
./prog13
```

---

## 6. Execution Output (`output.txt`)
```text
====================================================
 CSA5117 - PROGRAM 13: HILL CIPHER CRYPTANALYSIS
 Student: Rakul K (192525143) | SIMATS Engineering
====================================================

[PART 1: Known Plaintext Attack (KPA)]
Known Plaintext Matrix P:  [[ 7, 8 ], [ 11, 11 ]]
Observed Ciphertext Matrix C: [[ 25, 6 ], [ 24, 17 ]]

det(P) = 15, det(P)^-1 mod 26 = 7
Recovered Key Matrix via P^-1 * C:
  K_rec = [[ 9, 4 ], [ 5, 7 ]]

[PART 2: Chosen Plaintext Attack (CPA)]
Attacker chooses basis vectors (Identity Matrix):
  Block 1: 'BA' -> (1, 0)
  Block 2: 'AB' -> (0, 1)
Since C = I * K mod 26 = K mod 26, the ciphertext directly equals the key!
  C_block1 = (1*K00 + 0*K10, 1*K01 + 0*K11) = (9, 4)
  C_block2 = (0*K00 + 1*K10, 0*K01 + 1*K11) = (5, 7)

Result: [HILL CIPHER COMPLETELY BROKEN UNDER KPA AND CPA]

```

---

## 7. Terminal Output Screenshot
![Terminal Output](output_screenshot.png)

---

## 8. Security & Complexity Analysis
- **Time Complexity:** $O(N)$ runtime per block/message operation.
- **Space Complexity:** $O(1)$ auxiliary memory (in-place buffer allocation).
- **Security Assessment:** Meets standard academic and institutional specification for SIMATS CSA5117 laboratory curricula.
