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

	ANIMATOR animator;

	void InitScaleNMatrix() noexcept;

	void AniFromCurrentPos(ANI*) const noexcept;
	void AniToMatrix(const ANI&) noexcept;
	bool AnimationProceed() noexcept;
	void AnimationFinish() noexcept;

public:
	CUBE(GRAPHICS&, POS initial_position, const PROPERTIES& board_properties, CUBE_STATE initial_state);
	CUBE(const CUBE&) = delete;
	CUBE& operator= (const CUBE&) = delete;
	~CUBE() noexcept;

	void Draw() noexcept;

	void AnimationInit(ANI* end, ANI* start = 0) noexcept;
};