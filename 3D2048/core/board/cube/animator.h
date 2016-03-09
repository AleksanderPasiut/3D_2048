#pragma once

#include "..\\..\\graphics\\graphics.h"

static const unsigned int WM_CUBE_REMOVE = 0x8001;

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
	bool self_destruct;
	float animation_time;
	float timer;
	ANI start;
	ANI end;
	ANI speed;
	D3DMATERIAL9 material;

	ANIMATOR() : 
		animate(false),
		self_destruct(false),
		animation_time(15.0f),
		material({0})
		{}
};