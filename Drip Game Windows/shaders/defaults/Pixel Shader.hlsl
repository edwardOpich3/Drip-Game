bool al_use_tex;
texture al_tex;
sampler2D s = sampler_state {
   texture = <al_tex>;
};

float4 ps_main(VS_OUTPUT Input) : COLOR0
{
   if (al_use_tex) {
      return Input.Color * tex2D(s, Input.TexCoord);
   }
   else {
      return Input.Color;
   }
}
