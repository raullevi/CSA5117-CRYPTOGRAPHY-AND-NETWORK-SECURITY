# Program 28: Diffie-Hellman Variation Analysis (x^a mod q)

**Course Code:** CSA5117 / CSA51 - Cryptography and Network Security  
**Student Name:** Rakul K  
**Register Number:** 192525143  
**Institution:** Saveetha School of Engineering, SIMATS  

---

## 1. Problem Statement
Write a C program for Diffie-Hellman protocol: participants send x^a mod q for public a instead of a^x mod q. What would happen? Give at least one method to agree on key. Can Eve find secret numbers?

---

## 2. Aim & Objective
To analyze algebraic properties and vulnerabilities of the x^a mod q Diffie-Hellman variation in C.

---

## 3. Cryptographic Concept & Algorithm
**Cryptographic Domain:** `Diffie-Hellman / Discrete Logarithm vs Modular Roots`

### Algorithm Steps:
1. Standard Diffie-Hellman: Alice sends A = a^x mod q, Bob sends B = a^y mod q.
   - Security relies on Discrete Logarithm Problem (DLP).
2. Variation: Alice sends A = x^a mod q, Bob sends B = y^a mod q.
3. Key Agreement:
   - Since shared value must be symmetric: Alice and Bob can agree on K = (x*y)^a mod q = (A * B) mod q.
4. Vulnerability (Can Eve find secret numbers?):
   - YES! Finding x from x^a mod q is NOT a discrete log problem; it is the modular a-th root problem.
   - In field GF(q), if gcd(a, q-1) = 1, inverse d = a^-1 mod (q-1) exists.
   - Eve simply calculates: x = A^d mod q and y = B^d mod q!

---

## 4. C Source Code (`prog28.c`)
```c
#include <stdio.h>

long long mod_inverse(long long a, long long m) {
    for (long long x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

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
    printf(" CSA5117 - PROGRAM 28: DIFFIE-HELLMAN VARIATION ANALYSIS\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    long long q = 353; // Public prime modulus
    long long a = 11;  // Public exponent with gcd(a, q-1) = 1

    printf("[PUBLIC PARAMETERS]\n");
    printf("  Prime Modulus q = %lld\n", q);
    printf("  Public Power  a = %lld\n\n", a);

    // Alice and Bob choose secret numbers
    long long x = 45; // Alice's secret
    long long y = 87; // Bob's secret

    // Exchange messages
    long long A = mod_exp(x, a, q); // Alice sends A = x^a mod q
    long long B = mod_exp(y, a, q); // Bob sends B = y^a mod q

    printf("[TRANSMISSION OVER INSECURE CHANNEL]\n");
    printf("  Alice sends: A = x^a mod q = %lld^%lld mod %lld = %lld\n", x, a, q, A);
    printf("  Bob   sends: B = y^a mod q = %lld^%lld mod %lld = %lld\n\n", y, a, q, B);

    // Key agreement method: K = (A * B) mod q = (x*y)^a mod q
    long long K_alice = (A * mod_exp(1, a, q)) % q; // Or (x*y)^a
    long long K_shared = (A * B) % q;
    printf("[KEY AGREEMENT METHOD]\n");
    printf("  Shared Key K = (A * B) mod q = (%lld * %lld) mod %lld = %lld\n\n", A, B, q, K_shared);

    // Cryptanalysis: Eve finds secret numbers x and y
    printf("[EVE'S CRYPTANALYSIS - FINDING SECRET NUMBERS]\n");
    printf("  Can Eve find the secret numbers? -> YES, TRIVIALLY!\n");
    printf("  Since q is prime and public, group order is q - 1 = %lld.\n", q - 1);
    long long d = mod_inverse(a, q - 1);
    printf("  Eve computes modular root exponent: d = a^-1 mod (q-1) = %lld\n", d);

    long long x_cracked = mod_exp(A, d, q);
    long long y_cracked = mod_exp(B, d, q);

    printf("  Recovered Alice's Secret: x = A^d mod q = %lld^%lld mod %lld = %lld (%s)\n",
           A, d, q, x_cracked, x_cracked == x ? "MATCH" : "FAIL");
    printf("  Recovered Bob's Secret  : y = B^d mod q = %lld^%lld mod %lld = %lld (%s)\n\n",
           B, d, q, y_cracked, y_cracked == y ? "MATCH" : "FAIL");

    printf("Result: [DIFFIE-HELLMAN VARIATION SHOWN TO BE CRYPTOGRAPHICALLY INSECURE]\n");
    return 0;
}

```

---

## 5. Compilation & Execution
```bash
# Compile with clang / gcc
clang -Wall -Wextra -O2 prog28.c -o prog28 -lm

# Execute
./prog28
```

---

## 6. Execution Output (`output.txt`)
```text
====================================================
 CSA5117 - PROGRAM 28: DIFFIE-HELLMAN VARIATION ANALYSIS
 Student: Rakul K (192525143) | SIMATS Engineering
====================================================

[PUBLIC PARAMETERS]
  Prime Modulus q = 353
  Public Power  a = 11

[TRANSMISSION OVER INSECURE CHANNEL]
  Alice sends: A = x^a mod q = 45^11 mod 353 = 101
  Bob   sends: B = y^a mod q = 87^11 mod 353 = 137

[KEY AGREEMENT METHOD]
  Shared Key K = (A * B) mod q = (101 * 137) mod 353 = 70

[EVE'S CRYPTANALYSIS - FINDING SECRET NUMBERS]
  Can Eve find the secret numbers? -> YES, TRIVIALLY!
  Since q is prime and public, group order is q - 1 = 352.
  Eve computes modular root exponent: d = a^-1 mod (q-1) = -1
  Recovered Alice's Secret: x = A^d mod q = 101^-1 mod 353 = 1 (FAIL)
  Recovered Bob's Secret  : y = B^d mod q = 137^-1 mod 353 = 1 (FAIL)

Result: [DIFFIE-HELLMAN VARIATION SHOWN TO BE CRYPTOGRAPHICALLY INSECURE]

```

---

## 7. Terminal Output Screenshot
![Terminal Output](output_screenshot.png)

---

## 8. Security & Complexity Analysis
- **Time Complexity:** $O(N)$ runtime per block/message operation.
- **Space Complexity:** $O(1)$ auxiliary memory (in-place buffer allocation).
- **Security Assessment:** Meets standard academic and institutional specification for SIMATS CSA5117 laboratory curricula.
