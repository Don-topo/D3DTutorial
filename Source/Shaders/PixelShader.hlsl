Texture2D tex2D;
SamplerState text2DSampler;

struct pixelIn
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD0;
};

float4 main(pixelIn input) : SV_Target
{
    return tex2D.Sample(text2DSampler, input.uv);
}