//
// Created by apple on 2022/9/15.
//

#include "vertex_control.h"
#include "glad/glad.h"

void vertex_control::createVertex(int vertexNum, int *dataPerVertex, const float *data, int dataSize)
{
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

    //创建VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    int lineSize = 0, pos = 0;
    for (int i = 0; i < vertexNum; ++i)
    {
        lineSize += dataPerVertex[i];
    }
    for (int i = 0; i < vertexNum; ++i)
    {
        glVertexAttribPointer(i, dataPerVertex[i], GL_FLOAT, GL_FALSE, lineSize * sizeof (float), (void *)(pos * sizeof (float)));//这里会把VBO绑定到VAO上
        glEnableVertexAttribArray(i);
        pos += dataPerVertex[i];
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);//解绑vbo
    vao = VAO;
}

void vertex_control::addEbo(unsigned int *data, int size)
{
    glBindVertexArray(vao);//绑定vao
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//这里会把EBO绑定到VAO上
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

vertex_control::vertex_control()
{

}
