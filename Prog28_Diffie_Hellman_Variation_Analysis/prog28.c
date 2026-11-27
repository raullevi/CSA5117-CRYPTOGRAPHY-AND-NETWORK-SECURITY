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
    // (A * B) % q is the shared key
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
