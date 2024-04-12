#version 140
varying  vec4 vert_pos;
uniform sampler2D texture;
uniform bool hasTexture;
uniform vec2 lightPos;
uniform vec2 time;

// RGB values that represent an ambient 2D radius of lighting.

// the light intensity from the center of the circle 
uniform vec4 Intensity;
// Maximum radius of the lighting
uniform vec2 Radius;

// vec4 FragColor;

vec4 pixel;

void main() {
    //Ambient light
	vec4 ambient = vec4(0.02, 0.02, 0.5, 1.0);
	
	//Convert light to view coords
	vec2 lightPos1 = (gl_ModelViewProjectionMatrix * vec4(lightPos, 0, 1)).xy;
	
	//Calculate the vector from light to pixel (Make circular)
	vec2 lightToFrag = lightPos1 - vert_pos.xy;
	//lightToFrag.y = lightToFrag.y / 1.7;

	//Length of the vector (distance)
	float vecLength = clamp(length(lightToFrag) * 2, 0, 1);

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