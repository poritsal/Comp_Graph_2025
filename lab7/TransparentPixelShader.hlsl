#include "TransparentCB.hlsli"
#include "CalculateColor.hlsli"

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float4 worldPos : POSITION;
};
float4 main(PS_INPUT input) : SV_TARGET
{
    return float4(CalculateColor(color.xyz, float3(1, 0, 0), input.worldPos.xyz, 0.0, true), color.w);
}