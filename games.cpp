#include <iostream>

extern "C" {
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
}
#include "gl/shader.h"
#include "gl/vertex_control.h"
#include "util/util.h"

#define WINDOW_W 800
#define WINDOW_H 600
#define RENDER_FPS 30;

int stop;
void processInput(GLFWwindow *window, double* last_pass_time)
{
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        stop = stop ? 0 : 1;
        std::cout << "pass " <<  std::endl;
        *last_pass_time = glfwGetTime();
    }
}

int main() {
    //初始化一个窗口
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    //创建一个窗口对象
    GLFWwindow* windows = glfwCreateWindow(WINDOW_W, WINDOW_H, "Games", NULL, NULL);
    if (windows == NULL)
    {
        printf("创建窗口失败 \n");
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(windows);

    //初始化glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("初始化glad失败 \n");
        glfwTerminate();
        exit(-1);
    }

    //设置视口大小
    glViewport(0, 0, WINDOW_W, WINDOW_H);

    //创建VBO
    float vertices[] = {
            0.5f, 0.5f, 0.0f,  0.1f, 0.2f, 0.3f,    1.0f, 1.0f,   // 右上
            0.5f, -0.5f, 0.0f,   0.1f, 0.3f, 0.5f,    1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,    0.1f, 0.6f, 0.8f,    0.0f, 0.0f,   // 左下
            -0.5f, 0.5f, 0.0f,    0.1f, 0.3f, 0.3f,    0.0f, 1.0f    // 左上
    };
    unsigned int indices[] = {
            1, 2, 0,
            0, 2, 3
    };
    int vboDataIndex[] = {3, 3, 2};
    vertex_control vctl;
    vctl.createVertex(sizeof (vboDataIndex) / sizeof (int),
                      vboDataIndex,
                      vertices,
                      sizeof (vertices));
    vctl.addEbo(indices, sizeof (indices));

    shader triangleShader("./triangle.vs", "./triangle.fs");
    triangleShader.use();

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    //设置各种环绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;

    unsigned char *data = util::extractImageFromFile("container2.jpg", &width, &height, &nrChannels);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    util::freeImage(data);

    glClearColor(0.2f, 0.3f, 0.3f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    int time = 0;
    double current_time = glfwGetTime();
    double last_time = current_time;
    double last_pass_time = current_time;
    double interval_time = 1. / RENDER_FPS;
    while (!glfwWindowShouldClose(windows))
    {
        current_time = glfwGetTime();
        if (current_time - last_time < interval_time)
        {
            int sleeptime = (interval_time - current_time + last_time) * 1000000;
            usleep(sleeptime);
        }
        if (current_time - last_pass_time > 0.2)
            processInput(windows, &last_pass_time);

        if (!stop) {
            glClearColor(0.2f, 0.3f, 0.3f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
//            triangleShader.setUniform1f("time", (float)(time ++ % 11));
            glfwSwapBuffers(windows);
        }
        glfwPollEvents();
        last_time = glfwGetTime();
    }

    glfwTerminate();

    return 0;
}
