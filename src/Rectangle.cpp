#include "Rectangle.h"

namespace sdds {
    Rectangle::Rectangle() = default;
    Rectangle::~Rectangle() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
    Rectangle::Rectangle(const sdds::Window &w, const unsigned int width, const unsigned int height) {
        right = float(width)/float(w.getWidth()), top = float(height)/float(w.getHeight());
        vertices[0] = vertices[6] = right;
        vertices[12] = vertices[18] = -right;
        vertices[1] = vertices[19] = top;
        vertices[7] = vertices[13] = -top;
    }
    Rectangle::Rectangle(const sdds::Window &w, const unsigned int width, const unsigned int height, const char colour) {
        right = float(width)/float(w.getWidth()), top = float(height)/float(w.getHeight());
        vertices[0] = vertices[6] = right;
        left = vertices[12] = vertices[18] = -right;
        vertices[1] = vertices[19] = top;
        bottom = vertices[7] = vertices[13] = -top;
        switch (colour) {
            case 'R': red = 1.0f; green = 0.0f; blue = 0.0f; break;
            case 'G': red = 0.0f; green = 1.0f; blue = 0.0f; break;
            case 'B': red = 0.0f; green = 0.0f; blue = 1.0f; break;
            case 'Y': red = 1.0f; green = 1.0f; blue = 0.0f; break;
            case 'C': red = 0.0f; green = 1.0f; blue = 1.0f; break;
            case 'M': red = 1.0f; green = 0.0f; blue = 1.0f; break;
            case 'D': red = 0.0f; green = 0.0f; blue = 0.0f; break;
            default:break;
        }
        vertices[3] = vertices[9] = vertices[15] = vertices[21] = red;
        vertices[4] = vertices[10] = vertices[16] = vertices[22] =  green;
        vertices[5] = vertices[11] = vertices[17] = vertices[23] =  blue;
    }
    void Rectangle::mesh() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    void Rectangle::draw() const{
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, NumVertices, GL_UNSIGNED_INT, 0);
    }

    void Rectangle::translate(const glm::vec3 &v) {
        setTopRight( vertices[0] + v.x,  vertices[1] + v.y);
        setBottomRight(vertices[6]  + v.x,  vertices[7] + v.y);
        setBottomLeft(vertices[12]  + v.x,  vertices[13] + v.y);
        setTopLeft(vertices[18]  + v.x,  vertices[19] + v.y);

        mesh();
    }
    void Rectangle::rotate(const float &a) {
        /*translate(glm::vec3(0.5f, -0.5f, 0.0f));
        const double pi = std::acos(-1.0);
        glm::vec2 center = {vertices[6] - vertices[12], vertices[1] - vertices[7]};
        glm::vec2 midRight = {vertices[12], vertices[1] - vertices[7]};
        glm::vec2 from = {center.x - midRight.x, center.y - midRight.y};
        float norm = 1/std::sqrt(from.x * from.x + from.y * from.y);
        from.x = from.x * norm;
        from.y = from.y * norm;
        float cos = std::cos(pi/4), sin = std::sin(pi/4);
        glm::vec2 half = {cos * from.x, sin * from.y};
        norm = 1/std::sqrt(half.x * half.x + half.y * half.y);
        half.x = half.x * norm;
        half.y = half.y * norm;
        //float ix = cos * 1, jx = sin * 1;
        //float iy = -sin * 1, jy = cos * 1;
        sdds::Rotor r = { from.x * half.x + half.y * from.y ,
                          (half.x * from.y)-(half.y * from.x) ,
                          0,
                          0};

        float sx_rt = r.scalar*vertices[0] + r.xy * vertices[1] , sy_rt =r.scalar*vertices[1] - r.xy * vertices[0];
        float rtx = r.scalar*(sx_rt) + r.xy * (sy_rt),
              rty = r.scalar*(sy_rt) - r.xy * (sx_rt);
        setTopRight( rtx, rty);

        float sx_rb = r.scalar*vertices[6] + r.xy * vertices[7] , sy_rb =r.scalar*vertices[6] - r.xy * vertices[7];
        float rbx = r.scalar*(sx_rb) + r.xy * (sy_rb),
              rby = r.scalar*(sy_rb) - r.xy * (sx_rb);
        setBottomRight( rbx , rby );

        float sx_lb = r.scalar*vertices[12] + r.xy * vertices[13] , sy_lb =r.scalar*vertices[12] - r.xy * vertices[13];
        float lbx = r.scalar*(sx_lb) + r.xy * (sy_lb),
              lby = r.scalar*(sy_lb) - r.xy * (sx_lb);
        setBottomLeft( lbx   , lby  );

        float sx_lt = r.scalar*vertices[18] + r.xy * vertices[19], sy_lt =r.scalar*vertices[18] - r.xy * vertices[19];
        float ltx = r.scalar*(sx_lt) + r.xy * (sy_lt),
              lty = r.scalar*(sy_lt) - r.xy * (sx_lt);
        setTopLeft( ltx , lty );*/

        mesh();
    }
    void Rectangle::scale(const glm::vec3 &v) {
        setTopRight( vertices[0] * v.x,  vertices[1] * v.y);
        setBottomRight(vertices[6]  * v.x,  vertices[7] * v.y);
        setBottomLeft(vertices[12]  * v.x,  vertices[13] * v.y);
        setTopLeft(vertices[18]  * v.x,  vertices[19] * v.y);
        mesh();
    }

    Rectangle::Rectangle(const Rectangle &r)
    :top(r.top), right(r.right), left(r.left), bottom(r.bottom),
    red(r.red), green(r.green), blue(r.blue)
    {
        vertices[0] = vertices[6] = right;
        vertices[12] = vertices[18] = left;
        vertices[1] = vertices[19] = top;
        vertices[7] = vertices[13] = bottom;
        vertices[3] = vertices[9] = vertices[15] = vertices[21] = red;
        vertices[4] = vertices[10] = vertices[16] = vertices[22] =  green;
        vertices[5] = vertices[11] = vertices[17] = vertices[23] =  blue;
    }

    Rectangle& Rectangle::operator=(const Rectangle &r) {
        if(this != &r){
            top = (r.top), right = (r.right),
            left = (r.left), bottom = (r.bottom),
            red = (r.red), green = (r.green), blue = (r.blue);
            vertices[0] = vertices[6] = right;
            vertices[12] = vertices[18] = left;
            vertices[1] = vertices[19] = top;
            vertices[7] = vertices[13] = bottom;
            vertices[3] = vertices[9] = vertices[15] = vertices[21] = red;
            vertices[4] = vertices[10] = vertices[16] = vertices[22] =  green;
            vertices[5] = vertices[11] = vertices[17] = vertices[23] =  blue;
            mesh();
        }
        return *this;
    }

    void Rectangle::setTopRight(const float &x, const float &y) {
        vertices[0] = x; vertices[1] = y;
    }
    void Rectangle::setBottomRight(const float &x, const float &y) {
        vertices[6] = x; vertices[7] = y;
    }
    void Rectangle::setBottomLeft(const float &x, const float &y) {
        vertices[12] = x; vertices[13] = y;
    }
    void Rectangle::setTopLeft(const float &x, const float &y) {
        vertices[18] = x; vertices[19] = y;
    }
    glm::vec2 Rectangle::getcenter() const {
        return {vertices[6] - vertices[12], vertices[1] - vertices[7]};
    }
    GLuint Rectangle::getVAO() const{
        return VAO;
    }
    GLuint Rectangle::getVBO() const{
        return VBO;
    }
    GLuint Rectangle::getEBO() const{
        return EBO;
    }
} // sdds