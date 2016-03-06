#include "walls.h"

void WALLS::InitMatrices() noexcept
{
	float shift = 1.7f;
	float scale = 1.3f;
	D3DXMatrixScaling(&matrix_front_back, shift, scale, scale);
	D3DXMatrixScaling(&matrix_left_right, scale, shift, scale);
	D3DXMatrixScaling(&matrix_top_bottom, scale, scale, shift);
}
unsigned WALLS::DM(WALL_TYPE wall) noexcept
{
	if (selecting.Selected() == wall)
		if (selecting.Clicked())
			return 2;
		else return 1;
	else return 0;
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
		dev.SetMaterial(graphics.MaterialWall(DM(WALL_FRONT)));
			graphics.DrawWallFrontIn();
		dev.SetMaterial(graphics.MaterialWall(DM(WALL_BACK)));
			graphics.DrawWallBackIn();

	dev.SetTransform(D3DTS_WORLD, &nt_left_right);
		dev.SetMaterial(graphics.MaterialWall(DM(WALL_LEFT)));
			graphics.DrawWallLeftIn();
		dev.SetMaterial(graphics.MaterialWall(DM(WALL_RIGHT)));
			graphics.DrawWallRightIn();

	dev.SetTransform(D3DTS_WORLD, &nt_top_bottom);
		dev.SetMaterial(graphics.MaterialWall(DM(WALL_TOP)));
			graphics.DrawWallTopIn();
		dev.SetMaterial(graphics.MaterialWall(DM(WALL_BOTTOM)));
			graphics.DrawWallBottomIn();

	dev.SetTransform(D3DTS_WORLD, &nt_front_back);
		dev.SetMaterial(graphics.MaterialWall(DM(WALL_FRONT)));
			graphics.DrawWallFrontOut();
		dev.SetMaterial(graphics.MaterialWall(DM(WALL_BACK)));
			graphics.DrawWallBackOut();

	dev.SetTransform(D3DTS_WORLD, &nt_left_right);
		dev.SetMaterial(graphics.MaterialWall(DM(WALL_LEFT)));
			graphics.DrawWallLeftOut();
		dev.SetMaterial(graphics.MaterialWall(DM(WALL_RIGHT)));
			graphics.DrawWallRightOut();

	dev.SetTransform(D3DTS_WORLD, &nt_top_bottom);
		dev.SetMaterial(graphics.MaterialWall(DM(WALL_TOP)));
			graphics.DrawWallTopOut();
		dev.SetMaterial(graphics.MaterialWall(DM(WALL_BOTTOM)));
			graphics.DrawWallBottomOut();

	dev.SetTransform(D3DTS_WORLD, &old_transform);
}

bool WALLS::MouseButtonDown(LPARAM) noexcept
{
	selecting.PerformClicking(WM_LBUTTONDOWN);
	return selecting.Clicked();
}
void WALLS::MouseMove(LPARAM lParam) noexcept
{
	if (!selecting.Clicked())
		selecting.PerformSelecting(graphics, lParam);
}
WALL_TYPE WALLS::MouseButtonUp(LPARAM) noexcept
{
	selecting.PerformClicking(WM_LBUTTONUP);
	return selecting.Selected();
}