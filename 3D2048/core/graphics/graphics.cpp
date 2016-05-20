#include "graphics.h"

void GRAPHICS::CreateDirect3DDevice()
{
	DWORD quality = 0;
	d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		D3DFMT_X8R8G8B8,
		true,
		D3DMULTISAMPLE_8_SAMPLES,
		&quality);
	
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.Windowed = true;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
	d3dpp.MultiSampleQuality = quality - 1;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev)))
		throw 0;

	d3ddev->SetRenderState(D3DRS_ZENABLE, true);
	d3ddev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, true);
	d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	d3ddev->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);
 	d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
 	d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
 	d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	color_back = D3DCOLOR_XRGB(0, 0, 0);
}
void GRAPHICS::InitLights() noexcept
{
	d3ddev->SetRenderState(D3DRS_LIGHTING, true);

	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_POINT;
	light.Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	light.Position = D3DXVECTOR3(5.0f,  0.0f,  0.0f);
	light.Range = 60.0f;
	light.Attenuation1 = 0.25f;

	d3ddev->SetLight(0, &light);
	d3ddev->LightEnable(0, true);
}
void GRAPHICS::InitVBCube()
{
	if (FAILED(d3ddev->CreateVertexBuffer(
		48*sizeof(CUSTOMFVF),
		D3DUSAGE_WRITEONLY,
		CUSTOMFVF_TYPE,
		D3DPOOL_DEFAULT,
		&vb_cube,
		0)))
		throw 0;

	CUSTOMFVF* v;
	vb_cube->Lock(0, 0, reinterpret_cast<void**>(&v), 0);

	v[0] = CUSTOMFVF(1.0f,1.0f,1.0f,{1.0f, 0.0f, 0.0f});
	v[1] = CUSTOMFVF(1.0f,-1.0f,1.0f,{1.0f, 0.0f, 0.0f});
	v[2] = CUSTOMFVF(1.0f,1.0f,-1.0f,{1.0f, 0.0f, 0.0f});
	v[3] = CUSTOMFVF(1.0f,-1.0f,-1.0f,{1.0f, 0.0f, 0.0f});

	v[4] = CUSTOMFVF(-1.0f,1.0f,1.0f,{-1.0f, 0.0f, 0.0f});
	v[5] = CUSTOMFVF(-1.0f,1.0f,-1.0f,{-1.0f, 0.0f, 0.0f});
	v[6] = CUSTOMFVF(-1.0f,-1.0f,1.0f,{-1.0f, 0.0f, 0.0f});
	v[7] = CUSTOMFVF(-1.0f,-1.0f,-1.0f,{-1.0f, 0.0f, 0.0f});

	v[8] = CUSTOMFVF(-1.0f,1.0f,1.0f,{0.0f, 1.0f, 0.0f});
	v[9] = CUSTOMFVF(1.0f,1.0f,1.0f,{0.0f, 1.0f, 0.0f});
	v[10] = CUSTOMFVF(-1.0f,1.0f,-1.0f,{0.0f, 1.0f, 0.0f});
	v[11] = CUSTOMFVF( 1.0f,1.0f,-1.0f,{0.0f, 1.0f, 0.0f});

	v[12] = CUSTOMFVF(-1.0f,-1.0f,1.0f,{0.0f, -1.0f, 0.0f});
	v[13] = CUSTOMFVF(-1.0f,-1.0f,-1.0f,{0.0f, -1.0f, 0.0f});
	v[14] = CUSTOMFVF(1.0f,-1.0f,1.0f,{0.0f, -1.0f, 0.0f});
	v[15] = CUSTOMFVF(1.0f,-1.0f,-1.0f,{0.0f, -1.0f, 0.0f});

	v[16] = CUSTOMFVF(1.0f,1.0f,1.0f,{0.0f, 0.0f, 1.0f});
	v[17] = CUSTOMFVF(-1.0f,1.0f,1.0f,{0.0f, 0.0f, 1.0f});
	v[18] = CUSTOMFVF(1.0f,-1.0f,1.0f,{0.0f, 0.0f, 1.0f});
	v[19] = CUSTOMFVF(-1.0f,-1.0f,1.0f,{0.0f, 0.0f, 1.0f});

	v[20] = CUSTOMFVF(1.0f,1.0f,-1.0f,{0.0f, 0.0f, -1.0f});
	v[21] = CUSTOMFVF(1.0f,-1.0f,-1.0f,{0.0f, 0.0f, -1.0f});
	v[22] = CUSTOMFVF(-1.0f,1.0f,-1.0f,{0.0f, 0.0f, -1.0f});
	v[23] = CUSTOMFVF(-1.0f,-1.0f,-1.0f,{0.0f, 0.0f, -1.0f});


	v[24] = CUSTOMFVF(1.0f,1.0f,1.0f,{1.0f, 0.0f, 0.0f});
	v[25] = CUSTOMFVF(1.0f,1.0f,-1.0f,{1.0f, 0.0f, 0.0f});
	v[26] = CUSTOMFVF(1.0f,-1.0f,1.0f,{1.0f, 0.0f, 0.0f});
	v[27] = CUSTOMFVF(1.0f,-1.0f,-1.0f,{1.0f, 0.0f, 0.0f});

	v[28] = CUSTOMFVF(-1.0f,1.0f,1.0f,{-1.0f, 0.0f, 0.0f});
	v[29] = CUSTOMFVF(-1.0f,-1.0f,1.0f,{-1.0f, 0.0f, 0.0f});
	v[30] = CUSTOMFVF(-1.0f,1.0f,-1.0f,{-1.0f, 0.0f, 0.0f});
	v[31] = CUSTOMFVF(-1.0f,-1.0f,-1.0f,{-1.0f, 0.0f, 0.0f});

	v[32] = CUSTOMFVF(-1.0f,1.0f,1.0f,{0.0f, 1.0f, 0.0f});
	v[33] = CUSTOMFVF(-1.0f,1.0f,-1.0f,{0.0f, 1.0f, 0.0f});
	v[34] = CUSTOMFVF(1.0f,1.0f,1.0f,{0.0f, 1.0f, 0.0f});
	v[35] = CUSTOMFVF(1.0f,1.0f,-1.0f,{0.0f, 1.0f, 0.0f});

	v[36] = CUSTOMFVF(-1.0f,-1.0f,1.0f,{0.0f, -1.0f, 0.0f});
	v[37] = CUSTOMFVF(1.0f,-1.0f,1.0f,{0.0f, -1.0f, 0.0f});
	v[38] = CUSTOMFVF(-1.0f,-1.0f,-1.0f,{0.0f, -1.0f, 0.0f});
	v[39] = CUSTOMFVF(1.0f,-1.0f,-1.0f,{0.0f, -1.0f, 0.0f});

	v[40] = CUSTOMFVF(1.0f,1.0f,1.0f,{0.0f, 0.0f, 1.0f});
	v[41] = CUSTOMFVF(1.0f,-1.0f,1.0f,{0.0f, 0.0f, 1.0f});
	v[42] = CUSTOMFVF(-1.0f,1.0f,1.0f,{0.0f, 0.0f, 1.0f});
	v[43] = CUSTOMFVF(-1.0f,-1.0f,1.0f,{0.0f, 0.0f, 1.0f});

	v[44] = CUSTOMFVF(1.0f,1.0f,-1.0f,{0.0f, 0.0f, -1.0f});
	v[45] = CUSTOMFVF(-1.0f,1.0f,-1.0f,{0.0f, 0.0f, -1.0f});
	v[46] = CUSTOMFVF(1.0f,-1.0f,-1.0f,{0.0f, 0.0f, -1.0f});
	v[47] = CUSTOMFVF(-1.0f,-1.0f,-1.0f,{0.0f, 0.0f, -1.0f});

	vb_cube->Unlock();
}
void GRAPHICS::InitMaterials() noexcept
{
	for (unsigned i = 0; i < 8; i++)
		ZeroMemory(&material_cube[i], sizeof(D3DMATERIAL9));

	material_cube[0].Diffuse = D3DXCOLOR(0.05f, 0.05f, 0.05f, 1.0f);
	material_cube[1].Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	material_cube[2].Diffuse = D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f);
	material_cube[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	material_cube[4].Diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	material_cube[5].Diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	material_cube[6].Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	material_cube[7].Diffuse = D3DXCOLOR(0.8f, 0.0f, 1.0f, 1.0f);

	for (unsigned i = 0; i < 3; i++)
		ZeroMemory(&material_wall[i], sizeof(D3DMATERIAL9));
	material_wall[0].Emissive = material_wall[0].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.35f, 0.15f);
	material_wall[1].Emissive = material_wall[1].Diffuse = D3DXCOLOR(0.4f, 0.6f, 0.45f, 0.25f);
	material_wall[2].Emissive = material_wall[2].Diffuse = D3DXCOLOR(0.6f, 0.8f, 0.65f, 0.35f);
}

GRAPHICS::GRAPHICS(HWND in_hwnd) : 
	hwnd(in_hwnd)
{
	try
	{
		d3d = Direct3DCreate9(D3D_SDK_VERSION);
		if (!d3d)
			throw 0;

		try
		{
			CreateDirect3DDevice();
			
			try
			{
				InitVBCube();
			}
			catch(...) { d3ddev->Release(); throw; }
		}
		catch(...) { d3d->Release(); throw; }
	}
	catch(...) { throw; }

	InitLights();
	InitMaterials();

	strWorld.rotationY = 0.0f;
	strWorld.rotationZ = 0.0f;
	strView.camera_pos = D3DXVECTOR3(6.0f, 0.0f, 0.0f);
	strView.look_at_point = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	strView.up_direction = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	strProjection.angle = 45;
	strProjection.plane_near = 1.0f;
	strProjection.plane_far = 100.0f;
	UpdateMatrixWorld();
	UpdateMatrixView();
	UpdateMatrixProjection();
}
GRAPHICS::~GRAPHICS() noexcept
{
	vb_cube->Release();
	d3ddev->Release();
	d3d->Release();
}

void GRAPHICS::BeginScene() noexcept
{
	d3ddev->Clear(0, 0, D3DCLEAR_TARGET, color_back, 1.0f, 0);
	d3ddev->Clear(0, 0, D3DCLEAR_ZBUFFER, color_back, 1.0f, 0);

	d3ddev->BeginScene();

	d3ddev->SetTransform(D3DTS_WORLD, &strWorld.matWorld);
	d3ddev->SetTransform(D3DTS_VIEW, &strView.matView);
	d3ddev->SetTransform(D3DTS_PROJECTION, &strProjection.matProjection);

	d3ddev->SetFVF(CUSTOMFVF_TYPE);
}
void GRAPHICS::EndScene() noexcept
{
	d3ddev->EndScene();
	HRESULT hres = d3ddev->Present(0, 0, 0, 0);
}

void GRAPHICS::UpdateMatrixWorld() noexcept
{
	D3DXMATRIX m1, m2;
	D3DXMatrixMultiply(
		&strWorld.matWorld,
		D3DXMatrixRotationZ(&m1, strWorld.rotationZ),
		D3DXMatrixRotationY(&m2, strWorld.rotationY));
	D3DXMatrixInverse(&strWorld.matWorldInv, 0, &strWorld.matWorld);
}
void GRAPHICS::UpdateMatrixView() noexcept
{
	D3DXMatrixLookAtLH(&strView.matView,
		&strView.camera_pos,
		&strView.look_at_point,
		&strView.up_direction);
	D3DXMatrixInverse(&strView.matViewInv, 0, &strView.matView);
}
void GRAPHICS::UpdateMatrixProjection() noexcept
{
	RECT rect;
	GetClientRect(hwnd, &rect);

	D3DXMatrixPerspectiveFovLH(&strProjection.matProjection,
		D3DXToRadian(strProjection.angle),
		static_cast<float>(rect.right-rect.left)/static_cast<float>(rect.bottom-rect.top),
		strProjection.plane_near,
		strProjection.plane_far);
}

void GRAPHICS::DrawCube() noexcept
{
	for (unsigned i = 0; i < 6; i++)
	{
		d3ddev->SetStreamSource(0, vb_cube, 4*i*sizeof(CUSTOMFVF), sizeof(CUSTOMFVF));
		d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
void GRAPHICS::DrawWallFrontIn() noexcept
{
	d3ddev->SetStreamSource(0, vb_cube, 24*sizeof(CUSTOMFVF), sizeof(CUSTOMFVF));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
void GRAPHICS::DrawWallFrontOut() noexcept
{
	d3ddev->SetStreamSource(0, vb_cube, 0, sizeof(CUSTOMFVF));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
void GRAPHICS::DrawWallBackIn() noexcept
{
	d3ddev->SetStreamSource(0, vb_cube, 28*sizeof(CUSTOMFVF), sizeof(CUSTOMFVF));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
void GRAPHICS::DrawWallBackOut() noexcept
{
	d3ddev->SetStreamSource(0, vb_cube, 4*sizeof(CUSTOMFVF), sizeof(CUSTOMFVF));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
void GRAPHICS::DrawWallLeftIn() noexcept
{
	d3ddev->SetStreamSource(0, vb_cube, 32*sizeof(CUSTOMFVF), sizeof(CUSTOMFVF));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
void GRAPHICS::DrawWallLeftOut() noexcept
{
	d3ddev->SetStreamSource(0, vb_cube, 8*sizeof(CUSTOMFVF), sizeof(CUSTOMFVF));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
void GRAPHICS::DrawWallRightIn() noexcept
{
	d3ddev->SetStreamSource(0, vb_cube, 36*sizeof(CUSTOMFVF), sizeof(CUSTOMFVF));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
void GRAPHICS::DrawWallRightOut() noexcept
{
	d3ddev->SetStreamSource(0, vb_cube, 12*sizeof(CUSTOMFVF), sizeof(CUSTOMFVF));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
void GRAPHICS::DrawWallTopIn() noexcept
{
	d3ddev->SetStreamSource(0, vb_cube, 40*sizeof(CUSTOMFVF), sizeof(CUSTOMFVF));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
void GRAPHICS::DrawWallTopOut() noexcept
{
	d3ddev->SetStreamSource(0, vb_cube, 16*sizeof(CUSTOMFVF), sizeof(CUSTOMFVF));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
void GRAPHICS::DrawWallBottomIn() noexcept
{
	d3ddev->SetStreamSource(0, vb_cube, 44*sizeof(CUSTOMFVF), sizeof(CUSTOMFVF));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
void GRAPHICS::DrawWallBottomOut() noexcept
{
	d3ddev->SetStreamSource(0, vb_cube, 20*sizeof(CUSTOMFVF), sizeof(CUSTOMFVF));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}