#include "movegen.h"

movegen::movegen()
{
}

movegen::~movegen()
{
}


void movegen::generate_queen_qmoves(bitboard* b, movelist* l)
{
	uint64_t queens = b->bbs[QUEEN][b->side_to_move];
	unsigned long origin;
	unsigned long target;
	uint64_t queen_attacks = 0ULL;
	while (queens != 0ULL)
	{
		_BitScanForward64(&origin, queens);
		queen_attacks = attacks::get_rook_attacks(origin, b->occupancy[2]) & (~b->occupancy[2]);
		queen_attacks |= attacks::get_bishop_attacks(origin, b->occupancy[2]) & (~b->occupancy[2]);
		while (_BitScanForward64(&target, queen_attacks)) {
			l->moves[l->size] = bit_move((uint8_t)origin, (uint8_t)target, bit_move::quiet_move, QUEEN, EMPTY);
			l->size++;
			queen_attacks &= queen_attacks - 1;
		}
		queens &= queens - 1;
	}
}

void movegen::generate_queen_cmoves(bitboard* b, movelist* l)
{
	uint64_t queens = b->bbs[QUEEN][b->side_to_move];
	unsigned long origin;
	unsigned long target;
	uint64_t queen_attacks = 0ULL;
	uint8_t capture_type = EMPTY;
	while (queens != 0ULL)
	{
		_BitScanForward64(&origin, queens);
		queen_attacks = attacks::get_rook_attacks(origin, b->occupancy[2]) & (b->occupancy[!b->side_to_move]);
		queen_attacks |= attacks::get_bishop_attacks(origin, b->occupancy[2]) & (b->occupancy[!b->side_to_move]);
		while (_BitScanForward64(&target, queen_attacks)) {
			capture_type = b->piece_type_from_index(target);
			l->moves[l->size] = bit_move((uint8_t)origin, (uint8_t)target, bit_move::capture, QUEEN, capture_type);
			l->size++;
			queen_attacks &= queen_attacks - 1;
		}
		queens &= queens - 1;
	}
}


void movegen::generate_king_cmoves(bitboard* b, movelist* l)
{
	uint64_t king = b->bbs[KING][b->side_to_move];
	uint64_t opp_pieces = b->occupancy[!b->side_to_move];
	unsigned long origin;
	unsigned long target;
	_BitScanForward64(&origin, king);
	uint64_t king_attacks = attacks::king_attacks[origin] & opp_pieces;
	uint8_t capture_type = EMPTY;
	while (_BitScanForward64(&target, king_attacks)) {
		capture_type = b->piece_type_from_index(target);
		l->moves[l->size] = bit_move((uint8_t)origin, (uint8_t)target, bit_move::capture, KING, capture_type);
		l->size++;
		king_attacks &= king_attacks - 1;
	}
}

void movegen::generate_all_captures(bitboard* b, movelist* l)
{
	if (b->side_to_move) {
		generate_pawn_cmoves<true>(b, l);
		generate_knight_cmoves<true>(b, l);
		generate_bishop_cmoves<true>(b, l);
		generate_rook_cmoves<true>(b, l);
	}
	else {
		generate_pawn_cmoves<false>(b, l);
		generate_knight_cmoves<false>(b, l);
		generate_bishop_cmoves<false>(b, l);
		generate_rook_cmoves<false>(b, l);
	}
	generate_queen_cmoves(b, l);
	generate_king_cmoves(b, l);
}

void movegen::generate_all_quiet_moves(bitboard* b, movelist* l)
{
	if (b->side_to_move) {
		generate_pawn_qmoves<true>(b, l);
		generate_king_qmoves<true>(b, l);
		generate_knight_qmoves<true>(b, l);
		generate_bishop_qmoves<true>(b, l);
		generate_rook_qmoves<true>(b, l);
	}
	else {
		generate_pawn_qmoves<false>(b, l);
		generate_king_qmoves<false>(b, l);
		generate_knight_qmoves<false>(b, l);
		generate_bishop_qmoves<false>(b, l);
		generate_rook_qmoves<false>(b, l);
	}
	generate_queen_qmoves(b, l);
	
}

void movegen::generate_all_pseudo_legal_moves(bitboard* b, movelist* l)
{
	generate_all_captures(b, l);
	generate_all_quiet_moves(b, l);
}




