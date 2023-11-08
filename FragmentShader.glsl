#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position0;
uniform vec3 light_position1;
uniform vec3 light_position2;
uniform vec3 light_position3;
uniform vec3 light_position4;
uniform vec3 light_position5;
uniform vec3 light_position6;
uniform vec3 light_position7;
uniform vec3 light_position8;

uniform sampler2D texture_1;

uniform float time;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform int scene_type;


// TODO(student): Declare any other uniforms
uniform int type_of_light;
uniform vec3 light_color;
uniform vec3 light_color1;
uniform vec3 light_color2;
uniform vec3 light_color3;
uniform vec3 light_color4;
uniform vec3 light_color5;
uniform vec3 light_color6;
uniform vec3 light_color7;
uniform vec3 light_color8;

uniform vec3 spotlightPosition;
uniform vec3 spotlightColor;
uniform vec3 spotlightDirection;

uniform vec3 spotlightPosition1;
uniform vec3 spotlightColor1;

uniform vec3 spotlightPosition2;
uniform vec3 spotlightColor2;
uniform vec3 spotlightPosition3;
uniform vec3 spotlightColor3;




// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Define ambient, diffuse and specular light components
  
  if(scene_type == 1){
    float diffuse_light = 0;
    float specular_light = 0;
    vec3 N = normalize(world_normal);
    vec3 L = normalize( light_position0 - world_position );

    float diffuse_light2 = 0;
    float specular_light2 = 0;
    vec3 L2 = normalize( light_position2 - world_position );

    vec3 V = normalize( eye_position - world_position );
    vec3 H = normalize( L + V );

    vec3 H2 = normalize( L2 + V );

    vec3 R = normalize( reflect (L, world_normal));
    vec3 R2 = normalize( reflect (L2, world_normal));

   // ambient_light = material_kd * ambient_light;

    float diffuse_light1 = 0;
    float specular_light1 = 0;
    vec3 L1 = normalize( light_position1 - world_position );
    vec3 H1 = normalize( L1 + V );
    vec3 R1 = normalize( reflect (L1, world_normal));


    float diffuse_light3 = 0;
    float specular_light3 = 0;
    vec3 L3 = normalize( light_position3 - world_position );
    vec3 H3 = normalize( L3 + V );
    vec3 R3 = normalize( reflect (L3, world_normal));

    float diffuse_light4 = 0;
    float specular_light4 = 0;
    vec3 L4 = normalize( light_position4 - world_position );
    vec3 H4 = normalize( L4 + V );
    vec3 R4 = normalize( reflect (L4, world_normal));


     float diffuse_light5 = 0;
    float specular_light5 = 0;
    vec3 L5 = normalize( light_position5 - world_position );
    vec3 H5 = normalize( L5 + V );
    vec3 R5 = normalize( reflect (L5, world_normal));

    float diffuse_light6 = 0;
    float specular_light6 = 0;
    vec3 L6 = normalize( light_position6 - world_position );
    vec3 H6 = normalize( L6 + V );
    vec3 R6 = normalize( reflect (L6, world_normal));


     float diffuse_light7 = 0;
    float specular_light7 = 0;
    vec3 L7 = normalize( light_position7 - world_position );
    vec3 H7 = normalize( L7 + V );
    vec3 R7 = normalize( reflect (L7, world_normal));

     float diffuse_light8 = 0;
    float specular_light8 = 0;
    vec3 L8 = normalize( light_position8 - world_position );
    vec3 H8 = normalize( L8 + V );
    vec3 R8 = normalize( reflect (L8, world_normal));


    diffuse_light = material_kd * 1 * max (dot(world_normal,L), 0);
    diffuse_light1 = material_kd * 1 * max (dot(world_normal,L1), 0);
    diffuse_light2 = material_kd * 1 * max (dot(world_normal,L2), 0);
    diffuse_light3 = material_kd * 1 * max (dot(world_normal,L3), 0);
    diffuse_light4 = material_kd * 1 * max (dot(world_normal,L4), 0);
    diffuse_light5 = material_kd * 1 * max (dot(world_normal,L5), 0);
    diffuse_light6 = material_kd * 1 * max (dot(world_normal,L6), 0);
    diffuse_light7 = material_kd * 1 * max (dot(world_normal,L7), 0);
    diffuse_light8 = material_kd * 1 * max (dot(world_normal,L8), 0);






    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!
    float light_int = 0.1;
    if (diffuse_light > 0)
    {
        specular_light =  material_ks *light_int* pow(max(dot(world_normal, H), 0), material_shininess) ;
    }

     if (diffuse_light1 > 0)
    {
        specular_light1 =  material_ks *light_int* pow(max(dot(world_normal, H1), 0), material_shininess) ;
    }

     if (diffuse_light2 > 0)
    {
        specular_light2 =  material_ks *light_int* pow(max(dot(world_normal, H2), 0), material_shininess) ;
    }

     if (diffuse_light3 > 0)
    {
        specular_light3 =  material_ks *light_int* pow(max(dot(world_normal, H3), 0), material_shininess) ;
    }

     if (diffuse_light4 > 0)
    {
        specular_light4 =  material_ks *light_int* pow(max(dot(world_normal, H4), 0), material_shininess) ;
    }

     if (diffuse_light5 > 0)
    {
        specular_light5 =  material_ks*light_int * pow(max(dot(world_normal, H5), 0), material_shininess) ;
    }

     if (diffuse_light6 > 0)
    {
        specular_light6 =  material_ks *light_int* pow(max(dot(world_normal, H6), 0), material_shininess) ;
    }

     if (diffuse_light7 > 0)
    {
        specular_light7 =  material_ks *light_int* pow(max(dot(world_normal, H7), 0), material_shininess) ;
    }

     if (diffuse_light8 > 0)
    {
        specular_light8 =  material_ks *light_int* pow(max(dot(world_normal, H8), 0), material_shininess) ;
    }

    // TODO(student): If (and only if) the light is a spotlight, we need to do
    // some additional things.

    float light = 0.f;
    float light1 = 0.f;
    float light2 = 0.f;
    float light3 = 0.f;
    float light4 = 0.f;
    float light5 = 0.f;
    float light6 = 0.f;
    float light7 = 0.f;
    float light8 = 0.f;



    float fact = 0.f;
    float fact1 = 0.f;
    float fact2 = 0.f;
    float fact3 = 0.f;
    float fact4 = 0.f;
    float fact5 = 0.f;
    float fact6 = 0.f;
    float fact7 = 0.f;
    float fact8 = 0.f;


    float cut_off_angle = 30;
	//if (type_of_light == 1)
	//{
		float cut_off= radians(cut_off_angle);
		float spot_light= dot(-L, light_direction);
		
		
		float d = distance(light_position0, world_position);
         if(d <1.5){
		float attenuation_factor =(pow(1.5- d,2));
		fact = attenuation_factor;
        }

        float d1 = distance(light_position1, world_position);
         if(d1 <2){
		float attenuation_factor1 = (pow(1.5-d1,2));
		fact1 = attenuation_factor1;
        }

        float d2 = distance(light_position2, world_position);
         if(d2 <1.5){
		float attenuation_factor2 = (pow(1.5-d2,2));
		fact2 = attenuation_factor2;
        }

        float d3 = distance(light_position3, world_position);
         if(d3 <1.5){
		float attenuation_factor3= (pow(1.5-d3,2));
		fact3 = attenuation_factor3;
        }

        float d4 = distance(light_position4, world_position);
         if(d4 <1.5){
		float attenuation_factor4 = (pow(1.5-d4,2));
		fact4 = attenuation_factor4;
        }

        float d5 = distance(light_position5, world_position);
         if(d5 <1.5){
		float attenuation_factor5 =(pow(1.5-d5,2));
		fact5 = attenuation_factor5;
        }
        float d6 = distance(light_position6, world_position);
         if(d6 <1.5){
		float attenuation_factor6 = (pow(1.5-d6,2));
		fact6 = attenuation_factor6;
        }

        float d7 = distance(light_position7, world_position);
         if(d7 <1.5){
		float attenuation_factor7 = (pow(1.5-d7,2));
		fact7 = attenuation_factor7;
        }

        float d8 = distance(light_position8, world_position);
         if(d8 <1.5){
		float attenuation_factor8 = (pow(1.5-d8,2));
		fact8 = attenuation_factor8;
        }
	//}

   
    // TODO(student): Compute the total light. You can just add the components
    // together, but if you're feeling extra fancy, you can add individual
    // colors to the light components. To do that, pick some vec3 colors that
    // you like, and multiply them with the respective light components.

        
     light =  fact * (diffuse_light + specular_light);
     
     light1 =  fact1 * (diffuse_light1 + specular_light1);
     light2 =  fact2 * (diffuse_light2 + specular_light2);
     light3 =  fact3 * (diffuse_light3 + specular_light3);
     light4 =  fact4 * (diffuse_light4 + specular_light4);
     light5 =  fact5 * (diffuse_light5 + specular_light5);
     light6 =  fact6 * (diffuse_light6 + specular_light6);
     light7 =  fact7 * (diffuse_light7 + specular_light7);
     light8 =  fact8 * (diffuse_light8 + specular_light8);
     
    vec3 colour = light_color * light +  light_color1 * light1 +  light_color2 * light2+  light_color3* light3+  light_color4 * light4+ light_color5 * light5+  light_color6 * light6+  light_color7 * light7+  light_color8 * light8;
   
     out_color = vec4(colour, 1.f);

   }else if(scene_type == 2){
     

      float diffuse_light = 0;
    float specular_light = 0;
    vec3 N = normalize(world_normal);
    vec3 L = normalize( spotlightPosition - world_position );
     vec3 V = normalize( eye_position - world_position );
    vec3 H = normalize( L + V );
    vec3 R = normalize( reflect (L, world_normal));
    diffuse_light = material_kd  * max (dot(world_normal,L), 0);

     float light_int = 1;
    if (diffuse_light > 0)
    {
        specular_light =  material_ks *light_int* pow(max(dot(world_normal, H), 0), material_shininess) ;
    }
    float light = 0.f;
    float fact = 0.f;
    float cut_off_angle = 60;
	if (type_of_light == 0)
	{
		float cut_off= radians(cut_off_angle);
		float spot_light= dot(-L, spotlightDirection);
		
		if (spot_light > cos(cut_off))
		{	 
			// Quadratic attenuation
			float linear_att = (spot_light - cos(cut_off)) / (1.f - cos(cut_off));
			float light_att_factor	= pow(linear_att, 2);
			fact = light_att_factor;
		} 
       /// else
		//{
		//	light = ambient_light;  // There is no spot light, but there is light from other objects
       //     light2 = ambient
		//}
	} else
	{
		float d = distance(spotlightPosition, world_position);
		float attenuation_factor = 1.f /(pow(d,2));
		fact = attenuation_factor;
     }
     light =  fact * (diffuse_light + specular_light);
     //spotlightColor = glm::vec3(0,1,0);




     
      float diffuse_light1 = 0;
    float specular_light1 = 0;
    vec3 N1 = normalize(world_normal);
    vec3 L1 = normalize( spotlightPosition1 - world_position );
     vec3 V1 = normalize( eye_position - world_position );
    vec3 H1 = normalize( L1 + V1 );
    vec3 R1 = normalize( reflect (L1, world_normal));
    diffuse_light1 = material_kd  * max (dot(world_normal,L1), 0);

     float light_int1 = 1;
    if (diffuse_light1 > 0)
    {
        specular_light1 =  material_ks *light_int1* pow(max(dot(world_normal, H1), 0), material_shininess) ;
    }
    float light1 = 0.f;
    float fact1 = 0.f;
    float cut_off_angle1 = 30;
	if (type_of_light == 1)
	{
		float cut_off1= radians(cut_off_angle);
		float spot_light1= dot(-L1, spotlightDirection);
		
		if (spot_light1 > cos(cut_off1))
		{	 
			// Quadratic attenuation
			float linear_att1 = (spot_light1 - cos(cut_off1)) / (1.f - cos(cut_off1));
			float light_att_factor1	= pow(linear_att1, 2);
			fact1 = light_att_factor1;
		} 
       /// else
		//{
		//	light = ambient_light;  // There is no spot light, but there is light from other objects
       //     light2 = ambient
		//}
	} else
	{
		float d1 = distance(spotlightPosition1, world_position);
		float attenuation_factor1 = 1.f /(pow(d1,2));
		fact1 = attenuation_factor1;
     }
     light1 =  fact1 * (diffuse_light1 + specular_light1);

      
      float diffuse_light2 = 0;
    float specular_light2 = 0;
    vec3 N2 = normalize(world_normal);
    vec3 L2 = normalize( spotlightPosition2 - world_position );
     vec3 V2 = normalize( eye_position - world_position );
    vec3 H2 = normalize( L2 + V2 );
    vec3 R2 = normalize( reflect (L2, world_normal));
    diffuse_light2 = material_kd  * max (dot(world_normal,L2), 0);

     float light_int2 = 1;
    if (diffuse_light2 > 0)
    {
        specular_light2 =  material_ks *light_int2* pow(max(dot(world_normal, H2), 0), material_shininess) ;
    }
    float light2 = 0.f;
    float fact2 = 0.f;
    float cut_off_angle2 = 30;
	if (type_of_light == 1)
	{
		float cut_off2= radians(cut_off_angle);
		float spot_light2= dot(-L2, spotlightDirection);
		
		if (spot_light2 > cos(cut_off2))
		{	 
			// Quadratic attenuation
			float linear_att2 = (spot_light2 - cos(cut_off2)) / (1.f - cos(cut_off2));
			float light_att_factor2	= pow(linear_att2, 2);
			fact2 = light_att_factor2;
		} 
       /// else
		//{
		//	light = ambient_light;  // There is no spot light, but there is light from other objects
       //     light2 = ambient
		//}
	} else
	{
		float d2 = distance(spotlightPosition2, world_position);
		float attenuation_factor2 = 1.f /(pow(d2,1));
		fact2 = attenuation_factor2;
     }
     light2 =  fact2 * (diffuse_light2 + specular_light2);


     float diffuse_light3 = 0;
    float specular_light3 = 0;
    vec3 N3 = normalize(world_normal);
    vec3 L3 = normalize( spotlightPosition3 - world_position );
     vec3 V3 = normalize( eye_position - world_position );
    vec3 H3 = normalize( L3 + V3 );
    vec3 R3 = normalize( reflect (L3, world_normal));
    diffuse_light3 = material_kd  * max (dot(world_normal,L3), 0);

     float light_int3 = 1;
    if (diffuse_light3 > 0)
    {
        specular_light3 =  material_ks *light_int3* pow(max(dot(world_normal, H3), 0), material_shininess) ;
    }
    float light3 = 0.f;
    float fact3 = 0.f;
    float cut_off_angle3= 30;
	if (type_of_light == 1)
	{
		float cut_off3= radians(cut_off_angle);
		float spot_light3= dot(-L3, spotlightDirection);
		
		if (spot_light3 > cos(cut_off3))
		{	 
			// Quadratic attenuation
			float linear_att3 = (spot_light3 - cos(cut_off3)) / (1.f - cos(cut_off3));
			float light_att_factor3	= pow(linear_att3, 2);
			fact3 = light_att_factor3;
		} 
       /// else
		//{
		//	light = ambient_light;  // There is no spot light, but there is light from other objects
       //     light2 = ambient
		//}
	} else
	{
		float d3 = distance(spotlightPosition3, world_position);
		float attenuation_factor3 = 1.f /(pow(d3,2));
		fact3 = attenuation_factor3;
     }
     light3 =  fact3 * (diffuse_light3 + specular_light3);


     vec3 colour = spotlightColor * light + spotlightColor1 * light1  + spotlightColor2 * light2 + spotlightColor3 * light3;

     //vec3 colour = glm::vec3(1,0,0);
     out_color = vec4(colour, 1.f);
    
   } else{


         float diffuse_light = 0;
    float specular_light = 0;
    vec3 N = normalize(world_normal);
    vec3 L = normalize( vec3(4, 2.7, 4) - world_position );
     vec3 V = normalize( eye_position - world_position );
    vec3 H = normalize( L + V );
    vec3 R = normalize( reflect (L, world_normal));
    diffuse_light = 0.5  * max (dot(world_normal,L), 0);

     float light_int = 0.5;
    if (diffuse_light > 0)
    {
        specular_light =  0.5 *light_int* pow(max(dot(world_normal, H), 0), 0) ;
    }
    float light = 0.f;
    float fact = 0.f;
    
	
	float d = distance(vec3(4, 2.7, 4), world_position);
    if(d<15){
	float attenuation_factor = (pow(15-d,2));
	fact = attenuation_factor;
    }
     if(fact!=0){
     light =  fact * (diffuse_light + specular_light);
     //spotlightColor = glm::vec3(0,1,0);
     }
    
        vec3 light_dir = world_position - vec3(4, 2.7, 4);
 
        // texcoord este coordonata de textura utilizata pentru esantionare
        vec2 texcoord;
        texcoord.x = (1.0 / (2 * 3.14159)) * atan (light_dir.x, light_dir.z);
        texcoord.y = (1.0 / 3.14159) * acos (light_dir.y / length (light_dir));
 
        texcoord.x += time * 0.05;
        texcoord.y += time * 0.05;
     


        // color este culoarea corespunzatoare pozitiei world_position
        vec3 color = texture (texture_1, texcoord).xyz;
        vec3 colour;
     if(fact!=0){

         colour = color*(diffuse_light + specular_light);
        }
        out_color = vec4(colour, 1.f);
   }

    

	
    

}
