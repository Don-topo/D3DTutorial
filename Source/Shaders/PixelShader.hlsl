struct pixelIn
{
    float4 position : SV_Position;
    float4 color : COLOR;
};

float4 main(pixelIn input) : SV_Target
{
    return input.color;
}