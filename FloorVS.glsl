#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 v_position;


// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;



void main()
{
   
    // TODO(student): Compute gl_Position
    gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
