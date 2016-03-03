#include "walls.h"

void WALLS::InitMatrices() noexcept
{
	float shift = 1.6f;
	float scale = 1.4f;
	D3DXMatrixScaling(&matrix_front_back, shift, scale, scale);
	D3DXMatrixScaling(&matrix_left_right, scale, shift, scale);
	D3DXMatrixScaling(&matrix_top_bottom, scale, scale, shift);
}

WALLS::WALLS(GRAPHICS& in_graphics) : 
	graphics(in_graphics)
{
	InitMatrices();
}
WALLS::~WALLS()
{

}

void WALLS::Draw() noexcept
{
	IDirect3DDevice9& dev = *graphics.RetDevice();

	dev.SetMaterial(graphics.MaterialWall());

	D3DXMATRIX old_transform;
	dev.GetTransform(D3DTS_WORLD, &old_transform);

	D3DXMATRIX nt_front_back;
	D3DXMATRIX nt_left_right;
	D3DXMATRIX nt_top_bottom;
	
	D3DXMatrixMultiply(&nt_front_back, &matrix_front_back, &old_transform);
	D3DXMatrixMultiply(&nt_left_right, &matrix_left_right, &old_transform);
	D3DXMatrixMultiply(&nt_top_bottom, &matrix_top_bottom, &old_transform);

	dev.SetTransform(D3DTS_WORLD, &nt_front_back);
	graphics.DrawWallFrontIn();
	graphics.DrawWallBackIn();

	dev.SetTransform(D3DTS_WORLD, &nt_left_right);
	graphics.DrawWallLeftIn();
	graphics.DrawWallRightIn();

	dev.SetTransform(D3DTS_WORLD, &nt_top_bottom);
	graphics.DrawWallTopIn();
	graphics.DrawWallBottomIn();

	dev.SetTransform(D3DTS_WORLD, &nt_front_back);
	graphics.DrawWallFrontOut();
	graphics.DrawWallBackOut();

	dev.SetTransform(D3DTS_WORLD, &nt_left_right);
	graphics.DrawWallLeftOut();
	graphics.DrawWallRightOut();

	dev.SetTransform(D3DTS_WORLD, &nt_top_bottom);
	graphics.DrawWallTopOut();
	graphics.DrawWallBottomOut();

	dev.SetTransform(D3DTS_WORLD, &old_transform);
}