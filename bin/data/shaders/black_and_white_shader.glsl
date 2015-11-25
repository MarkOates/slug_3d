
uniform sampler2D backBuffer;
uniform float r;
uniform float g;
uniform float b;
uniform float ratio;

void main()
{
	vec4 color;
	float avg, dr, dg, db;
	color = texture2D(backBuffer, gl_TexCoord[0].st);
	avg = (color.r + color.g + color.b) / 3.0;
	color.r = avg;
	color.g = avg;
	color.b = avg;
	gl_FragColor = color;
}
