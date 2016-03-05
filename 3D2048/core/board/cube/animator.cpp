#include "cube.h"

void CUBE::AniFromCurrentPos(ANI* out) const noexcept
{
	*out =
	{
		D3DXVECTOR3(
			2.0f*static_cast<float>(pos.x)/static_cast<float>(brdppts.x_size-1)-1.0f,
			2.0f*static_cast<float>(pos.y)/static_cast<float>(brdppts.y_size-1)-1.0f,
			2.0f*static_cast<float>(pos.z)/static_cast<float>(brdppts.z_size-1)-1.0f),
		scale,
		graphics.MaterialCube(static_cast<unsigned>(state))->Diffuse
	};
}

void CUBE::AniToMatrix(const ANI& arg) noexcept
{
	D3DXMatrixScaling(&matrix, arg.scale, arg.scale, arg.scale);
	D3DXMATRIX tmp;
	D3DXMatrixTranslation(&tmp, arg.pos.x, arg.pos.y, arg.pos.z);
	D3DXMatrixMultiply(&matrix, &matrix, &tmp);
}

void CUBE::AnimationInit(ANI* end, ANI* start) noexcept
{
	if (!start)
	{
		if (!animator.animate)
			AniFromCurrentPos(&animator.start);
	}
	else animator.start = *start;

	animator.end = *end;
	animator.speed = (animator.end - animator.start);
	animator.speed /= animator.animation_time;
	animator.animate = true;
	animator.timer = 0.0f;
}

bool CUBE::AnimationProceed() noexcept
{
	if (!animator.animate)
		return false;

	animator.start += animator.speed;
	animator.timer++;

	if (animator.timer >= animator.animation_time)
	{
		AnimationFinish();
		return false;
	}

	AniToMatrix(animator.start);
	animator.material.Diffuse = animator.start.color;
	graphics.RetDevice()->SetMaterial(&animator.material);
	return true;
}

void CUBE::AnimationFinish() noexcept
{
	AniToMatrix(animator.end);
	animator.animate = false;
}
