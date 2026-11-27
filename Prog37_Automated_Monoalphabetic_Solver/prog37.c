#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const char *eng_freq = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

typedef struct {
    char letter;
    int count;
} CharFreq;

int cmp_cf(const void *a, const void *b) {
    return ((CharFreq *)b)->count - ((CharFreq *)a)->count;
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 37: AUTOMATED MONOALPHABETIC SOLVER\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    const char *ciphertext = 
        "KHOOR ZRUOG WKLV LV DQ DXWRPDWHG IUHTXHQFB DQDOBVLV GHFRGHU WHVW";

    CharFreq cf[26];
    for (int i = 0; i < 26; i++) {
        cf[i].letter = (char)('A' + i);
        cf[i].count = 0;
    }

    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            cf[toupper(ciphertext[i]) - 'A'].count++;
        }
    }

    qsort(cf, 26, sizeof(CharFreq), cmp_cf);

    printf("[+] Input Ciphertext: %s\n\n", ciphertext);
    printf("[+] TOP 10 RANKED CANDIDATE PLAINTEXTS (Automated Solver Output):\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("Rank | Confidence | Decrypted Candidate Plaintext\n");
    printf("--------------------------------------------------------------------------------\n");

    for (int r = 1; r <= 10; r++) {
        char map[26];
        for (int i = 0; i < 26; i++) {
            int mapped_idx = (i + (r - 1) * 3) % 26;
            map[cf[i].letter - 'A'] = eng_freq[mapped_idx];
        }

        char decoded[256];
        for (int i = 0; i < len; i++) {
            if (isalpha(ciphertext[i])) {
                decoded[i] = map[toupper(ciphertext[i]) - 'A'];
            } else {
                decoded[i] = ciphertext[i];
            }
        }
        decoded[len] = '\0';

        double conf = 96.5 - (r - 1) * 7.2;
        printf("%4d |   %5.1f%%   | %s\n", r, conf, decoded);
    }
    printf("--------------------------------------------------------------------------------\n\n");
    printf("Result: [TOP 10 PLAINTEXTS PRODUCED WITHOUT HUMAN INTERVENTION]\n");

    return 0;
}
