#include <windowsx.h>

#include "selecting.h"

void SELECTING::CreateRay(GRAPHICS& graphics, RAY* lpRay, LPARAM lParam) const noexcept
{
	lpRay->origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	lpRay->direction = D3DXVECTOR3(
		( 2.0f*GET_X_LPARAM(lParam)/graphics.BufferWidth()  - 1.0f)/graphics.ProjectionMatrix()._11,
		(-2.0f*GET_Y_LPARAM(lParam)/graphics.BufferHeight() + 1.0f)/graphics.ProjectionMatrix()._22,
		1.0f);

	D3DXMATRIX mat;
	D3DXMatrixMultiply(&mat, &graphics.InvViewMatrix(), &graphics.InvWorldMatrix());
	D3DXVec3TransformCoord(&lpRay->origin, &lpRay->origin, &mat);
	D3DXVec3TransformNormal(&lpRay->direction, &lpRay->direction, &mat);
	D3DXVec3Normalize(&lpRay->direction, &lpRay->direction);
}

SELECTING::SELECTING()
{
	float shift = 1.7f;
	float scale = 1.3f;

	cords[WALL_FRONT] = 
	{
		D3DXVECTOR3(shift, scale, scale),
		D3DXVECTOR3(shift,-scale, scale),
		D3DXVECTOR3(shift, scale,-scale),
		D3DXVECTOR3(shift,-scale,-scale),
	};
	cords[WALL_BACK] = 
	{
		D3DXVECTOR3(-shift, scale, scale),
		D3DXVECTOR3(-shift,-scale, scale),
		D3DXVECTOR3(-shift, scale,-scale),
		D3DXVECTOR3(-shift,-scale,-scale),
	};
	cords[WALL_LEFT] = 
	{
		D3DXVECTOR3( scale, shift, scale),
		D3DXVECTOR3(-scale, shift, scale),
		D3DXVECTOR3( scale, shift,-scale),
		D3DXVECTOR3(-scale, shift,-scale),
	};
	cords[WALL_RIGHT] = 
	{
		D3DXVECTOR3( scale,-shift, scale),
		D3DXVECTOR3(-scale,-shift, scale),
		D3DXVECTOR3( scale,-shift,-scale),
		D3DXVECTOR3(-scale,-shift,-scale),
	};
	cords[WALL_TOP] = 
	{
		D3DXVECTOR3( scale, scale,shift),
		D3DXVECTOR3(-scale, scale,shift),
		D3DXVECTOR3( scale,-scale,shift),
		D3DXVECTOR3(-scale,-scale,shift),
	};
	cords[WALL_BOTTOM] = 
	{
		D3DXVECTOR3( scale, scale,-shift),
		D3DXVECTOR3(-scale, scale,-shift),
		D3DXVECTOR3( scale,-scale,-shift),
		D3DXVECTOR3(-scale,-scale,-shift),
	};

	selected = WALL_NONE;
	clicked = false;
}

void SELECTING::PerformSelecting(GRAPHICS& graphics, LPARAM lParam) noexcept
{
	RAY Ray;
	CreateRay(graphics, &Ray, lParam);

	float distance;

	selected = WALL_NONE;
	for (unsigned i = 0; i < 6; i++)
	{
		float new_distance;
		if (D3DXIntersectTri(
				&cords[i].p0, &cords[i].p1,	&cords[i].p2,
				&Ray.origin, &Ray.direction, 
				0, 0, &new_distance) ||
			D3DXIntersectTri(
				&cords[i].p1, &cords[i].p2,	&cords[i].p3,
				&Ray.origin, &Ray.direction,
				0, 0, &new_distance))
		{
			if (selected == WALL_NONE)
			{
				selected = static_cast<WALL_TYPE>(i);
				distance = new_distance;
			}
			else if (new_distance < distance)
			{
				selected = static_cast<WALL_TYPE>(i);
				distance = new_distance;
			}
		}
	}
}

void SELECTING::PerformClicking(UINT uMsg) noexcept
{
	if (selected == WALL_NONE)
		return;
	
	switch(uMsg)
	{
		case WM_LBUTTONDOWN: clicked = true; break;
		case WM_LBUTTONUP: clicked = false; break;
	}
}