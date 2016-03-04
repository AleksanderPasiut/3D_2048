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

	D3DXMATRIX old_transform;
	dev.GetTransform(D3DTS_WORLD, &old_transform);

	D3DXMATRIX nt_front_back;
	D3DXMATRIX nt_left_right;
	D3DXMATRIX nt_top_bottom;
	
	D3DXMatrixMultiply(&nt_front_back, &matrix_front_back, &old_transform);
	D3DXMatrixMultiply(&nt_left_right, &matrix_left_right, &old_transform);
	D3DXMatrixMultiply(&nt_top_bottom, &matrix_top_bottom, &old_transform);

	dev.SetTransform(D3DTS_WORLD, &nt_front_back);
		dev.SetMaterial(graphics.MaterialWall(0));
			graphics.DrawWallFrontIn();
		dev.SetMaterial(graphics.MaterialWall(0));
			graphics.DrawWallBackIn();

	dev.SetTransform(D3DTS_WORLD, &nt_left_right);
		dev.SetMaterial(graphics.MaterialWall(0));
			graphics.DrawWallLeftIn();
		dev.SetMaterial(graphics.MaterialWall(0));
			graphics.DrawWallRightIn();

	dev.SetTransform(D3DTS_WORLD, &nt_top_bottom);
		dev.SetMaterial(graphics.MaterialWall(0));
			graphics.DrawWallTopIn();
		dev.SetMaterial(graphics.MaterialWall(0));
			graphics.DrawWallBottomIn();

	dev.SetTransform(D3DTS_WORLD, &nt_front_back);
		dev.SetMaterial(graphics.MaterialWall(0));
			graphics.DrawWallFrontOut();
		dev.SetMaterial(graphics.MaterialWall(0));
			graphics.DrawWallBackOut();

	dev.SetTransform(D3DTS_WORLD, &nt_left_right);
		dev.SetMaterial(graphics.MaterialWall(0));
			graphics.DrawWallLeftOut();
		dev.SetMaterial(graphics.MaterialWall(0));
			graphics.DrawWallRightOut();

	dev.SetTransform(D3DTS_WORLD, &nt_top_bottom);
		dev.SetMaterial(graphics.MaterialWall(0));
			graphics.DrawWallTopOut();
		dev.SetMaterial(graphics.MaterialWall(0));
			graphics.DrawWallBottomOut();

	dev.SetTransform(D3DTS_WORLD, &old_transform);
}

bool WALLS::MouseButtonDown(LPARAM) noexcept
{
	return false;
}
void WALLS::MouseMove(LPARAM) noexcept
{

}