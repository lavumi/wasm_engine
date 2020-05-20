#include "precompiled.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"


Texture::Texture(){

}

Texture::~Texture(){

}

void Texture::LoadTexture(std::string path ){


    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture); //GL_TEXTURE2D에 바인드


    //현재 바인딩된 객체에만 설정
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    int width, height, nrChannels;
    unsigned char *data = stbi_load((SDL_GetBasePath() + path).c_str(), &width, &height, &nrChannels, 4); 


    if ( data ){
        glTexImage2D(
            GL_TEXTURE_2D, //위에 GL_TEXTURE_2D에 바인딩된 곳을 타겟
            0, //mipmap 레벨
            GL_RGB, //텍스쳐 포멧
            width, //넓이, 높이
            height, 
            0, //무조건 0 ?
            GL_RGBA,     //원본 이미지 포멧
            GL_UNSIGNED_BYTE, //원본 이미지 데이터 타입
            data    //실제 데이터
            );
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Image Load Fail " << path << std::endl;
        if( stbi_failure_reason() )
            std::cout << stbi_failure_reason() << std::endl;
    }
    stbi_image_free(data);

}

void Texture::BindTexture(){
    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, _texture);
}