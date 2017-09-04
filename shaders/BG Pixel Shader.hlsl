bool al_use_tex;
texture bg_tex;
float2 texSize;
float2 bufferSize;
float2 cameraPos;
sampler2D s = sampler_state
{
	texture = <bg_tex>;
};

float4 ps_main(VS_OUTPUT Input) : COLOR0
{
	if (al_use_tex)
	{
		float2 myCoord = Input.TexCoord;
		myCoord *= bufferSize;
		myCoord += cameraPos;
		return Input.Color * tex2D(s, (((myCoord % texSize) + texSize) % texSize) / texSize);
	}
	else
	{
		return Input.Color;
	}
}
