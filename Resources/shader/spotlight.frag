

#version 100
// Interpolated values from the vertex shaders
uniform mediump vec4 LightColor;


void main(){
    gl_FragColor = LightColor;
}