#include <model.hpp>
#include <cassert>

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
    glBufferData(GL_ARRAY_BUFFER,
                 num_vertices*components_per_vertex*sizeof(GLfloat),
                 (void*)vertices,
                 GL_STATIC_DRAW);
    return vbo;
}

GLuint Model::generateVertexArray(GLuint vbo, GLuint tcbo, const ModelData &model_data) {
    assert(model_data.components_per_vertex >= 1 && model_data.components_per_vertex <= 4);
    GLuint vao;
    glGenVertexArrays(1, &vao);
    assert(vao != 0);
    bindVertexArray(vao);
    bindVertexBuffer(vbo);
    glVertexAttribPointer(0, model_data.components_per_vertex, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    if(tcbo != 0) {
        bindVertexBuffer(tcbo);
        glVertexAttribPointer(1, NUM_COMPONENTS_TEXCOORDS, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    }
    return vao;
}

void Model::generate(const ModelData &model_data) {
    vertex_buffer_object = generateVertexBuffer(model_data.vertices, model_data.num_vertices, model_data.components_per_vertex);
    if(model_data.texture_path.size() > 0) {
        texture.load(model_data.texture_path);
        texcoords_buffer_object = generateVertexBuffer(model_data.texcoords, model_data.num_vertices, NUM_COMPONENTS_TEXCOORDS);
    }
    vertex_array_object = generateVertexArray(vertex_buffer_object, texcoords_buffer_object, model_data);
    this->num_vertices = model_data.num_vertices;
}
    
Model::Model() {
    vertex_buffer_object = 0;
    vertex_array_object = 0;
    texcoords_buffer_object = 0;
}
    
void Model::render(Shader &shader) const {
    shader.use();
    bindVertexArray(vertex_array_object);
    glEnableVertexAttribArray(0);
    if(texcoords_buffer_object != 0) {
        glEnableVertexAttribArray(1);
        shader.setUniformVector("use_texture", GL_INT, 1, 1);
        texture.use();
    } else {
        shader.setUniformVector("use_texture", GL_INT, 1, 0);
    }
    glDrawArrays(GL_TRIANGLES, 0, num_vertices);
    glDisableVertexAttribArray(0);
    if(texcoords_buffer_object != 0)
        glDisableVertexAttribArray(1);
}

Model::~Model() {
    bindVertexArray(0);
    bindVertexBuffer(0);
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteBuffers(1, &vertex_buffer_object);
    glDeleteBuffers(1, &texcoords_buffer_object);
}
    
void loadSquare(GLfloat x, GLfloat y, GLfloat size, const std::string &texture_path, Model &result) {
    GLuint components_per_vertex = 2;
    GLfloat vertices[] = {
        x, y,
        size+x, y,
        x, size+y,
        size+x, y,
        x, size+y,
        size+x, size+y
    };
    GLfloat texcoords[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f
    };
    GLuint num_vertices = sizeof(vertices) / (components_per_vertex*sizeof(GLfloat));
    ModelData model_data;
    model_data.vertices = vertices;
    model_data.num_vertices = num_vertices;
    model_data.components_per_vertex = components_per_vertex;
    model_data.texcoords = texcoords;
    model_data.texture_path = texture_path;
    result.generate(model_data);
}
