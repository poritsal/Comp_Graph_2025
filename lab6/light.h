#pragma once

#include <d3dcompiler.h>
#include <dxgi.h>
#include <d3d11.h>
#include <directxmath.h>
#include <vector>

#include "structures.h"

using namespace DirectX;

class Light {
public:
	HRESULT init(ID3D11Device* device, ID3D11DeviceContext* context, int screenWidth, int screenHeight, XMFLOAT4 color, XMFLOAT4 position);
	void realize();
	void resize(int screenWidth, int screenHeight) {};
	void render(ID3D11DeviceContext* context);
	bool frame(ID3D11DeviceContext* context, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPos);
	XMFLOAT4 getColor() { return color; };
	XMFLOAT4 getPosition() { return position; };
private:
	void generateSphere(UINT LatLines, UINT LongLines, std::vector<SimpleVertex>& vertices, std::vector<UINT>& indices);

	ID3D11Buffer* g_pVertexBuffer = nullptr;
	ID3D11Buffer* g_pIndexBuffer = nullptr;
	ID3D11Buffer* g_pWorldMatrixBuffer = nullptr;
	ID3D11Buffer* g_pSceneMatrixBuffer = nullptr;
	ID3D11RasterizerState* g_pRasterizerState = nullptr;

	ID3D11InputLayout* g_pVertexLayout = nullptr;
	ID3D11VertexShader* g_pVertexShader = nullptr;
	ID3D11PixelShader* g_pPixelShader = nullptr;

	UINT numSphereVertices = 0;
	UINT numSphereFaces = 0;
	float radius = 0.1f;

	XMFLOAT4 color;
	XMFLOAT4 position;
};