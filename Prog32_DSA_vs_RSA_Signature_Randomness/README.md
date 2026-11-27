# Program 32: DSA vs RSA Signature Randomness & Nonce Reuse Vulnerability

**Course Code:** CSA5117 / CSA51 - Cryptography and Network Security  
**Student Name:** Rakul K  
**Register Number:** 192525143  
**Institution:** Saveetha School of Engineering, SIMATS  

---

## 1. Problem Statement
Write a C program for DSA: value of k is generated for each signature, so signing twice gives different signatures; not true of RSA. What is the implication of this difference?

---

## 2. Aim & Objective
To analyze implications of randomness in DSA vs RSA and demonstrate the private key recovery attack when DSA nonce k is reused.

---

## 3. Cryptographic Concept & Algorithm
**Cryptographic Domain:** `Digital Signatures / Ephemeral Nonces / Private Key Leakage`

### Algorithm Steps:
1. In RSA, signature s = H(m)^d mod n is deterministic: identical messages produce identical signatures.
2. In DSA, signature (r, s) uses per-message random nonce k:
   - r = (g^k mod p) mod q
   - s = k^-1 * (H(m) + x * r) mod q
   - Two signatures of same message differ, preventing replay correlation.
3. Catastrophic vulnerability if k is reused for two different messages m1 and m2:
   - s1 - s2 = k^-1 * (H(m1) - H(m2)) mod q
   - Attacker recovers k = (H(m1) - H(m2)) * (s1 - s2)^-1 mod q
   - Attacker recovers private key x = (s1 * k - H(m1)) * r^-1 mod q!

---

## 4. C Source Code (`prog32.c`)
```c
#include <stdio.h>

long long mod_inverse(long long a, long long m) {
    for (long long x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 32: DSA VS RSA SIGNATURE RANDOMNESS\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    printf("[PART 1: Implications of Randomized vs Deterministic Signatures]\n");
    printf("  1. Privacy & Unlinkability:\n");
    printf("     - Deterministic RSA reveals when the exact same message is signed twice.\n");
    printf("     - Randomized DSA produces different signatures every time, preserving unlinkability.\n");
    printf("  2. Nonce Fragility:\n");
    printf("     - RSA requires NO random number generator during signing.\n");
    printf("     - DSA critically relies on a cryptographically secure RNG. If the nonce 'k'\n");
    printf("       is repeated or predictable, the SIGNER'S PRIVATE KEY IS EXPOSED!\n\n");

    printf("[PART 2: Catastrophic Private Key Recovery Attack (Nonce Reuse)]\n");
    long long q = 101;       // Subprime group order
    long long x_secret = 42; // Signer's private key

    long long h1 = 55; // Hash of message 1
    long long h2 = 80; // Hash of message 2
    long long k_reused = 17; // Insecurely reused nonce!
    long long r = 23;        // Public r = (g^k mod p) mod q

    long long k_inv = mod_inverse(k_reused, q);
    long long s1 = (k_inv * (h1 + x_secret * r)) % q;
    long long s2 = (k_inv * (h2 + x_secret * r)) % q;

    printf("Signer generates two signatures with same reused nonce k = %lld:\n", k_reused);
    printf("  Sig 1: (r = %lld, s1 = %lld) for Message Hash %lld\n", r, s1, h1);
    printf("  Sig 2: (r = %lld, s2 = %lld) for Message Hash %lld\n\n", r, s2, h2);

    printf("Attacker intercepts both signatures and mounts nonce recovery:\n");
    long long diff_h = (h1 - h2 + q) % q;
    long long diff_s = (s1 - s2 + q) % q;
    long long diff_s_inv = mod_inverse(diff_s, q);

    long long k_cracked = (diff_h * diff_s_inv) % q;
    printf("  Cracked Nonce k = (H1 - H2) * (s1 - s2)^-1 mod q = %lld\n", k_cracked);

    long long r_inv = mod_inverse(r, q);
    long long x_cracked = (((s1 * k_cracked - h1) % q + q) % q * r_inv) % q;
    printf("  Cracked Private Key x = (s1*k - H1) * r^-1 mod q = %lld\n\n", x_cracked);

    if (x_cracked == x_secret) {
        printf("Result: [PRIVATE KEY CRACKED 100%% - NONCE REUSE PROVEN FATAL]\n");
    }
    return 0;
}

```

---

## 5. Compilation & Execution
```bash
# Compile with clang / gcc
clang -Wall -Wextra -O2 prog32.c -o prog32 -lm

# Execute
./prog32
```

---

## 6. Execution Output (`output.txt`)
```text
====================================================
 CSA5117 - PROGRAM 32: DSA VS RSA SIGNATURE RANDOMNESS
 Student: Rakul K (192525143) | SIMATS Engineering
====================================================

[PART 1: Implications of Randomized vs Deterministic Signatures]
  1. Privacy & Unlinkability:
     - Deterministic RSA reveals when the exact same message is signed twice.
     - Randomized DSA produces different signatures every time, preserving unlinkability.
  2. Nonce Fragility:
     - RSA requires NO random number generator during signing.
     - DSA critically relies on a cryptographically secure RNG. If the nonce 'k'
       is repeated or predictable, the SIGNER'S PRIVATE KEY IS EXPOSED!

[PART 2: Catastrophic Private Key Recovery Attack (Nonce Reuse)]
Signer generates two signatures with same reused nonce k = 17:
  Sig 1: (r = 23, s1 = 66) for Message Hash 55
  Sig 2: (r = 23, s2 = 14) for Message Hash 80

Attacker intercepts both signatures and mounts nonce recovery:
  Cracked Nonce k = (H1 - H2) * (s1 - s2)^-1 mod q = 17
  Cracked Private Key x = (s1*k - H1) * r^-1 mod q = 42

Result: [PRIVATE KEY CRACKED 100% - NONCE REUSE PROVEN FATAL]

```

---

## 7. Terminal Output Screenshot
![Terminal Output](output_screenshot.png)

---

## 8. Security & Complexity Analysis
- **Time Complexity:** $O(N)$ runtime per block/message operation.
- **Space Complexity:** $O(1)$ auxiliary memory (in-place buffer allocation).
- **Security Assessment:** Meets standard academic and institutional specification for SIMATS CSA5117 laboratory curricula.
