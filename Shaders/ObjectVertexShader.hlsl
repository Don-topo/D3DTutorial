struct vOut
{
    float4 pos : SV_POSITION;
    float4 color : COLOR0;
};

struct vIn
{
    float3 pos : POSITION;
    float4 color : COLOR;
};

vOut vs_main(vIn input)
{
    vOut output;    
    output.pos = float4(input.pos, 1.0f);
    output.color = input.color;
    
    return output;
}