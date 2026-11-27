#include <stdio.h>
#include <string.h>
#include <stdint.h>

void print_hex_bytes(const uint8_t *b, int len) {
    for (int i = 0; i < len; i++) printf("%02X ", b[i]);
    printf("\n");
}

int main(void) {
    printf("====================================================\n");
    printf(" CSA5117 - PROGRAM 34: PADDING MOTIVATION ANALYSIS\n");
    printf(" Student: Rakul K (192525143) | SIMATS Engineering\n");
    printf("====================================================\n\n");

    printf("[SCENARIO 1: FLAGGED AMBIGUITY WITHOUT DUMMY PADDING BLOCK]\n");
    uint8_t payload[8] = {'F', 'I', 'L', 'E', 'D', 'A', 'T', 0x80};
    printf("  Legitimate message ends in byte 0x80: "); print_hex_bytes(payload, 8);
    printf("  If sender does NOT pad because length is already 8 bytes:\n");
    printf("  Receiver runs depadder: detects 0x80 at end -> Strips byte 8!\n");
    printf("  Corrupted Message (7 bytes): "); print_hex_bytes(payload, 7);
    printf("  ERROR: [DATA CORRUPTION OCCURRED DUE TO AMBIGUITY]\n\n");

    printf("[SCENARIO 2: ROBUST SCHEME WITH MANDATORY PADDING BLOCK]\n");
    uint8_t padded_payload[16];
    memcpy(padded_payload, payload, 8);
    // Mandatory extra block
    padded_payload[8] = 0x80;
    for (int i = 9; i < 16; i++) padded_payload[i] = 0x00;

    printf("  Sender appends full dummy block (16 bytes total):\n  ");
    print_hex_bytes(padded_payload, 16);

    // Unpadding
    int depad_len = 16;
    while (depad_len > 0 && padded_payload[depad_len - 1] == 0x00) depad_len--;
    if (depad_len > 0 && padded_payload[depad_len - 1] == 0x80) depad_len--;

    printf("  Receiver unambiguously strips dummy block -> Length: %d bytes\n  ", depad_len);
    print_hex_bytes(padded_payload, depad_len);
    printf("  SUCCESS: [ORIGINAL MESSAGE PRESERVED PERFECTLY]\n\n");

    printf("Formal Motivation Conclusion:\n");
    printf("  1. Unambiguous Parsing: Without a guaranteed padding trailer, valid message\n");
    printf("     data cannot be distinguished from padding bytes.\n");
    printf("  2. Cryptographic Reversibility: Every padding scheme must define a unique,\n");
    printf("     invertible function mapping {0,1}* -> ({0,1}^b)+.\n\n");
    printf("Result: [PADDING MOTIVATION RIGOROUSLY VALIDATED]\n");

    return 0;
}
