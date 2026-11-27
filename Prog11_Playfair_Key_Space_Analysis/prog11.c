#include <stdio.h>
#include <math.h>

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 11: PLAYFAIR KEY SPACE ANALYSIS\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    // 25! calculation
    double fact25 = 1.0;
    for (int i = 1; i <= 25; i++) fact25 *= i;

    double log2_fact25 = log2(fact25);

    printf("[PART 1: Total Possible Keys (ignoring equivalences)]\n");
    printf("  Calculation: 25! (permutations of 25 distinct matrix cells)\n");
    printf("  Exact Value : %.0f\n", fact25);
    printf("  Scientific  : %.4e\n", fact25);
    printf("  Power of 2  : 2^(%.2f)  =>  Approximately 2^84 keys\n\n", log2_fact25);

    // Symmetries and effectively unique keys
    // Cyclic shifts: 5 row shifts * 5 col shifts = 25 equivalent matrices
    double fact24 = fact25 / 25.0;
    double log2_fact24 = log2(fact24);

    printf("[PART 2: Effectively Unique Keys (accounting for symmetries)]\n");
    printf("  Reasoning:\n");
    printf("    - Circular shift of all 5 rows leaves relative digraphs invariant (5 shifts).\n");
    printf("    - Circular shift of all 5 columns leaves relative digraphs invariant (5 shifts).\n");
    printf("    - Total symmetric equivalent configurations per key = 5 x 5 = 25.\n");
    printf("  Effective Keys = 25! / 25 = 24!\n");
    printf("  Exact Value    : %.0f\n", fact24);
    printf("  Scientific     : %.4e\n", fact24);
    printf("  Power of 2     : 2^(%.2f)  =>  Approximately 2^79 keys\n\n", log2_fact24);

    printf("Summary Comparison:\n");
    printf("  +--------------------------------+--------------------+------------+\n");
    printf("  | Key Category                   | Count (Decimal)    | Power of 2 |\n");
    printf("  +--------------------------------+--------------------+------------+\n");
    printf("  | Total Theoretical Matrix Keys  | 1.5511 x 10^25     | 2^83.68    |\n");
    printf("  | Effectively Unique Cipher Keys | 6.2045 x 10^23     | 2^79.04    |\n");
    printf("  +--------------------------------+--------------------+------------+\n\n");
    printf("Result: [ANALYSIS COMPLETE - 2^84 theoretical vs 2^79 effective unique keys]\n");

    return 0;
}
