#include <shader.hpp>
#include <tools.hpp>
#include <stdexcept>
#include <cassert>

GLuint Shader::current_program = 0;

GLuint Shader::loadShader(const std::string &path, GLenum type) {
    std::string source_code = loadBinaryFile(path);
    const char *str_source_code = source_code.c_str();
    GLint source_code_size = source_code.size();
    GLuint shader;
    GLint status;
    if(source_code.size() == 0)
        throw std::runtime_error("Trying to load a empty shader (" + path + ")");
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &str_source_code, &source_code_size);
    glCompileShader(shader);
    // Test
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE)
        throw std::runtime_error("Error compiling shader at '" + path + "'\n" + shaderLog(shader));
    return shader;
}

std::string Shader::shaderLog(GLuint shader) const {
    std::string res;
    GLint log_size;
    GLchar *log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
    log = new GLchar[log_size];
    assert(log);
    glGetShaderInfoLog(shader, log_size, NULL, log);
    res = std::move(std::string(log));
    delete[] log;
    return res;
}

std::string Shader::programLog(GLuint program) const {
    std::string res;
    GLint log_size;
    GLchar *log;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_size);
    log = new GLchar[log_size];
    assert(log);
    glGetProgramInfoLog(program, log_size, NULL, log);
    res = std::move(std::string(log));
    delete[] log;
    return res;
}

Shader::Shader() {
    vertex_shader = 0;
    fragment_shader = 0;
    program = 0;
}

void Shader::create(const std::string &vertex_shader_path, const std::string &fragment_shader_path) {
    GLint status;
    vertex_shader = loadShader(vertex_shader_path, GL_VERTEX_SHADER);
    fragment_shader = loadShader(fragment_shader_path, GL_FRAGMENT_SHADER);
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    // Test
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if(status != GL_TRUE)
        throw std::runtime_error("Error linking program with shaders " + vertex_shader_path +
                                 ", " + fragment_shader_path + "\n" + programLog(program));
}

void Shader::use() const {
    if(current_program != program) {
        current_program = program;
        glUseProgram(program);
    }
}

void Shader::unuse() const {
    if(current_program != 0) {
        current_program = 0;
        glUseProgram(0);
    }
}

Shader::~Shader() {
    glDeleteProgram(program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}
