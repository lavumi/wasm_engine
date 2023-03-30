#version 100
// Interpolated values from the vertex shaders
varying mediump vec2 texCoord;
uniform sampler2D myTexture;

void main(){
    mediump vec4 sampled = texture2D(myTexture, texCoord);
    gl_FragColor =  sampled;//vec4(sampled.a, 0,0,1);
}