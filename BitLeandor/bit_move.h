#pragma once

#include <cstdint>
#include <string>
class bit_move
{
public:
	bit_move(uint64_t origin, uint16_t target, uint16_t flags);
	bit_move();
	uint16_t get_origin();
	uint16_t get_target();
	uint16_t get_flags();
	uint16_t move = 0;
	enum flags : uint16_t {
		quiet_move,
		double_pawn_push,
		kingside_castle,
		queenside_castle,
		capture,
		ep_capture,
		knight_promotion = 8,
		bishop_promotion,
		rook_promotion,
		queen_promotion,
		knight_capture_promotion,
		bishop_capture_promotion,
		rook_capture_promotion,
		queen_capture_promotion
	};
	static std::string to_string(bit_move m);
	~bit_move();
	static std::string squares_to_string[64];
};
