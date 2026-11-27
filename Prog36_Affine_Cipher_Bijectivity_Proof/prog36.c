#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 36: AFFINE BIJECTIVITY PROOF\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    int b = 3;
    printf("[+] Testing Bijectivity for all 'a' in [0 .. 25] with b = %d:\n\n", b);
    printf("Multiplier a | gcd(a, 26) | Bijective? | First Collision Example\n");
    printf("-------------------------------------------------------------------\n");

    int allowed_count = 0;
    int disallowed_count = 0;

    for (int a = 0; a < 26; a++) {
        int g = gcd(a, 26);
        int seen[26] = {0};
        int p1_coll = -1, p2_coll = -1;
        int is_bijective = 1;

        for (int p = 0; p < 26; p++) {
            int c = (a * p + b) % 26;
            if (seen[c] != 0) {
                is_bijective = 0;
                p1_coll = seen[c] - 1;
                p2_coll = p;
                break;
            }
            seen[c] = p + 1;
        }

        if (is_bijective) {
            allowed_count++;
            printf("     %2d      |     %2d     |   YES      | None (1-to-1 Permutation)\n", a, g);
        } else {
            disallowed_count++;
            printf("     %2d      |     %2d     |   NO       | E(%d) = E(%d) = %d\n",
                   a, g, p1_coll, p2_coll, (a * p1_coll + b) % 26);
        }
    }
    printf("-------------------------------------------------------------------\n\n");

    printf("[SUMMARY OF MATHEMATICAL FINDINGS]\n");
    printf("  Total Allowed Multipliers   : %d  (All 'a' where gcd(a, 26) == 1)\n", allowed_count);
    printf("  Total Disallowed Multipliers: %d  (All 'a' sharing factors with 2 or 13)\n\n", disallowed_count);

    printf("[SPECIAL VERIFICATION: Given Case a = 2, b = 3]\n");
    printf("  E(0)  = (2 * 0 + 3) mod 26  = 3  -> 'D'\n");
    printf("  E(13) = (2 * 13 + 3) mod 26 = 29 mod 26 = 3 -> 'D'\n");
    printf("  Collision Confirmed: Plaintexts 0 ('A') and 13 ('N') both encrypt to 'D'!\n");
    printf("  Decryption is impossible because inverse of 2 mod 26 does not exist.\n\n");

    printf("Result: [BIJECTIVITY THEOREM MATHEMATICALLY AND EXPERIMENTALLY PROVEN]\n");
    return 0;
}
