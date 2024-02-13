#ifndef OPENGL_SQUARE_H
#define OPENGL_SQUARE_H
#include "Window.h"

namespace sdds {

class Rectangle {
    float top = 0.5f, right = 0.5f;
    float bottom = -0.5f, left = -0.5f;
    float red = 1.0f, green = 1.0f, blue = 1.0f;
    float vertices[24]= {
            right,  top, 0.0f, red, green, blue, // top right
            right, bottom, 0.0f, red, green, blue, // bottom right
            left, bottom, 0.0f, red, green, blue, // bottom left
            left,  top, 0.0f, red, green, blue // top left
    };
    unsigned int indices[6] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };
//Vertex Objects
    GLuint VBO = 0.0f ;
    GLuint VAO = 0.0f ;
    GLuint EBO = 0.0f ;
//Number of Vertexs
    const GLuint NumVertices = 6;
    void setTopRight(const float &x, const float &y);
    void setBottomRight(const float &x, const float &y);
    void setBottomLeft(const float &x, const float &y);
    void setTopLeft(const float &x, const float &y);
public:
    Rectangle();
    Rectangle(const Rectangle &r);
    Rectangle(const sdds::Window &w,  const unsigned int width, const unsigned int height);
    Rectangle(const sdds::Window &w,  const unsigned int width, const unsigned int height, const char colour);
    ~Rectangle();
    Rectangle& operator=(const Rectangle &r);
    void mesh();
    void draw() const;
    void translate(const glm::vec3 &v);
    void rotate(const float &a);
    void scale(const glm::vec3 &v);
    glm::vec2 getcenter() const;
    GLuint getVAO() const;
    GLuint getVBO() const;
    GLuint getEBO() const;
};

} // sdds

#endif //OPENGL_SQUARE_H
