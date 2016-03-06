#include "animator.h"

ANI& ANI::operator+= (const ANI& arg) noexcept
{
	this->pos += arg.pos;
	this->scale += arg.scale;
	//this->color.r += arg.color.r;
	//this->color.g += arg.color.g;
	//this->color.b += arg.color.b;
	//this->color.a = (this->color.a+arg.color.a)/2;
	return *this;
}

ANI ANI::operator- (const ANI& arg) const noexcept
{
	return
	{
		this->pos - arg.pos,
		this->scale - arg.scale,
		D3DXCOLOR(
			this->color.r-arg.color.r,
			this->color.g-arg.color.g,
			this->color.b-arg.color.b,
			(this->color.a+arg.color.a)/2)
	};
}

ANI& ANI::operator/= (float arg) noexcept
{
	this->pos /= arg;
	this->scale /= arg;
	this->color.r /= arg;
	this->color.g /= arg;
	this->color.b /= arg;
	return *this;
}