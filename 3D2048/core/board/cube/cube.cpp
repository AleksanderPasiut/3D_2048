#include "cube.h"

void CUBE::InitScaleNMatrix() noexcept
{
	scale = 0.2f;
	D3DXMatrixScaling(&matrix, scale, scale, scale);
	D3DXMATRIX tmp;
	D3DXMatrixTranslation(&tmp, 
		2.0f*static_cast<float>(pos.x)/static_cast<float>(brdppts.x_size-1)-1.0f,
		2.0f*static_cast<float>(pos.y)/static_cast<float>(brdppts.y_size-1)-1.0f,
		2.0f*static_cast<float>(pos.z)/static_cast<float>(brdppts.z_size-1)-1.0f);
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

	D3DXMATRIX old_transform;
	dev.GetTransform(D3DTS_WORLD, &old_transform);
	D3DXMATRIX new_transform;
	D3DXMatrixMultiply(&new_transform, &matrix, &old_transform);
	dev.SetTransform(D3DTS_WORLD, &new_transform);
	dev.SetMaterial(graphics.MaterialCube(state));
	graphics.DrawCube();
	dev.SetTransform(D3DTS_WORLD, &old_transform);
}