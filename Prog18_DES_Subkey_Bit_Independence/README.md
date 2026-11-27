# Program 18: DES Subkey Schedule Bit Independence Proof

**Course Code:** CSA5117 / CSA51 - Cryptography and Network Security  
**Student Name:** Rakul K  
**Register Number:** 192525143  
**Institution:** Saveetha School of Engineering, SIMATS  

---

## 1. Problem Statement
Write a C program for DES the first 24 bits of each subkey come from the same subset of 28 bits of the initial key and that the second 24 bits of each subkey come from a disjoint subset of 28 bits of the initial key.

---

## 2. Aim & Objective
To verify that in DES Permuted Choice 2 (PC-2), the left 24 bits come strictly from C and right 24 bits strictly from D.

---

## 3. Cryptographic Concept & Algorithm
**Cryptographic Domain:** `Permuted Choice 2 / Disjoint Bit Allocation`

### Algorithm Steps:
1. Define the standard DES PC-2 permutation table (48 positions).
2. Note that PC-1 maps 56 key bits into C0 (bits 1-28) and D0 (bits 29-56).
3. Examine positions 1 to 24 of PC-2: verify every selected bit index is in [1, 28].
4. Examine positions 25 to 48 of PC-2: verify every selected bit index is in [29, 56].
5. Prove disjoint set independence: Intersection(C_bits, D_bits) = Empty.

---

## 4. C Source Code (`prog18.c`)
```c
#include <stdio.h>

// Standard DES Permuted Choice 2 (PC-2) table (1-indexed bits 1 to 56)
const int PC2[48] = {
    14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 18: DES SUBKEY BIT INDEPENDENCE\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    printf("[+] Formal Structure of DES Subkey Schedule:\n");
    printf("    PC-1 splits the 56-bit key into two 28-bit disjoint halves:\n");
    printf("      C_i : Bits [ 1 .. 28 ]\n");
    printf("      D_i : Bits [ 29 .. 56 ]\n\n");

    printf("[+] Verifying First 24 Bits of Subkey (Left Half):\n    Bits: ");
    int left_valid = 1;
    for (int i = 0; i < 24; i++) {
        printf("%d ", PC2[i]);
        if (PC2[i] < 1 || PC2[i] > 28) left_valid = 0;
    }
    printf("\n    Verification: %s (All bits strictly in range [1, 28])\n\n", left_valid ? "PASSED" : "FAILED");

    printf("[+] Verifying Second 24 Bits of Subkey (Right Half):\n    Bits: ");
    int right_valid = 1;
    for (int i = 24; i < 48; i++) {
        printf("%d ", PC2[i]);
        if (PC2[i] < 29 || PC2[i] > 56) right_valid = 0;
    }
    printf("\n    Verification: %s (All bits strictly in range [29, 56])\n\n", right_valid ? "PASSED" : "FAILED");

    printf("[+] Set-Theoretic Disjoint Independence:\n");
    printf("    Let Left_Bits  = { PC2[0] .. PC2[23] } subset of C_i\n");
    printf("    Let Right_Bits = { PC2[24] .. PC2[47] } subset of D_i\n");
    printf("    Left_Bits INTERSECTION Right_Bits = EMPTY SET (Phi)\n");
    printf("    No bit from C_i ever enters the right 24 bits of any subkey.\n");
    printf("    No bit from D_i ever enters the left 24 bits of any subkey.\n\n");

    if (left_valid && right_valid) {
        printf("Result: [STRUCTURAL BIT INDEPENDENCE RIGOROUSLY PROVEN]\n");
    }
    return 0;
}

```

---

## 5. Compilation & Execution
```bash
# Compile with clang / gcc
clang -Wall -Wextra -O2 prog18.c -o prog18 -lm

# Execute
./prog18
```

---

## 6. Execution Output (`output.txt`)
```text
====================================================
 CSA5117 - PROGRAM 18: DES SUBKEY BIT INDEPENDENCE
 Student: Rakul K (192525143) | SIMATS Engineering
====================================================

[+] Formal Structure of DES Subkey Schedule:
    PC-1 splits the 56-bit key into two 28-bit disjoint halves:
      C_i : Bits [ 1 .. 28 ]
      D_i : Bits [ 29 .. 56 ]

[+] Verifying First 24 Bits of Subkey (Left Half):
    Bits: 14 17 11 24 1 5 3 28 15 6 21 10 23 19 12 4 26 8 16 7 27 20 13 2 
    Verification: PASSED (All bits strictly in range [1, 28])

[+] Verifying Second 24 Bits of Subkey (Right Half):
    Bits: 41 52 31 37 47 55 30 40 51 45 33 48 44 49 39 56 34 53 46 42 50 36 29 32 
    Verification: PASSED (All bits strictly in range [29, 56])

[+] Set-Theoretic Disjoint Independence:
    Let Left_Bits  = { PC2[0] .. PC2[23] } subset of C_i
    Let Right_Bits = { PC2[24] .. PC2[47] } subset of D_i
    Left_Bits INTERSECTION Right_Bits = EMPTY SET (Phi)
    No bit from C_i ever enters the right 24 bits of any subkey.
    No bit from D_i ever enters the left 24 bits of any subkey.

Result: [STRUCTURAL BIT INDEPENDENCE RIGOROUSLY PROVEN]

```

---

## 7. Terminal Output Screenshot
![Terminal Output](output_screenshot.png)

---

## 8. Security & Complexity Analysis
- **Time Complexity:** $O(N)$ runtime per block/message operation.
- **Space Complexity:** $O(1)$ auxiliary memory (in-place buffer allocation).
- **Security Assessment:** Meets standard academic and institutional specification for SIMATS CSA5117 laboratory curricula.
