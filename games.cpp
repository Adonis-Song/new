#include <iostream>

extern "C" {
#include <glad/glad.h>
#include <GLFW/glfw3.h>
}

#define WINDOW_W 800
#define WINDOW_H 600

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

    while (!glfwWindowShouldClose(windows))
    {
        glfwSwapBuffers(windows);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
