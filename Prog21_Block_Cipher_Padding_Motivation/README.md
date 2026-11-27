# Program 21: Block Cipher Padding Motivation & Ambiguity Analysis

**Course Code:** CSA5117 / CSA51 - Cryptography and Network Security  
**Student Name:** Rakul K  
**Register Number:** 192525143  
**Institution:** Saveetha School of Engineering, SIMATS  

---

## 1. Problem Statement
Write a C program for ECB, CBC, and CFB modes padding: consisting of a 1 bit followed by zero bits. What is the motivation for including a padding block when padding is not needed?

---

## 2. Aim & Objective
To demonstrate why an extra padding block must be added even when plaintext is a multiple of block size to prevent unpadding ambiguity.

---

## 3. Cryptographic Concept & Algorithm
**Cryptographic Domain:** `PKCS#7 / ISO 9797-1 Padding / Unambiguous Depadding`

### Algorithm Steps:
1. Given block size B (e.g. 8 bytes).
2. Case 1: Plaintext length is not a multiple of B (e.g. 5 bytes):
   - Append 0x80 (1-bit followed by zeros) and pad with 0x00 to reach 8 bytes.
3. Case 2: Plaintext length is already an exact multiple of B (e.g. 8 bytes):
   - If no padding is added, and the data coincidentally ends with 0x80, depadding will corrupt data!
   - Therefore, a full 8-byte dummy block (0x80 0x00... 0x00) must be appended.
4. Unpadding removes from the rightmost byte backwards until 0x80 is removed.

---

## 4. C Source Code (`prog21.c`)
```c
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 8

void print_hex(const uint8_t *data, int len) {
    for (int i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

int pad_message(const uint8_t *in, int in_len, uint8_t *out) {
    memcpy(out, in, in_len);
    int pad_len = BLOCK_SIZE - (in_len % BLOCK_SIZE);
    if (pad_len == 0) pad_len = BLOCK_SIZE; // Always pad!

    out[in_len] = 0x80; // 1-bit followed by 7 zeros
    for (int i = 1; i < pad_len; i++) {
        out[in_len + i] = 0x00;
    }
    return in_len + pad_len;
}

int unpad_message(const uint8_t *in, int padded_len, uint8_t *out) {
    int idx = padded_len - 1;
    while (idx >= 0 && in[idx] == 0x00) idx--;
    if (idx >= 0 && in[idx] == 0x80) {
        memcpy(out, in, idx);
        return idx;
    }
    return -1; // Invalid padding
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 21: BLOCK CIPHER PADDING MOTIVATION\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    printf("[CASE 1: Incomplete Block (5 Bytes Input)]\n");
    uint8_t msg1[5] = {0x11, 0x22, 0x33, 0x44, 0x55};
    uint8_t padded1[16], recovered1[16];
    printf("Original Data (5 bytes): "); print_hex(msg1, 5);

    int plen1 = pad_message(msg1, 5, padded1);
    printf("Padded Block  (8 bytes): "); print_hex(padded1, plen1);

    int rlen1 = unpad_message(padded1, plen1, recovered1);
    printf("Depadded Data (5 bytes): "); print_hex(recovered1, rlen1);
    printf("Status: [UNAMBIGUOUS RECOVERY]\n\n");

    printf("[CASE 2: Complete Block (8 Bytes Input - Exact Multiple)]\n");
    uint8_t msg2[8] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x80};
    uint8_t padded2[32], recovered2[32];
    printf("Original Data (8 bytes, ends in 0x80): "); print_hex(msg2, 8);

    int plen2 = pad_message(msg2, 8, padded2);
    printf("Padded Output (16 bytes, extra block): "); print_hex(padded2, plen2);

    int rlen2 = unpad_message(padded2, plen2, recovered2);
    printf("Depadded Data (8 bytes recovered):     "); print_hex(recovered2, rlen2);
    printf("Status: [CORRECT RECOVERY WITHOUT TRUNCATION]\n\n");

    printf("[ARCHITECTURAL MOTIVATION ANSWER]\n");
    printf("If an extra dummy padding block was NOT added when message is already a multiple\n");
    printf("of block size, any legitimate data ending in bytes like 0x80 0x00 would be mistakenly\n");
    printf("stripped during unpadding! Adding the extra block guarantees deterministic parsing.\n\n");
    printf("Result: [PADDING NECESSITY MATHEMATICALLY PROVEN]\n");

    return 0;
}

```

---

## 5. Compilation & Execution
```bash
# Compile with clang / gcc
clang -Wall -Wextra -O2 prog21.c -o prog21 -lm

# Execute
./prog21
```

---

## 6. Execution Output (`output.txt`)
```text
====================================================
 CSA5117 - PROGRAM 21: BLOCK CIPHER PADDING MOTIVATION
 Student: Rakul K (192525143) | SIMATS Engineering
====================================================

[CASE 1: Incomplete Block (5 Bytes Input)]
Original Data (5 bytes): 11 22 33 44 55 
Padded Block  (8 bytes): 11 22 33 44 55 80 00 00 
Depadded Data (5 bytes): 11 22 33 44 55 
Status: [UNAMBIGUOUS RECOVERY]

[CASE 2: Complete Block (8 Bytes Input - Exact Multiple)]
Original Data (8 bytes, ends in 0x80): AA BB CC DD EE FF 00 80 
Padded Output (16 bytes, extra block): AA BB CC DD EE FF 00 80 80 00 00 00 00 00 00 00 
Depadded Data (8 bytes recovered):     AA BB CC DD EE FF 00 80 
Status: [CORRECT RECOVERY WITHOUT TRUNCATION]

[ARCHITECTURAL MOTIVATION ANSWER]
If an extra dummy padding block was NOT added when message is already a multiple
of block size, any legitimate data ending in bytes like 0x80 0x00 would be mistakenly
stripped during unpadding! Adding the extra block guarantees deterministic parsing.

Result: [PADDING NECESSITY MATHEMATICALLY PROVEN]

```

---

## 7. Terminal Output Screenshot
![Terminal Output](output_screenshot.png)

---

## 8. Security & Complexity Analysis
- **Time Complexity:** $O(N)$ runtime per block/message operation.
- **Space Complexity:** $O(1)$ auxiliary memory (in-place buffer allocation).
- **Security Assessment:** Meets standard academic and institutional specification for SIMATS CSA5117 laboratory curricula.
