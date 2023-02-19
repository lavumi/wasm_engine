#pragma once

class Texture{

private:
    GLuint _texture; 
    public :
    Texture();
    ~Texture();

    void LoadTexture(std::string path);
    void BindTexture();
};