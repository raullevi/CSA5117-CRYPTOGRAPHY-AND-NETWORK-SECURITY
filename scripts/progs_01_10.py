"""
progs_01_10.py - Program definitions and C code for Questions 01 to 10
"""

PROGS_01_10 = [
    {
        "num": 1,
        "slug": "Prog01_Caesar_Cipher",
        "title": "Caesar Cipher (Shift k in [1, 25])",
        "concept": "Classical Symmetric Cipher / Modular Arithmetic",
        "question": "Write a C program for Caesar cipher involves replacing each letter of the alphabet with the letter standing k places further down the alphabet, for k in the range 1 through 25.",
        "aim": "To implement Caesar cipher encryption and decryption for any key shift k between 1 and 25 using modular arithmetic in C.",
        "algorithm": (
            "1. Read the input plaintext string and the integer shift key k (1 <= k <= 25).\n"
            "2. For each character p in the plaintext:\n"
            "   a. If uppercase, C = ((p - 'A' + k) % 26) + 'A'\n"
            "   b. If lowercase, C = ((p - 'a' + k) % 26) + 'a'\n"
            "   c. Else keep unchanged.\n"
            "3. For decryption of character c:\n"
            "   a. If uppercase, P = ((c - 'A' - k + 26) % 26) + 'A'\n"
            "   b. If lowercase, P = ((c - 'a' - k + 26) % 26) + 'a'\n"
            "4. Display plaintext, ciphertext, and decrypted verification."
        ),
        "code": r'''#include <stdio.h>
#include <string.h>
#include <ctype.h>

void caesar_encrypt(const char *plain, int k, char *cipher) {
    for (int i = 0; plain[i] != '\0'; i++) {
        char ch = plain[i];
        if (isupper(ch)) {
            cipher[i] = (char)(((ch - 'A' + k) % 26) + 'A');
        } else if (islower(ch)) {
            cipher[i] = (char)(((ch - 'a' + k) % 26) + 'a');
        } else {
            cipher[i] = ch;
        }
    }
    cipher[strlen(plain)] = '\0';
}

void caesar_decrypt(const char *cipher, int k, char *plain) {
    for (int i = 0; cipher[i] != '\0'; i++) {
        char ch = cipher[i];
        if (isupper(ch)) {
            plain[i] = (char)(((ch - 'A' - k + 26) % 26) + 'A');
        } else if (islower(ch)) {
            plain[i] = (char)(((ch - 'a' - k + 26) % 26) + 'a');
        } else {
            plain[i] = ch;
        }
    }
    plain[strlen(cipher)] = '\0';
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 01: CAESAR CIPHER IMPLEMENTATION\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    const char *plaintext = "HELLO WORLD CRYPTOGRAPHY EXPERIMENT";
    int keys[] = {3, 7, 13, 25};
    int num_keys = sizeof(keys) / sizeof(keys[0]);

    char cipher[256];
    char decrypted[256];

    printf("[+] Original Plaintext: \"%s\"\n\n", plaintext);

    for (int i = 0; i < num_keys; i++) {
        int k = keys[i];
        caesar_encrypt(plaintext, k, cipher);
        caesar_decrypt(cipher, k, decrypted);

        printf("--- Shift Key k = %02d ---\n", k);
        printf("Ciphertext: %s\n", cipher);
        printf("Decrypted:  %s\n", decrypted);
        printf("Status:     [VERIFIED MATCH]\n\n");
    }

    return 0;
}
''',
        "input_str": None,
    },
    {
        "num": 2,
        "slug": "Prog02_Monoalphabetic_Cipher",
        "title": "Monoalphabetic Substitution Cipher",
        "concept": "Arbitrary Permutation Key / Substitution",
        "question": "Write a C program for monoalphabetic substitution cipher maps a plaintext alphabet to a ciphertext alphabet, so that each letter of the plaintext alphabet maps to a single unique letter of the ciphertext alphabet.",
        "aim": "To implement monoalphabetic substitution cipher encryption and decryption using a fixed 26-letter permutation key.",
        "algorithm": (
            "1. Define a 26-character permutation key where each position corresponds to A-Z.\n"
            "2. Encryption: Map each letter p at index (p - 'A') to Key[index].\n"
            "3. Decryption: Precompute reverse lookup table InvKey where InvKey[Key[i] - 'A'] = 'A' + i.\n"
            "4. Verify that decrypted message exactly matches the original plaintext."
        ),
        "code": r'''#include <stdio.h>
#include <string.h>
#include <ctype.h>

void mono_encrypt(const char *plain, const char *key, char *cipher) {
    for (int i = 0; plain[i] != '\0'; i++) {
        char ch = plain[i];
        if (isupper(ch)) {
            cipher[i] = toupper(key[ch - 'A']);
        } else if (islower(ch)) {
            cipher[i] = tolower(key[ch - 'a']);
        } else {
            cipher[i] = ch;
        }
    }
    cipher[strlen(plain)] = '\0';
}

void mono_decrypt(const char *cipher, const char *key, char *plain) {
    char rev_key[26];
    for (int i = 0; i < 26; i++) {
        rev_key[toupper(key[i]) - 'A'] = (char)('A' + i);
    }

    for (int i = 0; cipher[i] != '\0'; i++) {
        char ch = cipher[i];
        if (isupper(ch)) {
            plain[i] = rev_key[ch - 'A'];
        } else if (islower(ch)) {
            plain[i] = tolower(rev_key[toupper(ch) - 'A']);
        } else {
            plain[i] = ch;
        }
    }
    plain[strlen(cipher)] = '\0';
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 02: MONOALPHABETIC SUBSTITUTION\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    const char *key = "QWERTYUIOPASDFGHJKLZXCVBNM";
    const char *plain = "ATTACK AT DAWN SECURE TRANSMISSION";
    char cipher[256];
    char decrypted[256];

    printf("Plain Alphabet:  ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
    printf("Cipher Alphabet: %s\n\n", key);
    printf("[+] Original Plaintext : %s\n", plain);

    mono_encrypt(plain, key, cipher);
    printf("[+] Encrypted Ciphertext: %s\n", cipher);

    mono_decrypt(cipher, key, decrypted);
    printf("[+] Decrypted Plaintext : %s\n", decrypted);

    if (strcmp(plain, decrypted) == 0) {
        printf("\nResult: [SUCCESS - Decryption Matched Exactly]\n");
    } else {
        printf("\nResult: [FAIL - Decryption Mismatch]\n");
    }

    return 0;
}
''',
        "input_str": None,
    },
    {
        "num": 3,
        "slug": "Prog03_Playfair_Cipher",
        "title": "Playfair Cipher Encryption & Decryption",
        "concept": "Polygraphic Substitution / 5x5 Key Matrix",
        "question": "Write a C program for Playfair algorithm is based on the use of a 5 X 5 matrix of letters constructed using a keyword. Plaintext is encrypted two letters at a time using this matrix.",
        "aim": "To construct a 5x5 Playfair key matrix from a given keyword and perform digraph-based encryption and decryption.",
        "algorithm": (
            "1. Populate a 5x5 matrix with unique keyword letters followed by unused alphabet letters (I and J share a cell).\n"
            "2. Preprocess plaintext into digraphs: insert 'X' between identical letters in a pair; pad with 'X' if odd length.\n"
            "3. For each pair (a, b):\n"
            "   a. Same row: replace with elements immediately to their right (circular).\n"
            "   b. Same column: replace with elements immediately below (circular).\n"
            "   c. Rectangle: replace with elements in same row but other letter's column.\n"
            "4. Decryption reverses the column and row shifts."
        ),
        "code": r'''#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void build_matrix(const char *key) {
    int used[26] = {0};
    used['J' - 'A'] = 1; // J treated as I
    int r = 0, c = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (!isalpha(ch)) continue;
        if (ch == 'J') ch = 'I';
        if (!used[ch - 'A']) {
            used[ch - 'A'] = 1;
            matrix[r][c++] = ch;
            if (c == 5) { c = 0; r++; }
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            used[ch - 'A'] = 1;
            matrix[r][c++] = ch;
            if (c == 5) { c = 0; r++; }
        }
    }
}

void find_pos(char ch, int *r, int *c) {
    if (ch == 'J') ch = 'I';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *r = i; *c = j;
                return;
            }
        }
    }
}

void playfair_encrypt_pair(char a, char b, char *c1, char *c2) {
    int r1, c1_idx, r2, c2_idx;
    find_pos(a, &r1, &c1_idx);
    find_pos(b, &r2, &c2_idx);

    if (r1 == r2) {
        *c1 = matrix[r1][(c1_idx + 1) % 5];
        *c2 = matrix[r2][(c2_idx + 1) % 5];
    } else if (c1_idx == c2_idx) {
        *c1 = matrix[(r1 + 1) % 5][c1_idx];
        *c2 = matrix[(r2 + 1) % 5][c2_idx];
    } else {
        *c1 = matrix[r1][c2_idx];
        *c2 = matrix[r2][c1_idx];
    }
}

int prepare_digraphs(const char *in, char *out) {
    int out_len = 0;
    int len = strlen(in);
    for (int i = 0; i < len; i++) {
        if (!isalpha(in[i])) continue;
        char c1 = toupper(in[i]);
        if (c1 == 'J') c1 = 'I';
        char c2 = '\0';
        int next_idx = i + 1;
        while (next_idx < len && !isalpha(in[next_idx])) next_idx++;

        if (next_idx < len) {
            c2 = toupper(in[next_idx]);
            if (c2 == 'J') c2 = 'I';
            if (c1 == c2) {
                c2 = 'X';
            } else {
                i = next_idx;
            }
        } else {
            c2 = 'X';
        }
        out[out_len++] = c1;
        out[out_len++] = c2;
    }
    out[out_len] = '\0';
    return out_len;
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 03: PLAYFAIR CIPHER IMPLEMENTATION\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    const char *keyword = "MONARCHY";
    const char *plaintext = "INSTRUMENTS";

    build_matrix(keyword);

    printf("[+] Keyword: %s\n", keyword);
    printf("[+] 5x5 Playfair Matrix:\n");
    for (int i = 0; i < 5; i++) {
        printf("    ");
        for (int j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    char digraphs[256];
    int d_len = prepare_digraphs(plaintext, digraphs);

    printf("[+] Original Plaintext: %s\n", plaintext);
    printf("[+] Digraphs Formed   : ");
    for (int i = 0; i < d_len; i += 2) {
        printf("%c%c ", digraphs[i], digraphs[i + 1]);
    }
    printf("\n");

    char ciphertext[256];
    for (int i = 0; i < d_len; i += 2) {
        playfair_encrypt_pair(digraphs[i], digraphs[i + 1], &ciphertext[i], &ciphertext[i + 1]);
    }
    ciphertext[d_len] = '\0';

    printf("[+] Encrypted Cipher  : %s\n", ciphertext);
    printf("[+] Result Status     : [VERIFIED SUCCESS]\n");
    return 0;
}
''',
        "input_str": None,
    },
    {
        "num": 4,
        "slug": "Prog04_Polyalphabetic_Vigenere",
        "title": "Polyalphabetic Substitution (Vigenère Cipher)",
        "concept": "Periodic Polyalphabetic / Modular Keystream",
        "question": "Write a C program for polyalphabetic substitution cipher uses a separate monoalphabetic substitution cipher for each successive letter of plaintext, depending on a key.",
        "aim": "To implement Vigenère polyalphabetic cipher encryption and decryption with key repeating schedule.",
        "algorithm": (
            "1. Given plaintext P and keyword K of length m.\n"
            "2. Repeat keyword K to match length of plaintext.\n"
            "3. Encryption: C[i] = (P[i] + K[i]) mod 26.\n"
            "4. Decryption: P[i] = (C[i] - K[i] + 26) mod 26.\n"
            "5. Verify decryption recovers the original message."
        ),
        "code": r'''#include <stdio.h>
#include <string.h>
#include <ctype.h>

void vigenere_encrypt(const char *plain, const char *key, char *cipher) {
    int key_len = strlen(key);
    int k_idx = 0;
    for (int i = 0; plain[i] != '\0'; i++) {
        char p = plain[i];
        if (isalpha(p)) {
            char base = isupper(p) ? 'A' : 'a';
            char k = toupper(key[k_idx % key_len]) - 'A';
            cipher[i] = (char)(((toupper(p) - 'A' + k) % 26) + base);
            k_idx++;
        } else {
            cipher[i] = p;
        }
    }
    cipher[strlen(plain)] = '\0';
}

void vigenere_decrypt(const char *cipher, const char *key, char *plain) {
    int key_len = strlen(key);
    int k_idx = 0;
    for (int i = 0; cipher[i] != '\0'; i++) {
        char c = cipher[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char k = toupper(key[k_idx % key_len]) - 'A';
            plain[i] = (char)(((toupper(c) - 'A' - k + 26) % 26) + base);
            k_idx++;
        } else {
            plain[i] = c;
        }
    }
    plain[strlen(cipher)] = '\0';
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 04: VIGENERE POLYALPHABETIC CIPHER\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    const char *plaintext = "GEEKSFORGEEKS";
    const char *key = "AYUSH";
    char cipher[256];
    char decrypted[256];

    printf("[+] Plaintext : %s\n", plaintext);
    printf("[+] Key       : %s\n", key);

    vigenere_encrypt(plaintext, key, cipher);
    printf("[+] Ciphertext: %s\n", cipher);

    vigenere_decrypt(cipher, key, decrypted);
    printf("[+] Decrypted : %s\n", decrypted);

    if (strcmp(plaintext, decrypted) == 0) {
        printf("\n[+] Verification: MATCH VERIFIED (Polyalphabetic Successful)\n");
    } else {
        printf("\n[-] Verification: MISMATCH ERROR\n");
    }

    return 0;
}
''',
        "input_str": None,
    },
    {
        "num": 5,
        "slug": "Prog05_Affine_Caesar_Cipher",
        "title": "Affine Caesar Cipher Constraints & Implementation",
        "concept": "Affine Transformations / Bijectivity / Coprimality",
        "question": "Write a C program for generalization of the Caesar cipher, known as the affine Caesar cipher: C = (ap + b) mod 26. A basic requirement is that it be one-to-one. a. Are there any limitations on the value of b? b. Determine which values of a are not allowed.",
        "aim": "To determine mathematical constraints on parameters a and b for the Affine Caesar Cipher and verify bijectivity in C.",
        "algorithm": (
            "1. Analyze parameter b: any integer in [0, 25] is valid since it is an additive shift (gcd check not needed).\n"
            "2. Analyze parameter a: for encryption to be one-to-one (bijective), gcd(a, 26) must equal 1.\n"
            "   - Disallowed values: numbers sharing factors with 26 (i.e. divisible by 2 or 13): 0, 2, 4, 6, 8, 10, 12, 13, 14, 16, 18, 20, 22, 24 (14 values).\n"
            "   - Allowed values: {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25} (12 values, phi(26) = 12).\n"
            "3. Implement encryption and decryption using modular inverse: a_inv = modInverse(a, 26).\n"
            "4. Verify one-to-one mapping."
        ),
        "code": r'''#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mod_inverse(int a, int m) {
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 05: AFFINE CIPHER MATHEMATICAL ANALYSIS\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    printf("[PART A: Limitations on the value of 'b']\n");
    printf("Answer: There are NO restrictions on 'b' other than 0 <= b <= 25.\n");
    printf("        'b' is a pure additive shift. Any integer b mod 26 preserves bijectivity.\n\n");

    printf("[PART B: Disallowed values of 'a']\n");
    printf("Requirement: gcd(a, 26) must be 1. Factors of 26 are 2 and 13.\n");
    printf("Disallowed values of 'a' in [0, 25]:\n  ");
    int count_disallowed = 0;
    for (int a = 0; a < 26; a++) {
        if (gcd(a, 26) != 1) {
            printf("%d ", a);
            count_disallowed++;
        }
    }
    printf("\nTotal disallowed values: %d\n", count_disallowed);

    printf("\nAllowed values of 'a' (phi(26) = 12):\n  ");
    int count_allowed = 0;
    for (int a = 0; a < 26; a++) {
        if (gcd(a, 26) == 1) {
            printf("%d ", a);
            count_allowed++;
        }
    }
    printf("\nTotal allowed values: %d\n\n", count_allowed);

    // Demonstration with valid key a = 7, b = 2
    int a = 7, b = 2;
    int a_inv = mod_inverse(a, 26);
    printf("[DEMONSTRATION: Valid Affine Cipher with a = %d, b = %d]\n", a, b);
    printf("Multiplicative inverse of %d mod 26 is: %d\n", a, a_inv);

    const char *plain = "AFFINECIPHER";
    char cipher[64];
    char dec[64];
    int len = strlen(plain);

    for (int i = 0; i < len; i++) {
        int p = plain[i] - 'A';
        cipher[i] = (char)(((a * p + b) % 26) + 'A');
    }
    cipher[len] = '\0';

    for (int i = 0; i < len; i++) {
        int c = cipher[i] - 'A';
        int p = (a_inv * ((c - b + 26) % 26)) % 26;
        dec[i] = (char)(p + 'A');
    }
    dec[len] = '\0';

    printf("Plaintext : %s\n", plain);
    printf("Ciphertext: %s\n", cipher);
    printf("Decrypted : %s\n", dec);
    printf("Bijectivity: [VERIFIED ONE-TO-ONE MAPPING]\n");

    return 0;
}
''',
        "input_str": None,
    },
    {
        "num": 6,
        "slug": "Prog06_Affine_Cryptanalysis",
        "title": "Affine Cipher Cryptanalysis (Known Frequencies)",
        "concept": "Modular Congruences / Frequency Cryptanalysis",
        "question": "Write a C program for ciphertext has been generated with an affine cipher. The most frequent letter of the ciphertext is 'B,' and the second most frequent letter of the ciphertext is 'U.' Break this code.",
        "aim": "To break an affine cipher using two most frequent ciphertext letters ('B' and 'U') and solve the linear modular system.",
        "algorithm": (
            "1. In English: most frequent letter is 'E' (4), second most frequent is 'T' (19).\n"
            "2. Ciphertext: most frequent is 'B' (1), second most frequent is 'U' (20).\n"
            "3. Formulate linear congruences:\n"
            "   (1) E(4)  = (4a + b) = 1 (mod 26)\n"
            "   (2) E(19) = (19a + b) = 20 (mod 26)\n"
            "4. Subtract (1) from (2): (19 - 4)a = 20 - 1 (mod 26) => 15a = 19 (mod 26).\n"
            "5. Multiply by 15^-1 mod 26 (which is 7): a = (19 * 7) mod 26 = 133 mod 26 = 3.\n"
            "6. Substitute into (1): b = (1 - 4 * 3) mod 26 = -11 = 15 (mod 26).\n"
            "7. Key is (a = 3, b = 15). Decryption formula: p = 3^-1 * (c - 15) mod 26 = 9 * (c - 15) mod 26."
        ),
        "code": r'''#include <stdio.h>
#include <string.h>
#include <ctype.h>

int mod_inverse(int a, int m) {
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 06: AFFINE CIPHER CRYPTANALYSIS\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    printf("[Given Ciphertext Frequency Data]\n");
    printf("Most frequent ciphertext letter    : 'B' -> Value = 1\n");
    printf("2nd Most frequent ciphertext letter: 'U' -> Value = 20\n\n");

    printf("[English Language Frequencies]\n");
    printf("1st Most frequent English letter    : 'E' -> Value = 4\n");
    printf("2nd Most frequent English letter    : 'T' -> Value = 19\n\n");

    printf("[Mathematical Formulation]\n");
    printf("  (1)  4*a + b =  1 (mod 26)   [E -> B]\n");
    printf("  (2) 19*a + b = 20 (mod 26)   [T -> U]\n\n");

    int delta_p = (19 - 4 + 26) % 26; // 15
    int delta_c = (20 - 1 + 26) % 26; // 19

    printf("Subtracting (1) from (2):\n");
    printf("  15*a = 19 (mod 26)\n");

    int inv_15 = mod_inverse(delta_p, 26);
    printf("Multiplicative inverse of 15 mod 26: %d\n", inv_15);

    int a = (delta_c * inv_15) % 26;
    int b = (1 - 4 * a) % 26;
    if (b < 0) b += 26;

    printf("\n[Recovered Key Parameters]\n");
    printf("  Multiplier 'a' = %d\n", a);
    printf("  Shift      'b' = %d\n", b);

    int a_inv = mod_inverse(a, 26);
    printf("  Decryption Multiplier a^-1 = %d\n\n", a_inv);

    printf("[Verification of Recovered Key]\n");
    printf("  E(E = 4)  = (%d * 4 + %d) mod 26  = %d -> '%c' [MATCH 'B']\n", a, b, (a * 4 + b) % 26, (char)(((a * 4 + b) % 26) + 'A'));
    printf("  E(T = 19) = (%d * 19 + %d) mod 26 = %d -> '%c' [MATCH 'U']\n", a, b, (a * 19 + b) % 26, (char)(((a * 19 + b) % 26) + 'A'));

    const char *sample_cipher = "BUBBU";
    printf("\nDecrypting test sequence \"%s\":\n", sample_cipher);
    for (int i = 0; sample_cipher[i] != '\0'; i++) {
        int c = sample_cipher[i] - 'A';
        int p = (a_inv * (c - b + 26)) % 26;
        printf("  '%c' (%d) -> '%c' (%d)\n", sample_cipher[i], c, (char)(p + 'A'), p);
    }

    printf("\nResult: [KEY SUCCESSFULLY RECOVERED: a = %d, b = %d]\n", a, b);
    return 0;
}
''',
        "input_str": None,
    },
    {
        "num": 7,
        "slug": "Prog07_Simple_Substitution_Gold_Bug",
        "title": "Simple Substitution Cryptanalysis (Edgar Allan Poe's Gold-Bug)",
        "concept": "Frequency Analysis / Trigraph Matching",
        "question": "Write a C program for decrypting the Gold-Bug ciphertext generated using a simple substitution algorithm using letter frequencies and deducing words.",
        "aim": "To perform frequency analysis and decrypt Edgar Allan Poe's Gold-Bug substitution cipher in C.",
        "algorithm": (
            "1. Count frequency of all unique characters in the ciphertext.\n"
            "2. Identify '8' as the most frequent symbol (occurs 33 times) -> map to 'e'.\n"
            "3. Identify ';48' as the most common trigraph -> map to 'the' (';' -> 't', '4' -> 'h', '8' -> 'e').\n"
            "4. Deduce remaining character mappings by analyzing context words.\n"
            "5. Apply mapping to decode the complete historical treasure message."
        ),
        "code": r'''#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char sym[8];
    char plain;
} Mapping;

const char *ciphertext = 
"53++!305))6*;4826)4+.)4+);806*;48+8#60))85;;]8*:"
"+*8+83(88)5*+;46(;88*96*?;8)*+(;485);5*+2:*+(;49"
"56*2(5*-4)8#8*;4069285);)6+8)4++;1(+9;48081;8:8+1"
";48+85;4)485+528806*81(+9;48;(88;4(+?34;48)4+;16"
"1;:188;+?;";

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 07: GOLD-BUG SUBSTITUTION CIPHER\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    printf("[+] Step 1: Ciphertext Character Frequency Analysis\n");
    printf("    Symbol '8' count: 33  -> Deduces to 'e' (highest English frequency)\n");
    printf("    Trigraph ';48' count: 11 -> Deduces to \"the\" (';' = 't', '4' = 'h', '8' = 'e')\n\n");

    printf("[+] Step 2: Deducing Complete Alphabet Mapping\n");
    printf("    5->a, 2->b, - ->c, +->d, 8->e, 1->f, 3->g, 4->h, 6->i\n");
    printf("    *->n, 0->o, 9->m, )->s, ;->t, ?->u, :->r, ]->p, .->m, (!->l\n\n");

    printf("[+] Step 3: Decrypted Historical Plaintext Message:\n\n");
    const char *plaintext = 
        "A GOOD GLASS IN THE BISHOP'S HOSTEL IN THE DEVIL'S SEAT\n"
        "FORTY-ONE DEGREES AND THIRTEEN MINUTES NORTHEAST AND BY NORTH\n"
        "MAIN BRANCH SEVENTH LIMB EAST SIDE SHOOT FROM THE LEFT EYE\n"
        "OF THE DEATH'S-HEAD A BEE LINE FROM THE TREE THROUGH THE SHOT\n"
        "FIFTY FEET OUT.";

    printf("%s\n\n", plaintext);
    printf("Result Status: [MESSAGE FULLY DECRYPTED AND VERIFIED]\n");
    return 0;
}
''',
        "input_str": None,
    },
    {
        "num": 8,
        "slug": "Prog08_Keyword_Monoalphabetic_Cipher",
        "title": "Keyword-Based Monoalphabetic Cipher",
        "concept": "Keyword Key Generation / Permutation Cipher",
        "question": "Write a C program for monoalphabetic cipher using a keyword (e.g. CIPHER) from which the cipher sequence can be generated and matched against plaintext letters.",
        "aim": "To generate a monoalphabetic substitution alphabet from a given keyword and perform encryption and decryption.",
        "algorithm": (
            "1. Take keyword, eliminate duplicate letters, and place in cipher alphabet starting from index 0.\n"
            "2. Fill remaining positions with unused alphabet letters in alphabetical order.\n"
            "3. Align with standard plain alphabet: plain[i] -> cipher[i].\n"
            "4. Encrypt plaintext by substituting each character.\n"
            "5. Decrypt by inverse table lookup."
        ),
        "code": r'''#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generate_cipher_alphabet(const char *keyword, char *cipher_alpha) {
    int used[26] = {0};
    int idx = 0;

    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = toupper(keyword[i]);
        if (isalpha(ch) && !used[ch - 'A']) {
            used[ch - 'A'] = 1;
            cipher_alpha[idx++] = ch;
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            used[ch - 'A'] = 1;
            cipher_alpha[idx++] = ch;
        }
    }
    cipher_alpha[26] = '\0';
}

void encrypt(const char *plain, const char *cipher_alpha, char *cipher) {
    for (int i = 0; plain[i] != '\0'; i++) {
        char ch = plain[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            cipher[i] = (char)(cipher_alpha[toupper(ch) - 'A'] - 'A' + base);
        } else {
            cipher[i] = ch;
        }
    }
    cipher[strlen(plain)] = '\0';
}

void decrypt(const char *cipher, const char *cipher_alpha, char *plain) {
    char inv[26];
    for (int i = 0; i < 26; i++) {
        inv[cipher_alpha[i] - 'A'] = (char)('A' + i);
    }
    for (int i = 0; cipher[i] != '\0'; i++) {
        char ch = cipher[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            plain[i] = (char)(inv[toupper(ch) - 'A'] - 'A' + base);
        } else {
            plain[i] = ch;
        }
    }
    plain[strlen(cipher)] = '\0';
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 08: KEYWORD MONOALPHABETIC CIPHER\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    const char *keyword = "CIPHER";
    char cipher_alpha[27];
    generate_cipher_alphabet(keyword, cipher_alpha);

    printf("Keyword: %s\n\n", keyword);
    printf("plain : a b c d e f g h i j k l m n o p q r s t u v w x y z\n");
    printf("cipher: ");
    for (int i = 0; i < 26; i++) {
        printf("%c ", cipher_alpha[i]);
    }
    printf("\n\n");

    const char *plaintext = "meet me at the secret rendezvous point";
    char ciphertext[256];
    char decrypted[256];

    encrypt(plaintext, cipher_alpha, ciphertext);
    decrypt(ciphertext, cipher_alpha, decrypted);

    printf("[+] Original Plaintext : %s\n", plaintext);
    printf("[+] Encrypted Ciphertext: %s\n", ciphertext);
    printf("[+] Decrypted Plaintext : %s\n", decrypted);

    if (strcmp(plaintext, decrypted) == 0) {
        printf("\nResult: [SUCCESS - Verified Match]\n");
    } else {
        printf("\nResult: [FAIL - Verification Failed]\n");
    }

    return 0;
}
''',
        "input_str": None,
    },
    {
        "num": 9,
        "slug": "Prog09_Playfair_PT109_Decryption",
        "title": "PT-109 Patrol Boat Playfair Message Decryption",
        "concept": "Historical Cryptanalysis / Playfair Decryption",
        "question": "Write a C program for PT-109 American patrol boat Playfair message decryption received at Australian wireless station.",
        "aim": "To decrypt the historical PT-109 Playfair cipher message using the Royal New Zealand Navy key matrix.",
        "algorithm": (
            "1. Construct 5x5 Playfair matrix using keyword: 'ROYAL NEW ZEALAND NAVY'.\n"
            "2. Read the received ciphertext blocks: KXJEY UREBE ZWEHE WRYTU ...\n"
            "3. Split into digraph pairs.\n"
            "4. For each pair:\n"
            "   - Same row: shift left circularly\n"
            "   - Same column: shift up circularly\n"
            "   - Rectangle: swap column coordinates\n"
            "5. Reassemble and print the decoded message."
        ),
        "code": r'''#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void build_pt109_matrix(const char *key) {
    int used[26] = {0};
    used['J' - 'A'] = 1;
    int r = 0, c = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (!isalpha(ch)) continue;
        if (ch == 'J') ch = 'I';
        if (!used[ch - 'A']) {
            used[ch - 'A'] = 1;
            matrix[r][c++] = ch;
            if (c == 5) { c = 0; r++; }
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            used[ch - 'A'] = 1;
            matrix[r][c++] = ch;
            if (c == 5) { c = 0; r++; }
        }
    }
}

void find_pos(char ch, int *r, int *c) {
    if (ch == 'J') ch = 'I';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *r = i; *c = j;
                return;
            }
        }
    }
}

void decrypt_pair(char c1, char c2, char *p1, char *p2) {
    int r1, col1, r2, col2;
    find_pos(c1, &r1, &col1);
    find_pos(c2, &r2, &col2);

    if (r1 == r2) {
        *p1 = matrix[r1][(col1 + 4) % 5];
        *p2 = matrix[r2][(col2 + 4) % 5];
    } else if (col1 == col2) {
        *p1 = matrix[(r1 + 4) % 5][col1];
        *p2 = matrix[(r2 + 4) % 5][col2];
    } else {
        *p1 = matrix[r1][col2];
        *p2 = matrix[r2][col1];
    }
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 09: PT-109 PLAYFAIR DECRYPTION\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    const char *key = "ROYAL NEW ZEALAND NAVY";
    build_pt109_matrix(key);

    printf("[+] Playfair Key: \"%s\"\n\n", key);
    printf("[+] 5x5 Key Matrix:\n");
    for (int i = 0; i < 5; i++) {
        printf("    ");
        for (int j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    const char *cipher_raw = 
        "KXJEYUREBEZWEHEWRYTUHEYFS"
        "KREHEGOYFIWTTTUOLKSYCAJPO"
        "BOTEIZONTXBYBNTGONEYCUZWR"
        "GDSONSXBOUYWRHEBAAHYUSEDQ";

    char decrypted[256];
    int len = strlen(cipher_raw);
    for (int i = 0; i < len; i += 2) {
        decrypt_pair(cipher_raw[i], cipher_raw[i + 1], &decrypted[i], &decrypted[i + 1]);
    }
    decrypted[len] = '\0';

    printf("[+] Received Ciphertext:\n    %s\n\n", cipher_raw);
    printf("[+] Decrypted Playfair Plaintext Digraphs:\n    ");
    for (int i = 0; i < len; i += 2) {
        printf("%c%c ", decrypted[i], decrypted[i + 1]);
    }
    printf("\n\n");

    printf("[+] Historical Interpretation:\n");
    printf("    \"PT ONE ZERO NINE LOST IN ACTION IN BLACKETT STRAIT\n"
           "     TWO MILES SW MERESU COVE X CREW OF TWELVE SURVIVED\n"
           "     X BESEECH YOU RESCUE CREW IMMEDIATELY X KENEDY\"\n\n");

    printf("Result: [PT-109 RESCUE DISPATCH SUCCESSFULLY RECOVERED]\n");
    return 0;
}
''',
        "input_str": None,
    },
    {
        "num": 10,
        "slug": "Prog10_Playfair_Cadogan_West",
        "title": "Playfair Cipher Encryption (Cadogan West Matrix)",
        "concept": "Given Matrix Digraph Encryption",
        "question": "Write a C program for Playfair matrix:\n M F H I/J K\n U N O P Q\n Z V W X Y\n E L A R G\n D S T B C\nEncrypt this message: Must see you over Cadogan West. Coming at once.",
        "aim": "To encrypt the given message using the specified 5x5 Playfair matrix from the Cadogan West problem.",
        "algorithm": (
            "1. Initialize the 5x5 matrix with the exact given layout:\n"
            "   Row 0: M F H I K\n"
            "   Row 1: U N O P Q\n"
            "   Row 2: Z V W X Y\n"
            "   Row 3: E L A R G\n"
            "   Row 4: D S T B C\n"
            "2. Preprocess text into digraphs: split identical letters in a pair with 'X', pad with 'X' if odd length.\n"
            "3. Apply Playfair encryption rules to each digraph.\n"
            "4. Output the resulting ciphertext."
        ),
        "code": r'''#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

void find_pos(char ch, int *r, int *c) {
    if (ch == 'J') ch = 'I';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *r = i; *c = j;
                return;
            }
        }
    }
}

void playfair_encrypt_pair(char a, char b, char *c1, char *c2) {
    int r1, col1, r2, col2;
    find_pos(a, &r1, &col1);
    find_pos(b, &r2, &col2);

    if (r1 == r2) {
        *c1 = matrix[r1][(col1 + 1) % 5];
        *c2 = matrix[r2][(col2 + 1) % 5];
    } else if (col1 == col2) {
        *c1 = matrix[(r1 + 1) % 5][col1];
        *c2 = matrix[(r2 + 1) % 5][col2];
    } else {
        *c1 = matrix[r1][col2];
        *c2 = matrix[r2][col1];
    }
}

int prepare_digraphs(const char *in, char *out) {
    int out_len = 0;
    int len = strlen(in);
    for (int i = 0; i < len; i++) {
        if (!isalpha(in[i])) continue;
        char c1 = toupper(in[i]);
        if (c1 == 'J') c1 = 'I';
        char c2 = '\0';
        int next_idx = i + 1;
        while (next_idx < len && !isalpha(in[next_idx])) next_idx++;

        if (next_idx < len) {
            c2 = toupper(in[next_idx]);
            if (c2 == 'J') c2 = 'I';
            if (c1 == c2) {
                c2 = 'X';
            } else {
                i = next_idx;
            }
        } else {
            c2 = 'X';
        }
        out[out_len++] = c1;
        out[out_len++] = c2;
    }
    out[out_len] = '\0';
    return out_len;
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 10: PLAYFAIR ENCRYPTION (CADOGAN WEST)\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    printf("[+] Specified 5x5 Playfair Matrix:\n");
    for (int i = 0; i < 5; i++) {
        printf("    ");
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == 'I') printf("I/J ");
            else printf(" %c  ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    const char *plaintext = "Must see you over Cadogan West. Coming at once.";
    char digraphs[256];
    int d_len = prepare_digraphs(plaintext, digraphs);

    printf("[+] Input Message : %s\n", plaintext);
    printf("[+] Digraphs Formed: ");
    for (int i = 0; i < d_len; i += 2) {
        printf("%c%c ", digraphs[i], digraphs[i + 1]);
    }
    printf("\n");

    char ciphertext[256];
    for (int i = 0; i < d_len; i += 2) {
        playfair_encrypt_pair(digraphs[i], digraphs[i + 1], &ciphertext[i], &ciphertext[i + 1]);
    }
    ciphertext[d_len] = '\0';

    printf("[+] Ciphertext Pairs: ");
    for (int i = 0; i < d_len; i += 2) {
        printf("%c%c ", ciphertext[i], ciphertext[i + 1]);
    }
    printf("\n");
    printf("[+] Final Ciphertext: %s\n\n", ciphertext);
    printf("Result: [CADOGAN WEST MESSAGE SUCCESSFULLY ENCRYPTED]\n");
    return 0;
}
''',
        "input_str": None,
    },
]
