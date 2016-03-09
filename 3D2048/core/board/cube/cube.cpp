#include "cube.h"

void CUBE::InitScaleNMatrix() noexcept
{
	scale = 0.2f;
	D3DXMatrixScaling(&matrix, scale, scale, scale);
	D3DXMATRIX tmp;
	D3DXVECTOR3 vec = Position();
	D3DXMatrixTranslation(&tmp, Position().x, Position().y, Position().z);
	D3DXMatrixMultiply(&matrix, &matrix, &tmp);
}

CUBE::CUBE(GRAPHICS& in_graphics, POS init_pos, const PROPERTIES& board_properties, CUBE_STATE in_state) :
	graphics(in_graphics),
	pos(init_pos),
	brdppts(board_properties),
	state(in_state)
{
	InitScaleNMatrix();
}
CUBE::~CUBE() noexcept
{

}

void CUBE::Draw() noexcept
{
	IDirect3DDevice9& dev = *graphics.RetDevice();

	if (!AnimationProceed())
		dev.SetMaterial(graphics.MaterialCube(state));

	D3DXMATRIX old_transform;
	dev.GetTransform(D3DTS_WORLD, &old_transform);
	D3DXMATRIX new_transform;
	D3DXMatrixMultiply(&new_transform, &matrix, &old_transform);
	dev.SetTransform(D3DTS_WORLD, &new_transform);

	graphics.DrawCube();
	dev.SetTransform(D3DTS_WORLD, &old_transform);
}

void CUBE::Show() noexcept
{
	ANI start;
	AniFromCurrentPos(&start);

	start.scale = 0.0f;

	ANI end;
	AniFromCurrentPos(&end);

	AnimationInit(&end, &start);
}
void CUBE::MoveIn(D3DXVECTOR3 starting_pos) noexcept
{
	ANI start;
	start.pos = starting_pos;
	start.scale = 0.0f;
	start.color = graphics.MaterialCube(static_cast<unsigned>(state))->Diffuse;

	ANI end;
	AniFromCurrentPos(&end);

	AnimationInit(&end, &start);
}
void CUBE::Move(POS in_pos, CUBE_STATE cs) noexcept
{
	ANI start;
	AniFromCurrentPos(&start);

	pos = in_pos;
	state = cs;

	ANI end;
	AniFromCurrentPos(&end);

	AnimationInit(&end, &start);
}
void CUBE::MoveOut(D3DXVECTOR3 fading_pos) noexcept
{
	ANI end;
	end.pos = fading_pos;
	end.scale = 0.0f;
	end.color = graphics.MaterialCube(CS_INVISIBLE)->Diffuse;

	AnimationInit(&end);
	animator.self_destruct = true;
}