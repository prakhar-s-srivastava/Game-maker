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



in vec3 normal0;


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

    //gl_FragColor = total_light*vec4(0.6,0.1,0.4,1.0);
    gl_FragColor = vec4(total_light,1.0)*vec4(1.0,1.0,1.0,1.0);

}

