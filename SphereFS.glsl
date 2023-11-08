#version 330

// Input
in vec2 texcoord;
in vec3 world_position;
in vec3 world_normal;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform vec3 disco_ball_position;
uniform vec3 light_dir;
uniform float time;
// TODO(student): Declare various other uniforms
uniform bool mix_textures;
// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Calculate the out_color using the texture2D() function.
	vec3 light_dir = world_position - disco_ball_position;
 
	// texcoord este coordonata de textura utilizata pentru esantionare
	vec2 texcoord;
	texcoord.x = (1.0 / (2 * 3.14159)) * atan (light_dir.x, light_dir.z);
	texcoord.y = (1.0 / 3.14159) * acos (light_dir.y / length (light_dir));
	 texcoord.x += time* 0.05;
     texcoord.y += time*0.05;
	

    vec4 colour1 = texture2D(texture_1, texcoord);
	
		out_color = colour1;
	
    if (out_color.a < .5f)
	{
		discard;
	}

}
