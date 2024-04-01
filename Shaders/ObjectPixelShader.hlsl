struct pixelIn
{
    float4 pos : SV_Position;
    float4 color : COLOR0;
};

float4 ps_main(pixelIn input) : SV_Target
{
    return input.color;
}