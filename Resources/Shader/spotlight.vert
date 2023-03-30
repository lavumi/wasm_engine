#version 100
// Input vertex data, different for all executions of this shaderProgram.
attribute vec3 vertexPosition;
// Output data ; will be interpolated for each fragment.

// Values that stay constant for the whole mesh.
uniform mat4 Model;
uniform mat4 VP;


void main(){
    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  VP * Model * vec4(vertexPosition,1);
}
