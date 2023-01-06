
/* Color palette Debugging */
#define BLACK           vec3(0.0, 0.0, 0.0)
#define WHITE           vec3(1.0, 1.0, 1.0)
#define RED             vec3(1.0, 0.0, 0.0)
#define GREEN           vec3(0.0, 1.0, 0.0)
#define BLUE            vec3(0.0, 0.0, 1.0)
#define YELLOW          vec3(1.0, 1.0, 0.0)
#define CYAN            vec3(0.0, 1.0, 1.0)
#define MAGENTA         vec3(1.0, 0.0, 1.0)
#define ORANGE          vec3(1.0, 0.5, 0.0)
#define PURPLE          vec3(1.0, 0.0, 0.5)
#define LIME            vec3(0.5, 1.0, 0.0)
#define ACQUA           vec3(0.0, 1.0, 0.5)
#define VIOLET          vec3(0.5, 0.0, 1.0)
#define AZUR            vec3(0.0, 0.5, 1.0)


/* Object struct */
struct Light { vec2 radius; vec4 color; vec2 position; };

/* Uniforms */
#define MAX_LIGHTS = 16; 
in vec4 vert_pos;
uniform sampler2D texture;
uniform vec2 resolution;
uniform vec2 lightPos;
uniform vec2 time;
uniform float value1;
uniform float value2;
uniform float value3; 
// The RGB values are the ambient light color
// and the alpha is the ambient intensity
uniform vec4 Color;
// The RGB values are the light color
// and the alpha is the light intensity
uniform vec4 Intensity;
// Maximum radius of the light
uniform vec2 Radius;
uniform int lights_on_screen; 

struct light 
{
   vec2 position; 
   vec4 color; 
   vec2 radius; 
};


uniform light lights;  


void main() {
 
   // Light's position
   //debug 
   


 lightPos = (gl_ModelViewProjectionMatrix * vec4(lightPos, 0, 1)).xy;
 vec2 position = lightPos - vert_pos.xy; 
 position.y = position.y / 1.7;
  // Makes the light change its size slightly to make a fire effect
 float maxDistance = Radius.x + 0.015*sin(time.x);
  // Gets the distance from the light's position and the fragment coord
 float distance = distance(gl_FragCoord.xy/resolution.xx, position);
  // Calculates the amount of light for the fragment
 float value = value1 - smoothstep(-0.2, maxDistance, distance);

  // Gets the original color from the texture
 vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

  // Applies the ambient light to the original pixel color
 vec3 ambient = pixel.rgb * Color.rgb * Color.a;

  // Calculates the light color for the pixel
 vec3 light = Intensity.rgb * Intensity.a * clamp(value, 0.2, 1.0); 
 

 vec3 intensity = ambient + light;
 vec3 final = pixel.rgb * Intensity;
 

 gl_FragColor = gl_Color * vec4(final, pixel.a);
}