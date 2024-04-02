struct vertexOut
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct vertexIn
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

cbuffer cbPerObject : register(b0)
{
    matrix world;
    matrix view;
    matrix projection;
}

vertexOut vs_main(vertexIn input)
{
    vertexOut output;
    output.pos = mul(float4(input.pos, 1.0f), world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    output.uv = input.uv;
    output.normal = input.normal;
    
    return output;
}