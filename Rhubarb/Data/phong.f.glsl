#version 130

out vec4 vFragColor;

uniform vec4 AmbientColor;
uniform vec4 DiffuseColor;
uniform float Shininess;

smooth in vec3 vNormalSmooth;
smooth in vec3 vLightDir;

void main(void)
{ 
    float Intensity = max(0.0, dot(normalize(vNormalSmooth), normalize(vLightDir)));
    vFragColor = Intensity * DiffuseColor;
	
    vFragColor += AmbientColor;

    vec3 Reflection = normalize(reflect(-normalize(vLightDir), normalize(vNormalSmooth)));
    float Specular = max(0.0, dot(normalize(vNormalSmooth), Reflection));
    if(Intensity != 0)
	{
        float fSpec = pow(Specular, Shininess);
        vFragColor.rgb += vec3(fSpec, fSpec, fSpec);
    }
}
    