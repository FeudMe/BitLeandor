#include "evaluator.h"

const int evaluator::piece_values[2][6] = {
	{ 100, 300, 330, 480, 900, 0 },
	{ 120, 310, 340, 550, 1000, 0 }
};

const int evaluator::game_phase_values[6] = {
	0,
	4,
	4,
	6,
	10,
	0
};

int evaluator::eval_material(bitboard* b)
{
	int midgame_score = 0;
	int endgame_score = 0;
	
	int phase = 0;
	int num_w_queens = __popcnt64(b->bbs[bitboard::QUEEN][bitboard::WHITE]);
	int num_b_queens = __popcnt64(b->bbs[bitboard::QUEEN][bitboard::BLACK]);
	int num_w_rooks = __popcnt64(b->bbs[bitboard::ROOK][bitboard::WHITE]);
	int num_b_rooks = __popcnt64(b->bbs[bitboard::ROOK][bitboard::BLACK]);
	int num_w_bishops = __popcnt64(b->bbs[bitboard::BISHOP][bitboard::WHITE]);
	int num_b_bishops = __popcnt64(b->bbs[bitboard::BISHOP][bitboard::BLACK]);
	int num_w_knights = __popcnt64(b->bbs[bitboard::KNIGHT][bitboard::WHITE]);
	int num_b_knights = __popcnt64(b->bbs[bitboard::KNIGHT][bitboard::BLACK]);
	int num_w_pawns = __popcnt64(b->bbs[bitboard::PAWN][bitboard::WHITE]);
	int num_b_pawns = __popcnt64(b->bbs[bitboard::PAWN][bitboard::BLACK]);
	
	phase += (num_w_queens + num_b_queens) * game_phase_values[bitboard::QUEEN];
	phase += (num_w_rooks + num_b_rooks) * game_phase_values[bitboard::ROOK];
	phase += (num_w_bishops + num_b_bishops) * game_phase_values[bitboard::BISHOP];
	phase += (num_w_knights + num_b_knights) * game_phase_values[bitboard::KNIGHT];

	midgame_score += (num_w_queens - num_b_queens) * piece_values[MIDGAME][bitboard::QUEEN];
	midgame_score += (num_w_rooks - num_b_rooks) * piece_values[MIDGAME][bitboard::ROOK];
	midgame_score += (num_w_bishops - num_b_bishops) * piece_values[MIDGAME][bitboard::BISHOP];
	midgame_score += (num_w_knights - num_b_knights) * piece_values[MIDGAME][bitboard::KNIGHT];
	midgame_score += (num_w_pawns - num_b_pawns) * piece_values[MIDGAME][bitboard::PAWN];

	endgame_score += (num_w_queens - num_b_queens) * piece_values[ENDGAME][bitboard::QUEEN];
	endgame_score += (num_w_rooks - num_b_rooks) * piece_values[ENDGAME][bitboard::ROOK];
	endgame_score += (num_w_bishops - num_b_bishops) * piece_values[ENDGAME][bitboard::BISHOP];
	endgame_score += (num_w_knights - num_b_knights) * piece_values[ENDGAME][bitboard::KNIGHT];
	endgame_score += (num_w_pawns - num_b_pawns) * piece_values[ENDGAME][bitboard::PAWN];
	
	int score = (midgame_score * phase + endgame_score * (24 - phase)) / 24;
	return (b->side_to_move) ? -score : score;
}