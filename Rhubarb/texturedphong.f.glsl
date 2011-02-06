varying vec4 vFragColor;
varying vec2 vTex;

uniform sampler2D tTexture;
void main(void) {
	gl_FragColor = vFragColor * texture2D(tTexture, vTex);
}