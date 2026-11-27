#include <stdio.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

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
    printf(" CSA5117 - PROGRAM 25: RSA COMMON FACTOR ATTACK\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    long long p_actual = 61;
    long long q_actual = 53;
    long long n = p_actual * q_actual; // 3233
    long long e = 17;

    printf("[TARGET SYSTEM]\n");
    printf("  Public Modulus n = %lld\n", n);
    printf("  Public Exp     e = %lld\n\n", e);

    // Suppose a plaintext block P shares a factor with n (e.g. multiple of 61)
    long long P_vulnerable = 61 * 3; // 183
    long long C = mod_exp(P_vulnerable, e, n);

    printf("[ATTACK EXECUTION]\n");
    printf("  Vulnerable Plaintext P = %lld (shares factor with n)\n", P_vulnerable);
    printf("  Observed Ciphertext  C = %lld\n\n", C);

    printf("  Attacker computes: gcd(C, n)...\n");
    long long recovered_p = gcd(C, n);
    long long recovered_q = n / recovered_p;

    printf("  Recovered Prime p = gcd(%lld, %lld) = %lld\n", C, n, recovered_p);
    printf("  Recovered Prime q = n / p = %lld / %lld = %lld\n\n", n, recovered_p, recovered_q);

    long long phi = (recovered_p - 1) * (recovered_q - 1);
    long long d = mod_inverse(e, phi);

    printf("[PRIVATE KEY EXFILTRATION]\n");
    printf("  phi(n) = (%lld - 1) * (%lld - 1) = %lld\n", recovered_p, recovered_q, phi);
    printf("  Attacker-Calculated Private Key d = %lld\n\n", d);

    printf("Answer to Question:\n");
    printf("  YES, IT COMPLETELY BREAKS THE ENTIRE CRYPTOSYSTEM!\n");
    printf("  Computing gcd(C, n) directly factors n in O(log n) steps, yielding p and q,\n");
    printf("  which allows immediate derivation of the victim's private key d.\n\n");
    printf("Result: [COMMON FACTOR VULNERABILITY DEMONSTRATED WITH FULL KEY EXFILTRATION]\n");

    return 0;
}
