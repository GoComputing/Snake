#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <GL/glew.h>
#include <vector>
#include <string>

class Shader {
private:
    static const char *WINDOW_SIZE_NAME;
    static std::vector<Shader*> instances;
    static GLuint current_program;
    
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint program;
    
protected:
    GLuint loadShader(const std::string &path, GLenum type);
    
    std::string shaderLog(GLuint shader) const;
    std::string programLog(GLuint program) const;
    
    void useProgram(GLuint program) const;
    
public:
    Shader();
    void create(const std::string &vertex_shader_path, const std::string &fragment_shader_path);
    
    static void setWindowRatio(GLfloat ratio);
    
    void setUniformVector(const std::string &name, GLenum component_type, GLuint num_components, ...);
    void use() const;
    void unuse() const;
    
    ~Shader();
};

#endif
