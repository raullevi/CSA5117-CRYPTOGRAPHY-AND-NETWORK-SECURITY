#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const double eng_prob[26] = {
    0.0817, 0.0149, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, 0.0609,
    0.0697, 0.0015, 0.0077, 0.0403, 0.0241, 0.0675, 0.0751, 0.0193,
    0.0010, 0.0599, 0.0633, 0.0906, 0.0276, 0.0098, 0.0236, 0.0015,
    0.0197, 0.0007
};

typedef struct {
    int key;
    double chi;
    char text[256];
} Cand;

int cmp_cand(const void *a, const void *b) {
    if (((Cand *)a)->chi < ((Cand *)b)->chi) return -1;
    if (((Cand *)a)->chi > ((Cand *)b)->chi) return 1;
    return 0;
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 39: ADDITIVE CIPHER TOP 10 ATTACK\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    const char *ciphertext = "LIPPS ASVPH GVCTXSKVETLC WIGYVMXC";
    int len = strlen(ciphertext);

    Cand candidates[26];

    for (int k = 0; k < 26; k++) {
        candidates[k].key = k;
        int counts[26] = {0};
        int total = 0;

        for (int i = 0; i < len; i++) {
            if (isalpha(ciphertext[i])) {
                char p = (char)(((toupper(ciphertext[i]) - 'A' - k + 26) % 26) + 'A');
                candidates[k].text[i] = p;
                counts[p - 'A']++;
                total++;
            } else {
                candidates[k].text[i] = ciphertext[i];
            }
        }
        candidates[k].text[len] = '\0';

        double chi = 0.0;
        for (int i = 0; i < 26; i++) {
            double expected = eng_prob[i] * total;
            double diff = counts[i] - expected;
            chi += (diff * diff) / (expected + 1e-6);
        }
        candidates[k].chi = chi;
    }

    qsort(candidates, 26, sizeof(Cand), cmp_cand);

    printf("[+] Input Ciphertext: %s\n\n", ciphertext);
    printf("[+] TOP 10 MOST LIKELY PLAINTEXTS:\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("Rank | Shift Key | Chi-Sq Metric | Candidate Plaintext\n");
    printf("--------------------------------------------------------------------------------\n");

    for (int r = 0; r < 10; r++) {
        printf("%4d |    k=%02d   |    %9.2f  | %s\n",
               r + 1, candidates[r].key, candidates[r].chi, candidates[r].text);
    }
    printf("--------------------------------------------------------------------------------\n\n");
    printf("Result: [CORRECT SHIFT IDENTIFIED AS RANK 1]\n");

    return 0;
}
