#pragma once

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <functional>

#include "bitboard_util.h"
#include "attacks.h"


class utility
{
public:
	utility();
	static void remove_first_occurance(std::list<int>* l, int i);
	template <typename T> static int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}
	static uint64_t random_64_bit_num();
	static unsigned int random_state;
	static unsigned int pseudo_rand_32_bit_num();
	static uint64_t pseudo_rand_64_bit_num();
	static uint64_t magic_num_candidate();
	static void generate_magics();
	static const int num_relevant_bits_bishop[64];
	static const int num_relevant_bits_rook[64];
	static uint64_t generate_occupancy_by_index(int index, int bit_count, uint64_t attack_mask);
	static uint64_t generate_magic_number(int square, int relevant_bits, bool is_bishop);
	static void generate_magic_attacks();
	bool random_bool();
	static void split_string(std::vector<std::string>* v, std::string s);
	~utility();
private:

};
