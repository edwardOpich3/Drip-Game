#ifdef GL_ES
precision lowp float;
#endif
uniform sampler2D bg_tex;
uniform bool al_use_tex;
varying vec4 varying_color;
varying vec2 varying_texcoord;
uniform vec2 texSize;
void main()
{
  if (al_use_tex)
    gl_FragColor = varying_color * texture2D(bg_tex, varying_texcoord % texSize);
  else
    gl_FragColor = varying_color;
}
