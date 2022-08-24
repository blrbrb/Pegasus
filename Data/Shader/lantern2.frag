
varying vec4 vert_pos;

uniform sampler2D texture;
uniform bool hasTexture;
uniform vec2 lightPos; 
uniform int lights;
uniform float position_vector[10]; 


void main()
{
vec4 ambient;
	//Ambient light
	
		 ambient = vec4(0.2, 0.2, 0.9, 1.0 );
    
	
		
	
	//Convert light to view coords
	lightPos = (gl_ModelViewProjectionMatrix * vec4(lightPos, 0, 1)).xy;
	
	//Calculate the vector from light to pixel (Make circular) 
	//is there any way to make the light vector wrap around mobile entities? 

	vec2 lightToFrag = lightPos - vert_pos.xy;
	lightToFrag.y = lightToFrag.y / 1.7;

	//Length of the vector (distance) 
	//cont the ambient occulsion of the shadow, and light leaving the position of whichever entity's center is set /center var
	float vecLength = clamp(length(lightToFrag) *2, 0, 1);

    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // multiply it by the color and lighting
	if(hasTexture == true)
	{
		gl_FragColor = gl_Color * pixel * (clamp(ambient + vec4(1-vecLength, 1-vecLength, 1-vecLength, 1), 0, 1));
	}
	else
	{
		gl_FragColor = gl_Color;
	}
}