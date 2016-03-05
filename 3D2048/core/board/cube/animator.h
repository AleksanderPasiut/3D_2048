#pragma once

#include "..\\..\\graphics\\graphics.h"

struct ANI
{
	D3DXVECTOR3 pos;
	float scale;
	D3DCOLORVALUE color;

	ANI& operator+= (const ANI&) noexcept;
	ANI operator- (const ANI&) const noexcept;
	ANI& operator/= (float) noexcept;
};

struct ANIMATOR
{
	bool animate;
	float animation_time;
	float timer;
	ANI start;
	ANI end;
	ANI speed;
	D3DMATERIAL9 material;

	ANIMATOR() : 
		animate(false),
		animation_time(300.0f),
		material({0})
		{}
};