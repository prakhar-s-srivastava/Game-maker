#version 330

struct ambientLight
{
    vec3 rgb; float intensity;

};
uniform  ambientLight ambient;

struct DirectionalLight
{
    vec3 position;
    vec3 direction;
    vec3 color ;
    float intensity;
};
uniform DirectionalLight directionalLights[100];
uniform  vec3 color;


in vec3 normal0;
in vec2 uv;
uniform sampler2D sampler;  

vec3 DirectionalLightEffect(int it)
{
    
        vec3 effect =vec3(0,0,0);
        if(directionalLights[it].intensity!= 0)
        {
            float apperentIntensity =max(dot(normalize(-1*directionalLights[it].direction),normal0),0.0);
            effect = directionalLights[it].intensity*apperentIntensity*directionalLights[it].color;
        }
        return effect;
}

void main()
{
    vec3 total_light = vec3(0,0,0);
    if(ambient.intensity != 0.0)
    total_light =ambient.rgb*ambient.intensity*vec3(1);
    

    for(int it=0;it<100;it++){
     total_light +=DirectionalLightEffect(it);
   }


    vec4 texturecolor ;
    texturecolor=texture2D(sampler, uv)*vec4(color,1.0);
    if( texturecolor == vec4(0,0,0,1))
    {
         texturecolor = vec4(color,1.0);
    }
   

    gl_FragColor = vec4(total_light,1.0)+ texturecolor ;
    
    

}

