Texture2D baseColor : register(t0);
Texture2D emmisiveMap : register(t1);
Texture2D normalMap : register(t2);

SamplerState sampleView : register(s0);

struct pixelIn
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

float4 ps_main(pixelIn input) : SV_Target
{
    return baseColor.Sample(sampleView, input.uv) + emmisiveMap.Sample(sampleView, input.uv);
}