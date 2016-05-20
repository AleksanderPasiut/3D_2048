#pragma once

#include "..\\..\\graphics\\graphics.h"
#include "..\\properties.h"
#include "animator.h"

enum CUBE_STATE
{
	CS_INVISIBLE = 0,
	CS_RED = 1,
	CS_ORANGE = 2,
	CS_YELLOW = 3,
	CS_GREEN = 4,
	CS_CYAN = 5,
	CS_BLUE = 6,
	CS_PURPLE = 7,
};

class CUBE
{
protected:
	GRAPHICS& graphics;
	const PROPERTIES& brdppts;
	struct POS
	{
		unsigned x;
		unsigned y;
		unsigned z;
	};
	POS pos;
	float scale;
	D3DXMATRIX matrix;
	CUBE_STATE state;
	bool showed;

	ANIMATOR animator;

	void InitScaleNMatrix() noexcept;

	void AniFromCurrentPos(ANI*) const noexcept;
	void AniToMatrix(const ANI&) noexcept;
	bool AnimationProceed() noexcept;
	void AnimationFinish() noexcept;
	void AnimationInit(ANI* end, ANI* start = 0) noexcept;

public:
	CUBE(GRAPHICS&, POS initial_position, const PROPERTIES& board_properties, CUBE_STATE initial_state);
	CUBE(const CUBE&) = delete;
	CUBE& operator= (const CUBE&) = delete;
	~CUBE() noexcept;

	void Draw() noexcept;

	void Show() noexcept;
	void MoveIn(D3DXVECTOR3 starting_pos) noexcept;
	void Move(POS target_pos, CUBE_STATE target_state, bool self_destruct) noexcept;
	void MoveOut(D3DXVECTOR3 fading_pos) noexcept;

	CUBE_STATE RetState() const noexcept { return state; }
	bool ToBeDestroyed() const noexcept { return !animator.animate && animator.self_destruct; }
	bool Showed() const noexcept { return showed; }
	D3DXVECTOR3 Position() const noexcept 
	{ return D3DXVECTOR3(
		2.0f*static_cast<float>(pos.x)/static_cast<float>(brdppts.x_size-1)-1.0f,
		2.0f*static_cast<float>(pos.y)/static_cast<float>(brdppts.y_size-1)-1.0f,
		2.0f*static_cast<float>(pos.z)/static_cast<float>(brdppts.z_size-1)-1.0f); }
	
	friend class BOARD;
};