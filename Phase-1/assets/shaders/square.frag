#version 330 core

out vec4 frag_color;

//TODO: Define uniforms for the center and the side-length

// ================ < --- TODOes --- > ================ //

//==// Define Square (Center & Side Length)
uniform vec2 center;
uniform float side_length;

uniform vec4 inside_color = vec4(1.0, 0.0, 0.0, 1.0);
uniform vec4 outside_color = vec4(0.0, 0.0, 0.0, 1.0);

void main() {
    //TODO: Write code that will draw the square

    float x_diff = abs(gl_FragCoord.x - center[0]);
    float y_diff = abs(gl_FragCoord.y - center[1]);

    float norm_distance = max(x_diff, y_diff);
    float half_length = side_length / 2.0;

    if(norm_distance <= half_length) { //==// Inside The Square
        frag_color = inside_color;

    } else {  //==// Outside The Square
        frag_color = outside_color;
    }
}

// ================ < --- End --- > ================ //
