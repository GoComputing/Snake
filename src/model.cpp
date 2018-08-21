#include <model.hpp>
#include <cassert>

/*
class Model {
private:
    GLuint vertex_array_object;
    GLuint vertex_buffer_object;
    
protected:
    void bindVertexBuffer(GLuint vbo);
    void bindVertexArray(GLuint vao);
    GLuint generateVertexBuffer(GLfloat *vertices);
    GLuint generateVertexArray(GLuint vbo, GLuint components_per_vertex);
    void generate(const GLfloat *vertices, GLuint components_per_vertex);
    
public:
    Model();
    Model(const Model &model) = delete;
    
    Model& operator=(const Model &model) = delete;
    void render() const;
    
    ~Model();
    
    friend void loadSquare(GLfloat x, GLfloat y, GLfloat size, Model &result);
};
*/

GLuint Model::current_vao = 0;
GLuint Model::current_vbo = 0;

void Model::bindVertexBuffer(GLuint vbo) const {
    if(current_vbo != vbo) {
        current_vbo = vbo;
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
    }
}

void Model::bindVertexArray(GLuint vao) const {
    if(current_vao != vao) {
        current_vao = vao;
        glBindVertexArray(vao);
    }
}

GLuint Model::generateVertexBuffer(const GLfloat *vertices, GLuint num_vertices, GLuint components_per_vertex) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    assert(vbo != 0);
    bindVertexBuffer(vbo);
    glBufferData(GL_ARRAY_BUFFER, num_vertices*components_per_vertex*sizeof(GLfloat), (void*)vertices, GL_STATIC_DRAW);
    return vbo;
}

GLuint Model::generateVertexArray(GLuint vbo, GLuint components_per_vertex) {
    assert(components_per_vertex >= 1 && components_per_vertex <= 4);
    GLuint vao;
    glGenVertexArrays(1, &vao);
    assert(vao != 0);
    bindVertexArray(vao);
    bindVertexBuffer(vbo);
    glVertexAttribPointer(0, components_per_vertex, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    return vao;
}

void Model::generate(const GLfloat *vertices, GLuint num_vertices, GLuint components_per_vertex) {
    vertex_buffer_object = generateVertexBuffer(vertices, num_vertices, components_per_vertex);
    vertex_array_object = generateVertexArray(vertex_buffer_object, components_per_vertex);
    this->num_vertices = num_vertices;
}
    
Model::Model() {
    vertex_buffer_object = 0;
    vertex_array_object = 0;
}
    
void Model::render(const Shader &shader) const {
    shader.use();
    bindVertexArray(vertex_array_object);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, num_vertices);
    glDisableVertexAttribArray(0);
}

Model::~Model() {
    bindVertexArray(0);
    bindVertexBuffer(0);
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteBuffers(1, &vertex_buffer_object);
}
    
void loadSquare(GLfloat x, GLfloat y, GLfloat size, Model &result) {
    GLuint components_per_vertex = 2;
    GLfloat vertices[] = {
        x, y,
        size+x, y,
        x, size+y,
        size+x, y,
        x, size+y,
        size+x, size+y
    };
    GLuint num_vertices = sizeof(vertices) / (components_per_vertex*sizeof(GLfloat));
    result.generate(vertices, num_vertices, components_per_vertex);
}
