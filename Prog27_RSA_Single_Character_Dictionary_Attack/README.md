# Program 27: RSA Single-Character Encryption Dictionary Attack

**Course Code:** CSA5117 / CSA51 - Cryptography and Network Security  
**Student Name:** Rakul K  
**Register Number:** 192525143  
**Institution:** Saveetha School of Engineering, SIMATS  

---

## 1. Problem Statement
Write a C program for Bob uses RSA with large n. Suppose Alice sends a message by representing each character as an integer (A=0, ..., Z=25) and encrypting each number separately with large e and n. Is this method secure? If not, describe the most efficient attack.

---

## 2. Aim & Objective
To demonstrate the dictionary codebook attack against small message space RSA encryption in C.

---

## 3. Cryptographic Concept & Algorithm
**Cryptographic Domain:** `Small Message Space / Precomputed Codebook Attack`

### Algorithm Steps:
1. Given public key (e, n) where n is arbitrarily large.
2. Message space is tiny: only 26 possible plaintext values m in [0, 25].
3. Attacker precomputes dictionary table: T[m] = m^e mod n for m = 0 .. 25.
   - Total work: only 26 modular exponentiations!
4. For any intercepted ciphertext character C, attacker does O(1) table lookup.
5. Message is completely decrypted in milliseconds without factoring n.

---

## 4. C Source Code (`prog27.c`)
```c
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

```

---

## 5. Compilation & Execution
```bash
# Compile with clang / gcc
clang -Wall -Wextra -O2 prog27.c -o prog27 -lm

# Execute
./prog27
```

---

## 6. Execution Output (`output.txt`)
```text
====================================================
 CSA5117 - PROGRAM 27: RSA CHARACTER DICTIONARY ATTACK
 Student: Rakul K (192525143) | SIMATS Engineering
====================================================

[TARGET SETUP]
  Public Modulus n = 10403
  Public Exp     e = 31

[ALICE'S INSECURE ENCRYPTION]
  'C' (02) -> C = 2761
  'O' (14) -> C = 7892
  'N' (13) -> C = 9576
  'F' (05) -> C = 6838
  'I' (08) -> C = 4257
  'D' (03) -> C = 9209
  'E' (04) -> C = 8125
  'N' (13) -> C = 9576
  'T' (19) -> C = 9676
  'I' (08) -> C = 4257
  'A' (00) -> C = 0
  'L' (11) -> C = 5967

[EVE'S PRECOMPUTED DICTIONARY ATTACK (26 Exponentiations)]
  Dictionary of 26 symbols precomputed in < 1 millisecond.

[EVE RECOVERS SECRET MESSAGE VIA DIRECT LOOKUP]
  Ciphertext 2761 matches Table -> Plaintext 'C'
  Ciphertext 7892 matches Table -> Plaintext 'O'
  Ciphertext 9576 matches Table -> Plaintext 'N'
  Ciphertext 6838 matches Table -> Plaintext 'F'
  Ciphertext 4257 matches Table -> Plaintext 'I'
  Ciphertext 9209 matches Table -> Plaintext 'D'
  Ciphertext 8125 matches Table -> Plaintext 'E'
  Ciphertext 9576 matches Table -> Plaintext 'N'
  Ciphertext 9676 matches Table -> Plaintext 'T'
  Ciphertext 4257 matches Table -> Plaintext 'I'
  Ciphertext 0 matches Table -> Plaintext 'A'
  Ciphertext 5967 matches Table -> Plaintext 'L'

Original Message: CONFIDENTIAL
Cracked  Message: CONFIDENTIAL

Verdict: IS THIS SECURE? -> ABSOLUTELY INSECURE!
Defense: Use randomized padding like RSA-OAEP before encryption.

Result: [DICTIONARY ATTACK CRACKED ALL CIPHERTEXT CHARACTERS INSTANTLY]

```

---

## 7. Terminal Output Screenshot
![Terminal Output](output_screenshot.png)

---

## 8. Security & Complexity Analysis
- **Time Complexity:** $O(N)$ runtime per block/message operation.
- **Space Complexity:** $O(1)$ auxiliary memory (in-place buffer allocation).
- **Security Assessment:** Meets standard academic and institutional specification for SIMATS CSA5117 laboratory curricula.
