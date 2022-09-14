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


    //开始搞三角形
    //创建VBO
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,
            0.0f, -1.f, 0.0f
    };
    unsigned int VBO;
    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

    //创建VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //创建EBO
    unsigned int indices[] = {
            0, 1, 2,
            0, 1, 3
    };
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//这里会把EBO绑定到VAO上
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (indices), indices, GL_STATIC_DRAW);

    //设置顶点数据的类型
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float), nullptr);//这里会把VBO绑定到VAO上
    glEnableVertexAttribArray(0);

    //设置顶点着色器
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//设置源码
    glCompileShader(vertexShader);

    //设置片段着色器
    const char* fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "\n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\0";
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //创建着色器程序
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


    //使用着色器程序
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//将EBO重新绑定到VAO中

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    while (!glfwWindowShouldClose(windows))
    {
        glfwSwapBuffers(windows);
        glClearColor(0.2f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VAO);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);//解绑VAO 就算解绑EBO，实际的绑定信息也存在VAO里面了
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);//就算解绑VBO

        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
