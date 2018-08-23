#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include <GL/glew.h>
#include <string>

class Texture {
private:
    static GLuint current_texture;
    GLuint texture;
    
protected:
    void bind(GLuint texture) const;
    void setDefaultState();
    
public:
    Texture();
    Texture(const Texture &texture) = delete;
    void load(const std::string &path);
    
    Texture& operator=(const Texture &texture) = delete;
    void use() const;
    void unuse() const;
    
    ~Texture();
};

struct Bmp {
    uint32_t pos_data;
    uint32_t width;
    uint32_t height;
    uint16_t bits_per_pixel;
    std::string data;
    
    void transformARGB_RGBA();
    void extractData(const std::string &path);
    void getFormat(GLint &internal_format, GLint &format);
    const char* dataPtr();
};

#endif
