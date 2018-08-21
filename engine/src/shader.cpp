#include <shader.hpp>
#include <tools.hpp>
#include <algorithm>
#include <stdexcept>
#include <cassert>
#include <cstdarg>

const char *Shader::WINDOW_SIZE_NAME = "window_ratio";
std::vector<Shader*> Shader::instances;
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

void Shader::useProgram(GLuint program) const {
    if(program != current_program) {
        current_program = program;
        glUseProgram(program);
    }
}

Shader::Shader() {
    vertex_shader = 0;
    fragment_shader = 0;
    program = 0;
    instances.push_back(this);
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

void Shader::setWindowRatio(GLfloat ratio) {
    size_t i;
    for(i = 0; i < instances.size(); ++i)
        if(instances[i]->program != 0)
            instances[i]->setUniformVector(WINDOW_SIZE_NAME, GL_FLOAT, 1, ratio);
}

void Shader::setUniformVector(const std::string &name, GLenum component_type, GLuint num_components, ...) {
    assert(component_type == GL_INT || component_type == GL_UNSIGNED_INT || component_type == GL_FLOAT);
    assert(num_components >= 1 && num_components <= 4);
    GLuint current = current_program;
    GLint uniform_location;
    va_list components;
    use();
    uniform_location = glGetUniformLocation(program, name.c_str());
    if(uniform_location < 0)
        throw std::runtime_error ("Error finding uniform location with name '" + name + "'");
    va_start(components, num_components);
    if(component_type == GL_INT) {
        if(num_components == 1) {
            GLint v1 = va_arg(components, GLint);
            glUniform1i(uniform_location, v1);
        } else if(num_components == 2) {
            GLint v1 = va_arg(components, GLint);
            GLint v2 = va_arg(components, GLint);
            glUniform2i(uniform_location, v1, v2);
        } else if(num_components == 3) {
            GLint v1 = va_arg(components, GLint);
            GLint v2 = va_arg(components, GLint);
            GLint v3 = va_arg(components, GLint);
            glUniform3i(uniform_location, v1, v2, v3);
        } else {
            GLint v1 = va_arg(components, GLint);
            GLint v2 = va_arg(components, GLint);
            GLint v3 = va_arg(components, GLint);
            GLint v4 = va_arg(components, GLint);
            glUniform4i(uniform_location, v1, v2, v3, v4);
        }
    } else if(component_type == GL_UNSIGNED_INT) {
        if(num_components == 1) {
            GLuint v1 = va_arg(components, GLuint);
            glUniform1ui(uniform_location, v1);
        } else if(num_components == 2) {
            GLuint v1 = va_arg(components, GLuint);
            GLuint v2 = va_arg(components, GLuint);
            glUniform2ui(uniform_location, v1, v2);
        } else if(num_components == 3) {
            GLuint v1 = va_arg(components, GLuint);
            GLuint v2 = va_arg(components, GLuint);
            GLuint v3 = va_arg(components, GLuint);
            glUniform3ui(uniform_location, v1, v2, v3);
        } else {
            GLuint v1 = va_arg(components, GLuint);
            GLuint v2 = va_arg(components, GLuint);
            GLuint v3 = va_arg(components, GLuint);
            GLuint v4 = va_arg(components, GLuint);
            glUniform4ui(uniform_location, v1, v2, v3, v4);
        }
    } else {
        if(num_components == 1) {
            GLfloat v1 = va_arg(components, double);
            glUniform1f(uniform_location, v1);
        } else if(num_components == 2) {
            GLfloat v1 = va_arg(components, double);
            GLfloat v2 = va_arg(components, double);
            glUniform2f(uniform_location, v1, v2);
        } else if(num_components == 3) {
            GLfloat v1 = va_arg(components, double);
            GLfloat v2 = va_arg(components, double);
            GLfloat v3 = va_arg(components, double);
            glUniform3f(uniform_location, v1, v2, v3);
        } else {
            GLfloat v1 = va_arg(components, double);
            GLfloat v2 = va_arg(components, double);
            GLfloat v3 = va_arg(components, double);
            GLfloat v4 = va_arg(components, double);
            glUniform4f(uniform_location, v1, v2, v3, v4);
        }
    }
    va_end(components);
    useProgram(current);
}

void Shader::use() const {
    useProgram(program);
}

void Shader::unuse() const {
    useProgram(0);
}

Shader::~Shader() {
    std::vector<Shader*>::iterator it;
    glDeleteProgram(program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    it = std::find(instances.begin(), instances.end(), this);
    assert(it != instances.end());
    instances.erase(it);
}
