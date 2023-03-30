#version 100
// Input vertex data, different for all executions of this shaderProgram.
attribute vec3 vertexPosition;
attribute vec2 aTexCoord;

// Output data ; will be interpolated for each fragment.
varying mediump vec2 texCoord;

// Values that stay constant for the whole mesh.
uniform mat4 Model;
uniform mat4 VP;
uniform vec2 uvTarget;

void main(){

    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  VP * Model * vec4(vertexPosition,1);

    texCoord = aTexCoord + uvTarget;
}