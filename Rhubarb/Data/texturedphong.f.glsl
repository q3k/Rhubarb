#version 130

out vec4 vFragColor;

uniform vec4 AmbientColor;
uniform vec4 DiffuseColor;
uniform float Shininess;
uniform sampler2D Texture;

smooth in vec3 vNormalSmooth;
smooth in vec3 vLightDir;
smooth in vec2 vTextureSmooth;

void main(void)
{ 
    float Intensity = max(AmbientColor.r, dot(normalize(vNormalSmooth), normalize(vLightDir)));
    vFragColor = Intensity * texture2D(Texture, vTextureSmooth);
	
    vFragColor += AmbientColor;

    vec3 Reflection = normalize(reflect(-normalize(vLightDir), normalize(vNormalSmooth)));
    float Specular = max(0.0, dot(normalize(vNormalSmooth), Reflection));
    if(Intensity != 0)
	{
        float fSpec = pow(Specular, Shininess);
        vFragColor.rgb += vec3(fSpec, fSpec, fSpec);
    }
}
    