#pragma once

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <directxmath.h>
#include <ctime>
#include <chrono>
#include <corecrt_math_defines.h>

#include "renderTexture.h"
#include "postprocessing.h"
#include "camera.h"
#include "scene.h"


class Renderer {
public:
	static Renderer& getInstance();
	Renderer(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;
	HRESULT init(const HWND& g_hWnd, const HINSTANCE& g_hInstance, UINT screenWidth, UINT screenHeight);
	bool frame();
	void render();
	void deviceCleanup();
	void resizeWindow(const HWND& g_hWnd);
	void mouseMoved(int x, int y);
	void mouseRBPressed(bool pressed, int x, int y);
	void mouseWheel(int wheel);
private:
	HRESULT initDevice(const HWND& g_hWnd);
	HRESULT initBackBuffer();
	void resize(UINT screenWidth, UINT screenHeight);
	Renderer() = default;

	D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device* g_pd3dDevice = nullptr;
	ID3D11Device1* g_pd3dDevice1 = nullptr;
	ID3D11DeviceContext* g_pImmediateContext = nullptr;
	ID3D11DeviceContext1* g_pImmediateContext1 = nullptr;
	IDXGISwapChain* g_pSwapChain = nullptr;
	IDXGISwapChain1* g_pSwapChain1 = nullptr;
	ID3D11RenderTargetView* g_pRenderTargetView = nullptr;
	ID3D11Texture2D* g_pDepthBuffer = nullptr;
	ID3D11DepthStencilView* g_pDepthBufferDSV = nullptr;

	RenderTexture renderTexture;
	Postprocessing postprocessing;

	Camera camera;
	Scene scene;

	bool m_fixFrustumCulling;
	bool m_usePosteffect;
	const char* m_modes[3];
	int m_currentMode = 0;

	long long m_totalFrameTime[3]; // 0 - CPU mode, 1 - instancing, 2 - GPU culling + instancing
	long long m_totalRenderTime[3];
	int m_frameCount[3]; // Frame count for every draw mode


	UINT m_width;
	UINT m_height;
	bool m_rbPressed;
	int m_prevMouseX;
	int m_prevMouseY;
	float angle_velocity = XM_PIDIV2;
};