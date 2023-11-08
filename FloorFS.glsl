#version 330



in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 object_color;
uniform vec3 light_position;
//uniform vec3 c;
uniform vec3 light_direction;
uniform vec3 eye_position;

uniform int scene_type;


uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// TODO(student): Declare any other uniforms

uniform vec3 spotlightPosition;
uniform vec3 spotlightColor;
uniform vec3 spotlightDirection;


uniform int type_of_light;
//uniform float cut_off_angle;

// Output
layout(location = 0) out vec4 out_color;


void main()
{

        
    if(scene_type == 1){

       
        vec3 color;
       

        float d = distance(world_position, light_position); 
    
         
        float att =0.f;
        if(d <2){
            att = pow(2 - d, 2);
        }
        if(att==0){
            color =  object_color;
        }else{
        color =  object_color  * att ;
        }
  
        out_color = vec4(color, 1);
    }
  
}
