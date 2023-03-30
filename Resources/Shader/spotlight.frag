#version 100
uniform mediump vec4 LightColor;
varying mediump float zclip;


void main(){
    if ( zclip < -2.0 ){
        discard;
    }
//    LightColor.a = zclip >= 0.0 ? LightColor.a : 0.0;
    gl_FragColor = LightColor;
}