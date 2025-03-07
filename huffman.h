#pragma once

#include <stdlib.h>

unsigned int huffman_bits(unsigned int lit_value);
unsigned int huffman_codes(unsigned int lit_value);

unsigned int append_bit(unsigned char bit);
unsigned int append_bits(unsigned int bits, unsigned int n_bits);
unsigned int append_bits_reverse(unsigned int bits, unsigned int n_bits);

unsigned long get_adler(unsigned char* buf, unsigned int buf_size);
unsigned long get_adler_from_lines(const unsigned char* rgbs, int width, int height);

unsigned int huffman_static_lines(const unsigned char* rgbs, int width, int height, unsigned char* huff_codes);

