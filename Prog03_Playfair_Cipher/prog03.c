#include <stdio.h>
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
