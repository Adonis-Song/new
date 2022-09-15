//
// Created by apple on 2022/9/15.
//

#ifndef OPENGL_VERTEX_CONTROL_H
#define OPENGL_VERTEX_CONTROL_H
//#include "vbo.h"
//#include "ebo.h"
//#include "vao.h"
class vertex_control
{
private:
//    vbo vbo;
//    vao vao;
//    ebo ebo;
    unsigned int vao;
public:
    vertex_control();
    void createVertex(int vertexNum, int* dataPerVertex, const float* data, int dataSize);
    void addEbo(unsigned int* data, int size);
};


#endif //OPENGL_VERTEX_CONTROL_H
