# CSA5117 / CSA51 - Cryptography and Network Security (40 Laboratory Programs)

<div align="center">

### SAVEETHA SCHOOL OF ENGINEERING
### SAVEETHA INSTITUTE OF MEDICAL AND TECHNICAL SCIENCES (SIMATS)
**Department of Computer Science and Engineering**

---

**Student Name:** Rakul K  
**Register Number:** 192525143  
**Course Code:** CSA5117 / CSA51 - Cryptography and Network Security  
**Academic Term:** 2026-2027  

---

[![GitHub license](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Programs](https://img.shields.io/badge/Programs-40%2F40%20Completed-brightgreen.svg)]()
[![Platform](https://img.shields.io/badge/Language-C11%20%2F%20POSIX-orange.svg)]()
[![Institution](https://img.shields.io/badge/Institution-SIMATS%20Engineering-purple.svg)]()

</div>

---

## :book: Repository Overview
This repository contains the complete laboratory curriculum implementations, cryptanalytic attacks, mathematical proofs, verified execution outputs, and high-resolution dark-mode terminal screenshots for all **40 Programming Questions** in **CSA5117 - Cryptography and Network Security** at Saveetha School of Engineering (SIMATS).

Each experiment is organized into an isolated directory containing:
1. **Source Code (`progXX.c`)**: Highly optimized, robust ANSI C implementation.
2. **Execution Output (`output.txt`)**: Verbatim console output recorded during execution.
3. **Output Screenshot (`output_screenshot.png`)**: High-resolution dark-mode terminal capture.
4. **Experiment Report (`README.md`)**: Comprehensive documentation covering Aim, Algorithm, Mathematical Derivations, Code, and Complexity Analysis.

A dedicated central folder [`output_ss/`](./output_ss/) aggregates all 40 program output screenshots for rapid inspection.

---

## :clipboard: Master Index of 40 Programs

| # | Program Title | Cryptographic Concept | Source Code | Screenshot | Verification |
|---|---|---|:---:|:---:|:---:|
| 01 | [Caesar Cipher (Shift k in [1, 25])](./Prog01_Caesar_Cipher) | `Classical Symmetric Cipher / Modular Arithmetic` | [:page_facing_up: Code](./Prog01_Caesar_Cipher/prog01.c) | [:camera: Screenshot](./output_ss/prog01_output.png) | :white_check_mark: Verified |
| 02 | [Monoalphabetic Substitution Cipher](./Prog02_Monoalphabetic_Cipher) | `Arbitrary Permutation Key / Substitution` | [:page_facing_up: Code](./Prog02_Monoalphabetic_Cipher/prog02.c) | [:camera: Screenshot](./output_ss/prog02_output.png) | :white_check_mark: Verified |
| 03 | [Playfair Cipher Encryption & Decryption](./Prog03_Playfair_Cipher) | `Polygraphic Substitution / 5x5 Key Matrix` | [:page_facing_up: Code](./Prog03_Playfair_Cipher/prog03.c) | [:camera: Screenshot](./output_ss/prog03_output.png) | :white_check_mark: Verified |
| 04 | [Polyalphabetic Substitution (Vigenère Cipher)](./Prog04_Polyalphabetic_Vigenere) | `Periodic Polyalphabetic / Modular Keystream` | [:page_facing_up: Code](./Prog04_Polyalphabetic_Vigenere/prog04.c) | [:camera: Screenshot](./output_ss/prog04_output.png) | :white_check_mark: Verified |
| 05 | [Affine Caesar Cipher Constraints & Implementation](./Prog05_Affine_Caesar_Cipher) | `Affine Transformations / Bijectivity / Coprimality` | [:page_facing_up: Code](./Prog05_Affine_Caesar_Cipher/prog05.c) | [:camera: Screenshot](./output_ss/prog05_output.png) | :white_check_mark: Verified |
| 06 | [Affine Cipher Cryptanalysis (Known Frequencies)](./Prog06_Affine_Cryptanalysis) | `Modular Congruences / Frequency Cryptanalysis` | [:page_facing_up: Code](./Prog06_Affine_Cryptanalysis/prog06.c) | [:camera: Screenshot](./output_ss/prog06_output.png) | :white_check_mark: Verified |
| 07 | [Simple Substitution Cryptanalysis (Edgar Allan Poe's Gold-Bug)](./Prog07_Simple_Substitution_Gold_Bug) | `Frequency Analysis / Trigraph Matching` | [:page_facing_up: Code](./Prog07_Simple_Substitution_Gold_Bug/prog07.c) | [:camera: Screenshot](./output_ss/prog07_output.png) | :white_check_mark: Verified |
| 08 | [Keyword-Based Monoalphabetic Cipher](./Prog08_Keyword_Monoalphabetic_Cipher) | `Keyword Key Generation / Permutation Cipher` | [:page_facing_up: Code](./Prog08_Keyword_Monoalphabetic_Cipher/prog08.c) | [:camera: Screenshot](./output_ss/prog08_output.png) | :white_check_mark: Verified |
| 09 | [PT-109 Patrol Boat Playfair Message Decryption](./Prog09_Playfair_PT109_Decryption) | `Historical Cryptanalysis / Playfair Decryption` | [:page_facing_up: Code](./Prog09_Playfair_PT109_Decryption/prog09.c) | [:camera: Screenshot](./output_ss/prog09_output.png) | :white_check_mark: Verified |
| 10 | [Playfair Cipher Encryption (Cadogan West Matrix)](./Prog10_Playfair_Cadogan_West) | `Given Matrix Digraph Encryption` | [:page_facing_up: Code](./Prog10_Playfair_Cadogan_West/prog10.c) | [:camera: Screenshot](./output_ss/prog10_output.png) | :white_check_mark: Verified |
| 11 | [Playfair Cipher Key Space Analysis](./Prog11_Playfair_Key_Space_Analysis) | `Combinatorics / Symmetries / Key Space Entropy` | [:page_facing_up: Code](./Prog11_Playfair_Key_Space_Analysis/prog11.c) | [:camera: Screenshot](./output_ss/prog11_output.png) | :white_check_mark: Verified |
| 12 | [Hill Cipher 2x2 Matrix Encryption & Decryption](./Prog12_Hill_Cipher_2x2) | `Linear Algebra mod 26 / Matrix Inversion` | [:page_facing_up: Code](./Prog12_Hill_Cipher_2x2/prog12.c) | [:camera: Screenshot](./output_ss/prog12_output.png) | :white_check_mark: Verified |
| 13 | [Hill Cipher Known & Chosen Plaintext Attack](./Prog13_Hill_Cipher_Known_Plaintext_Attack) | `Cryptanalysis / Matrix Inversion over GF(26)` | [:page_facing_up: Code](./Prog13_Hill_Cipher_Known_Plaintext_Attack/prog13.c) | [:camera: Screenshot](./output_ss/prog13_output.png) | :white_check_mark: Verified |
| 14 | [One-Time Pad Vigenère Cipher & Two-Time Pad Vulnerability](./Prog14_One_Time_Pad_Vigenere) | `Vernam Cipher / Keystream Inversion / Perfect Secrecy` | [:page_facing_up: Code](./Prog14_One_Time_Pad_Vigenere/prog14.c) | [:camera: Screenshot](./output_ss/prog14_output.png) | :white_check_mark: Verified |
| 15 | [Additive (Caesar) Cipher Letter Frequency Attack](./Prog15_Additive_Cipher_Frequency_Attack) | `Automated Cryptanalysis / Chi-Squared Goodness of Fit` | [:page_facing_up: Code](./Prog15_Additive_Cipher_Frequency_Attack/prog15.c) | [:camera: Screenshot](./output_ss/prog15_output.png) | :white_check_mark: Verified |
| 16 | [Monoalphabetic Cipher Automated Frequency Attack](./Prog16_Monoalphabetic_Frequency_Attack) | `Ciphertext-Only Attack / Letter Frequency Mapping` | [:page_facing_up: Code](./Prog16_Monoalphabetic_Frequency_Attack/prog16.c) | [:camera: Screenshot](./output_ss/prog16_output.png) | :white_check_mark: Verified |
| 17 | [DES Decryption Key Generation & Reverse Shift Schedule](./Prog17_DES_Decryption_Key_Schedule) | `DES Subkey Schedule / Circular Shifts / Reversibility` | [:page_facing_up: Code](./Prog17_DES_Decryption_Key_Schedule/prog17.c) | [:camera: Screenshot](./output_ss/prog17_output.png) | :white_check_mark: Verified |
| 18 | [DES Subkey Schedule Bit Independence Proof](./Prog18_DES_Subkey_Bit_Independence) | `Permuted Choice 2 / Disjoint Bit Allocation` | [:page_facing_up: Code](./Prog18_DES_Subkey_Bit_Independence/prog18.c) | [:camera: Screenshot](./output_ss/prog18_output.png) | :white_check_mark: Verified |
| 19 | [3DES Encryption in Cipher Block Chaining (CBC) Mode](./Prog19_3DES_CBC_Mode_Analysis) | `Triple DES / CBC Chaining / Security vs Performance` | [:page_facing_up: Code](./Prog19_3DES_CBC_Mode_Analysis/prog19.c) | [:camera: Screenshot](./output_ss/prog19_output.png) | :white_check_mark: Verified |
| 20 | [ECB vs CBC Error Propagation Analysis](./Prog20_ECB_vs_CBC_Error_Propagation) | `Cipher Modes / Error Propagation / Bit Flipping` | [:page_facing_up: Code](./Prog20_ECB_vs_CBC_Error_Propagation/prog20.c) | [:camera: Screenshot](./output_ss/prog20_output.png) | :white_check_mark: Verified |
| 21 | [Block Cipher Padding Motivation & Ambiguity Analysis](./Prog21_Block_Cipher_Padding_Motivation) | `PKCS#7 / ISO 9797-1 Padding / Unambiguous Depadding` | [:page_facing_up: Code](./Prog21_Block_Cipher_Padding_Motivation/prog21.c) | [:camera: Screenshot](./output_ss/prog21_output.png) | :white_check_mark: Verified |
| 22 | [Simplified DES (S-DES) in Cipher Block Chaining (CBC) Mode](./Prog22_SDES_CBC_Mode) | `S-DES / CBC Mode / Bitwise Feistel Cipher` | [:page_facing_up: Code](./Prog22_SDES_CBC_Mode/prog22.c) | [:camera: Screenshot](./output_ss/prog22_output.png) | :white_check_mark: Verified |
| 23 | [Simplified DES (S-DES) in Counter (CTR) Mode](./Prog23_SDES_CTR_Mode) | `S-DES / Stream Cipher Mode / CTR Counter Keystream` | [:page_facing_up: Code](./Prog23_SDES_CTR_Mode/prog23.c) | [:camera: Screenshot](./output_ss/prog23_output.png) | :white_check_mark: Verified |
| 24 | [RSA Private Key Calculation & Trial Factorization](./Prog24_RSA_Private_Key_Calculation) | `RSA / Trial Division / Extended Euclidean Algorithm` | [:page_facing_up: Code](./Prog24_RSA_Private_Key_Calculation/prog24.c) | [:camera: Screenshot](./output_ss/prog24_output.png) | :white_check_mark: Verified |
| 25 | [RSA Common Factor Factorization Attack](./Prog25_RSA_Common_Factor_Attack) | `RSA Vulnerabilities / Greatest Common Divisor Attack` | [:page_facing_up: Code](./Prog25_RSA_Common_Factor_Attack/prog25.c) | [:camera: Screenshot](./output_ss/prog25_output.png) | :white_check_mark: Verified |
| 26 | [RSA Modulus Reuse Vulnerability Analysis](./Prog26_RSA_Modulus_Reuse_Vulnerability) | `RSA Key Generation / Modulus Factorization from (e, d)` | [:page_facing_up: Code](./Prog26_RSA_Modulus_Reuse_Vulnerability/prog26.c) | [:camera: Screenshot](./output_ss/prog26_output.png) | :white_check_mark: Verified |
| 27 | [RSA Single-Character Encryption Dictionary Attack](./Prog27_RSA_Single_Character_Dictionary_Attack) | `Small Message Space / Precomputed Codebook Attack` | [:page_facing_up: Code](./Prog27_RSA_Single_Character_Dictionary_Attack/prog27.c) | [:camera: Screenshot](./output_ss/prog27_output.png) | :white_check_mark: Verified |
| 28 | [Diffie-Hellman Variation Analysis (x^a mod q)](./Prog28_Diffie_Hellman_Variation_Analysis) | `Diffie-Hellman / Discrete Logarithm vs Modular Roots` | [:page_facing_up: Code](./Prog28_Diffie_Hellman_Variation_Analysis/prog28.c) | [:camera: Screenshot](./output_ss/prog28_output.png) | :white_check_mark: Verified |
| 29 | [SHA-3 Keccak Sponge Capacity Diffusion Analysis](./Prog29_SHA3_Sponge_Capacity_Diffusion) | `SHA-3 / Sponge Construction / Theta Diffusion Step` | [:page_facing_up: Code](./Prog29_SHA3_Sponge_Capacity_Diffusion/prog29.c) | [:camera: Screenshot](./output_ss/prog29_output.png) | :white_check_mark: Verified |
| 30 | [CBC-MAC Forgery on Variable-Length Messages](./Prog30_CBC_MAC_Message_Extension_Attack) | `MAC Forgery / CBC-MAC Extension Attack` | [:page_facing_up: Code](./Prog30_CBC_MAC_Message_Extension_Attack/prog30.c) | [:camera: Screenshot](./output_ss/prog30_output.png) | :white_check_mark: Verified |
| 31 | [CMAC Subkey Generation Algorithm & Polynomials](./Prog31_CMAC_Subkey_Generation) | `CMAC / Galois Field GF(2^b) / Irreducible Polynomials` | [:page_facing_up: Code](./Prog31_CMAC_Subkey_Generation/prog31.c) | [:camera: Screenshot](./output_ss/prog31_output.png) | :white_check_mark: Verified |
| 32 | [DSA vs RSA Signature Randomness & Nonce Reuse Vulnerability](./Prog32_DSA_vs_RSA_Signature_Randomness) | `Digital Signatures / Ephemeral Nonces / Private Key Leakage` | [:page_facing_up: Code](./Prog32_DSA_vs_RSA_Signature_Randomness/prog32.c) | [:camera: Screenshot](./output_ss/prog32_output.png) | :white_check_mark: Verified |
| 33 | [Data Encryption Standard (DES) Implementation](./Prog33_DES_Standard_Implementation) | `Block Cipher / Feistel Network / S-Box Nonlinearity` | [:page_facing_up: Code](./Prog33_DES_Standard_Implementation/prog33.c) | [:camera: Screenshot](./output_ss/prog33_output.png) | :white_check_mark: Verified |
| 34 | [Block Cipher Padding Ambiguity Analysis](./Prog34_Padding_Ambiguity_Analysis) | `PKCS#7 / 1-bit Followed by Zeros / Padding Oracle Defense` | [:page_facing_up: Code](./Prog34_Padding_Ambiguity_Analysis/prog34.c) | [:camera: Screenshot](./output_ss/prog34_output.png) | :white_check_mark: Verified |
| 35 | [One-Time Pad Vigenère Cipher & Shannon Perfect Secrecy](./Prog35_One_Time_Pad_Perfect_Secrecy) | `Shannon Entropy / Information-Theoretic Security / OTP` | [:page_facing_up: Code](./Prog35_One_Time_Pad_Perfect_Secrecy/prog35.c) | [:camera: Screenshot](./output_ss/prog35_output.png) | :white_check_mark: Verified |
| 36 | [Affine Caesar Cipher Bijectivity Proof & Collision Analysis](./Prog36_Affine_Cipher_Bijectivity_Proof) | `Number Theory / Bijective Mappings / Pigeonhole Principle` | [:page_facing_up: Code](./Prog36_Affine_Cipher_Bijectivity_Proof/prog36.c) | [:camera: Screenshot](./output_ss/prog36_output.png) | :white_check_mark: Verified |
| 37 | [Automated Monoalphabetic Substitution Cipher Solver](./Prog37_Automated_Monoalphabetic_Solver) | `Ciphertext-Only Cryptanalysis / Frequency & Digram Heuristics` | [:page_facing_up: Code](./Prog37_Automated_Monoalphabetic_Solver/prog37.c) | [:camera: Screenshot](./output_ss/prog37_output.png) | :white_check_mark: Verified |
| 38 | [Hill Cipher Chosen Plaintext Attack Implementation](./Prog38_Hill_Cipher_Chosen_Plaintext_Attack) | `Cryptanalysis / Chosen Plaintext Attack / Basis Vector Probing` | [:page_facing_up: Code](./Prog38_Hill_Cipher_Chosen_Plaintext_Attack/prog38.c) | [:camera: Screenshot](./output_ss/prog38_output.png) | :white_check_mark: Verified |
| 39 | [Additive Cipher Frequency Analysis Top 10 Evaluation](./Prog39_Caesar_Frequency_Analysis_Top10) | `Cryptanalysis / Chi-Squared Fitting / Statistical Ranking` | [:page_facing_up: Code](./Prog39_Caesar_Frequency_Analysis_Top10/prog39.c) | [:camera: Screenshot](./output_ss/prog39_output.png) | :white_check_mark: Verified |
| 40 | [Monoalphabetic Frequency Attack Evaluation](./Prog40_Monoalphabetic_Frequency_Evaluation) | `Cryptanalysis / Text Length Convergence / Statistical Scoring` | [:page_facing_up: Code](./Prog40_Monoalphabetic_Frequency_Evaluation/prog40.c) | [:camera: Screenshot](./output_ss/prog40_output.png) | :white_check_mark: Verified |

---

## :rocket: Quickstart & Automated Test Suite

### Prerequisites
- Clang or GCC compiler with `-lm` math library support.
- POSIX-compliant environment (macOS / Linux).

### Running All 40 Programs
Execute the master automated build harness:
```bash
chmod +x run_all.sh
./run_all.sh
```

### Compiling and Executing an Individual Program
```bash
cd Prog01_Caesar_Cipher
clang -Wall -Wextra -O2 prog01.c -o prog01 -lm
./prog01
```

---

## :mortar_board: Author
- **Rakul K** (Reg: `192525143`)
- Department of Computer Science and Engineering
- Saveetha School of Engineering, SIMATS
