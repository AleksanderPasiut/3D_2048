#pragma once

#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#include "customfvf.h"

class GRAPHICS
{
protected:
	HWND hwnd;
	IDirect3D9* d3d;
	IDirect3DDevice9* d3ddev;
	D3DPRESENT_PARAMETERS d3dpp;

	struct STR_WORLD
	{
		D3DXMATRIX matWorld;
		float rotationY;
		float rotationZ;
	};
	struct STR_VIEW
	{
		D3DXMATRIX matView;
		D3DXVECTOR3 camera_pos;
		D3DXVECTOR3 look_at_point;
		D3DXVECTOR3 up_direction;
	};
	struct STR_PROJECTION
	{
		D3DXMATRIX matProjection;
		float angle;
		float plane_near;
		float plane_far;
	};

	STR_WORLD strWorld;
	STR_VIEW strView;
	STR_PROJECTION strProjection;

	D3DCOLOR color_back;
	D3DMATERIAL9 material_cube[8];
	D3DMATERIAL9 material_wall;

	IDirect3DVertexBuffer9* vb_cube;

	inline void CreateDirect3DDevice();
	inline void InitLights() noexcept;
	inline void InitVBCube();
	inline void InitMaterials() noexcept;

public:
	GRAPHICS(HWND);
	GRAPHICS(const GRAPHICS&) = delete;
	GRAPHICS& operator= (const GRAPHICS&) = delete;
	~GRAPHICS() noexcept;

	void BeginScene() noexcept;
	void EndScene() noexcept;

	void UpdateMatrixWorld() noexcept;
	void UpdateMatrixView() noexcept;
	void UpdateMatrixProjection() noexcept;

	void DrawCube() noexcept;
	void DrawWallFrontIn() noexcept;
	void DrawWallFrontOut() noexcept;
	void DrawWallBackIn() noexcept;
	void DrawWallBackOut() noexcept;
	void DrawWallLeftIn() noexcept;
	void DrawWallLeftOut() noexcept;
	void DrawWallRightIn() noexcept;
	void DrawWallRightOut() noexcept;
	void DrawWallTopIn() noexcept;
	void DrawWallTopOut() noexcept;
	void DrawWallBottomIn() noexcept;
	void DrawWallBottomOut() noexcept;

	IDirect3DDevice9* RetDevice() noexcept { return d3ddev; }
	float& RotationY() noexcept { return strWorld.rotationY; }
	float& RotationZ() noexcept { return strWorld.rotationZ; }
	D3DXVECTOR3& CameraPos() noexcept { return strView.camera_pos; }
	D3DXVECTOR3& LookAtPoint() noexcept { return strView.look_at_point; }
	D3DXVECTOR3& UpDirection() noexcept { return strView.up_direction; }
	float& ProjectionAngle() noexcept { return strProjection.angle; }
	float& PlaneNear() noexcept { return strProjection.plane_near; }
	float& PlaneFar() noexcept { return strProjection.plane_far; }

	D3DMATERIAL9* MaterialCube(unsigned value) noexcept { return value < 8 ? &material_cube[value] : 0; }
	D3DMATERIAL9* MaterialWall() noexcept { return &material_wall; }
};
