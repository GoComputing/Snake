#include <texture.hpp>
#include <tools.hpp>
#include <cstdint>

// BM
#define BMP_CHECK           0x4D42
#define MINIMUN_HEADER_SIZE 54

GLuint Texture::current_texture = 0;

#include <iostream>
#include <iomanip>

void Bmp::extractData(const std::string &path) {
    uint32_t data_size;
    uint16_t check;
    data = loadBinaryFile(path);
    if(data.size() < MINIMUN_HEADER_SIZE)
        throw std::runtime_error ("Not valid BMP size at " + path);
    check          = *reinterpret_cast<const uint16_t *>(data.c_str() + 0);
    pos_data       = *reinterpret_cast<const uint32_t *>(data.c_str() + 10);
    width          = *reinterpret_cast<const uint32_t *>(data.c_str() + 18);
    height         = *reinterpret_cast<const uint32_t *>(data.c_str() + 22);
    bits_per_pixel = *reinterpret_cast<const uint16_t *>(data.c_str() + 28);
    data_size = width*height*bits_per_pixel / 8;
    if(check != BMP_CHECK)
        throw std::runtime_error ("Not valid BMP signature at " + path);
    if(data.size() < data_size+pos_data)
        throw std::runtime_error ("Not enought data in BMP at " + path);
    if(bits_per_pixel != 24 && bits_per_pixel != 32)
        throw std::runtime_error ("Not valid pixel size in BMP at " + path);
}

const char* Bmp::dataPtr() {
    return data.c_str() + pos_data;
}

void Bmp::getFormat(GLint &internal_format, GLint &format) {
    if(bits_per_pixel == 24) {
        internal_format = GL_RGB;
        format = GL_BGR;
    } else {
        internal_format = GL_RGBA;
        format = GL_BGRA;
    }
}

void Texture::bind(GLuint texture) const {
    if(current_texture != texture) {
        current_texture = texture;
        glBindTexture(GL_TEXTURE_2D, texture);
    }
}

void Texture::setDefaultState() {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

Texture::Texture() {
    texture = 0;
}

void Texture::load(const std::string &path) {
    Bmp image;
    GLint internal_format;
    GLint format;
    image.extractData(path);
    glGenTextures(1, &texture);
    use();
    image.getFormat(internal_format, format);
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, image.width, image.height, 0, format, GL_UNSIGNED_BYTE, image.dataPtr());
    setDefaultState();
}

void Texture::use() const {
    bind(texture);
}

void Texture::unuse() const {
    bind(0);
}
    
Texture::~Texture() {
    glDeleteTextures(1, &texture);
}
