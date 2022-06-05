#version 330 core

out vec4 frag_color;

// ================ < --- TODOes --- > ================ //

//TODO: Define uniforms for the center and the side-length

uniform vec4 inside_color = vec4(1.0, 0.0, 0.0, 1.0);
uniform vec4 outside_color = vec4(0.0, 0.0, 0.0, 1.0);

//==// Define Diamond (Center & Side Length)
uniform vec2 center;
uniform float side_length;

void main(){
    //TODO: Write code that will draw the Diamond

    float x_diff = abs(gl_FragCoord.x - center[0]);
    float y_diff = abs(gl_FragCoord.y - center[1]);

    float manhattan_distance = x_diff + y_diff;
    float half_length = side_length / 2.0;

    if(manhattan_distance <= half_length){ //==// Inside The Diamond
        frag_color = inside_color;

    } else { //==// Outside The Diamond
        frag_color = outside_color;

    }
}

// ================ < --- End --- > ================ //