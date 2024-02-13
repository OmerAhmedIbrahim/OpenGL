#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H
#include <utility>

namespace sdds {

class TriangleMesh {
    struct M {
        struct Triangle{
            float positionA[3] = {0.0, 0.0, 0.0};
            float colourA[3] = {0.0, 0.0, 0.0};
            float positionB[3] = {0.0, 0.0, 0.0};
            float colourB[3] = {0.0, 0.0, 0.0};
            float positionC[3] = {0.0, 0.0, 0.0};
            float colourC[3] = {0.0, 0.0, 0.0};
        } tri;
        unsigned int VBO = 0;
        unsigned int VAO = 0;
    } m;
    TriangleMesh::TriangleMesh();
    TriangleMesh::TriangleMesh(const TriangleMesh& t);
    TriangleMesh::TriangleMesh(TriangleMesh&& t) noexcept;
    explicit TriangleMesh::TriangleMesh(M m) : m(std::move(m)){}
public:
    static TriangleMesh create(float* triangle);
};

} // sdds

#endif //TRIANGLEMESH_H
