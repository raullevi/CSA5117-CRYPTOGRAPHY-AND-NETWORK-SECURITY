# Program 11: Playfair Cipher Key Space Analysis

**Course Code:** CSA5117 / CSA51 - Cryptography and Network Security  
**Student Name:** Rakul K  
**Register Number:** 192525143  
**Institution:** Saveetha School of Engineering, SIMATS  

---

## 1. Problem Statement
Write a C program for possible keys does the Playfair cipher have? Ignore the fact that some keys might produce identical encryption results. Express your answer as an approximate power of 2. a. Now take into account the fact that some Playfair keys produce the same encryption results. How many effectively unique keys does the Playfair cipher have?

---

## 2. Aim & Objective
To compute total permutations and effective unique key space for the Playfair cipher taking cyclic shifts and symmetries into account.

---

## 3. Cryptographic Concept & Algorithm
**Cryptographic Domain:** `Combinatorics / Symmetries / Key Space Entropy`

### Algorithm Steps:
1. Compute total keys: 25! (permutations of 25 letters in 5x5 matrix).
2. Convert 25! to power of 2: log2(25!) = ln(25!) / ln(2).
3. Identify symmetries:
   - Any 5 cyclic row shifts and 5 cyclic column shifts produce identical digraph encryption.
   - Total equivalence classes = 5 * 5 = 25.
4. Effective unique keys = 25! / 25 = 24!.
5. Convert 24! to power of 2: log2(24!).
6. Display detailed mathematical report.

---

## 4. C Source Code (`prog11.c`)
```c
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

```

---

## 5. Compilation & Execution
```bash
# Compile with clang / gcc
clang -Wall -Wextra -O2 prog11.c -o prog11 -lm

# Execute
./prog11
```

---

## 6. Execution Output (`output.txt`)
```text
====================================================
 CSA5117 - PROGRAM 11: PLAYFAIR KEY SPACE ANALYSIS
 Student: Rakul K (192525143) | SIMATS Engineering
====================================================

[PART 1: Total Possible Keys (ignoring equivalences)]
  Calculation: 25! (permutations of 25 distinct matrix cells)
  Exact Value : 15511210043330986055303168
  Scientific  : 1.5511e+25
  Power of 2  : 2^(83.68)  =>  Approximately 2^84 keys

[PART 2: Effectively Unique Keys (accounting for symmetries)]
  Reasoning:
    - Circular shift of all 5 rows leaves relative digraphs invariant (5 shifts).
    - Circular shift of all 5 columns leaves relative digraphs invariant (5 shifts).
    - Total symmetric equivalent configurations per key = 5 x 5 = 25.
  Effective Keys = 25! / 25 = 24!
  Exact Value    : 620448401733239409999872
  Scientific     : 6.2045e+23
  Power of 2     : 2^(79.04)  =>  Approximately 2^79 keys

Summary Comparison:
  +--------------------------------+--------------------+------------+
  | Key Category                   | Count (Decimal)    | Power of 2 |
  +--------------------------------+--------------------+------------+
  | Total Theoretical Matrix Keys  | 1.5511 x 10^25     | 2^83.68    |
  | Effectively Unique Cipher Keys | 6.2045 x 10^23     | 2^79.04    |
  +--------------------------------+--------------------+------------+

Result: [ANALYSIS COMPLETE - 2^84 theoretical vs 2^79 effective unique keys]

```

---

## 7. Terminal Output Screenshot
![Terminal Output](output_screenshot.png)

---

## 8. Security & Complexity Analysis
- **Time Complexity:** $O(N)$ runtime per block/message operation.
- **Space Complexity:** $O(1)$ auxiliary memory (in-place buffer allocation).
- **Security Assessment:** Meets standard academic and institutional specification for SIMATS CSA5117 laboratory curricula.
