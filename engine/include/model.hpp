#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include <GL/glew.h>
#include <shader.hpp>
#include <texture.hpp>

struct ModelData {
    const GLfloat *vertices;
    GLuint num_vertices;
    GLuint components_per_vertex;
    
    const GLfloat *texcoords;
    std::string texture_path;
};

class Model {
private:
    static constexpr int NUM_COMPONENTS_TEXCOORDS = 2;
    
    static GLuint current_vao;
    static GLuint current_vbo;
    GLuint vertex_array_object;
    GLuint vertex_buffer_object;
    GLuint texcoords_buffer_object;
    GLuint num_vertices;
    Texture texture;
    
protected:
    void bindVertexBuffer(GLuint vbo) const;
    void bindVertexArray(GLuint vao) const;
    GLuint generateVertexBuffer(const GLfloat *vertices, GLuint num_vertices, GLuint components_per_vertex);
    GLuint generateVertexArray(GLuint vbo, GLuint tcbo, const ModelData &model_data);
    void generate(const ModelData &model_data);
    
public:
    Model();
    Model(const Model &model) = delete;
    
    Model& operator=(const Model &model) = delete;
    void render(Shader &shader) const;
    
    ~Model();
    
    /**
     * @brief Loads a square, which could be textured
     * @param x: x bottom left corner of the square
     * @param y: y bottom left corner of the square
     * @param size: size of the square. 2.0 is equal to screen width
     * @param texture_path: Path to a BMP image. If path is empty, texture will not be loaded
     * @return result: Model which represents the (textured) square model
     */
    friend void loadSquare(GLfloat x, GLfloat y, GLfloat size, const std::string &texture_path, Model &result);
};

#endif
