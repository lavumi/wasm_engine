#version 100

attribute vec3 vertexPosition;
uniform mat4 Model;
uniform mat4 VP;
varying mediump float zclip;

void main(){
    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  VP * Model * vec4(vertexPosition,1);
    zclip = gl_Position.y;
}
