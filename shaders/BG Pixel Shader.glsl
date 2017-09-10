#ifdef GL_ES
precision lowp float;
#endif
uniform sampler2D bg_tex;
uniform bool al_use_tex;
varying vec4 varying_color;
varying vec2 varying_texcoord;

uniform vec2 texSize;
uniform vec2 bufferSize;
uniform vec2 cameraPos;
void main()
{
	if (al_use_tex)
	{
		vec2 myCoord = varying_texcoord;
		myCoord *= bufferSize;
		myCoord.x += cameraPos.x;
		myCoord.y -= cameraPos.y;
		gl_FragColor = varying_color * texture2D(bg_tex, mod((mod(myCoord, texSize) + texSize), texSize) / texSize);
	}
	else
		gl_FragColor = varying_color;
}
