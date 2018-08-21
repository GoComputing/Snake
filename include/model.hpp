#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include <GL/glew.h>
#include <shader.hpp>

class Model {
private:
    static GLuint current_vao;
    static GLuint current_vbo;
    GLuint vertex_array_object;
    GLuint vertex_buffer_object;
    GLuint num_vertices;
    
protected:
    void bindVertexBuffer(GLuint vbo) const;
    void bindVertexArray(GLuint vao) const;
    GLuint generateVertexBuffer(const GLfloat *vertices, GLuint num_vertices, GLuint components_per_vertex);
    GLuint generateVertexArray(GLuint vbo, GLuint components_per_vertex);
    void generate(const GLfloat *vertices, GLuint num_vertices, GLuint components_per_vertex);
    
public:
    Model();
    Model(const Model &model) = delete;
    
    Model& operator=(const Model &model) = delete;
    void render(const Shader &shader) const;
    
    ~Model();
    
    friend void loadSquare(GLfloat x, GLfloat y, GLfloat size, Model &result);
};

#endif
