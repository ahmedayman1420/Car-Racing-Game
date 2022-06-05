#version 330 core

out vec4 frag_color;

//TODO: Define uniforms for the center and the radius

// ================ < --- TODOes --- > ================ //

//==// Define Circle (Center & Raduis)
uniform vec2 center;
uniform float radius;

uniform vec4 inside_color = vec4(1.0, 0.0, 0.0, 1.0);
uniform vec4 outside_color = vec4(0.0, 0.0, 0.0, 1.0);

void main() {
    //TODO: Write code that will draw the circle

      
    //==// By Using Euclidean Law, Calculate The Distance, The Point Inisde The Circle If The Distance From (cent, point) less Than raduis

    float x_pow2 = (gl_FragCoord.x - center[0]) * (gl_FragCoord.x - center[0]);
    float y_pow2 = (gl_FragCoord.y - center[1]) * (gl_FragCoord.y - center[1]);

    float euclidean_dist = sqrt(x_pow2 + y_pow2);

    if(euclidean_dist <= radius) { //==// Inside The Circle
        frag_color = inside_color;
    
    } else {//==// Outside The Circle
    
        frag_color = outside_color;
    }
}

// ================ < --- End --- > ================ //
