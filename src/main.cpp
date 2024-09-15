#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
unsigned int complie_shader_code(const char* shader_code, unsigned int shader_type);

int main()
{
    // we first initialize GLFW
    glfwInit();
    // configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // GLAD manages function pointers for OpenGL 
    // so we want to initialize GLAD before we call any OpenGL function
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    // telling OpenGL Window size for rendering
    // first 2 parms set the location of lower left corner in window
    // next 2 parms sets window width and height
    glViewport(0, 0, 800, 600);

    // resize the viewport of OpenGL when window resizes
    // by setting a callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // vertices for creating a triangle
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
    };

    // vertex shader code to display triangle with given vertex data points
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    // fragment shader code to color the triangle with given color
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
        "}\n";

    /*
        VBO -> Vertex Buffer Objects
        this is used to allocate memory to store the vertex data in GPU
        by allocating memory large enough to store all the vertex data
        in GPU, we can send all the vertex data at once to GPU
        rather than sending vertex data one by one
    */
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    /*
        VAO -> Vertex Array Object
        like VBO it holdes all the attributes required for vertex
        > glEnableVertexAttribArray / glDisableVertexAttribArray
        > glVertexAttribPointer
        > VBO associated with vertex attributes called by glVertexAttribPointer
    */
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    
    // once we bind the VAO any subsequent vertex attribute calls will be stored in VAO
    // by doing so all the vertex configurating will be saved in VAO
    // we can use this VAO to draw the object
    // which makes it easy to switch VAO to draw diffrent object
    glBindVertexArray(VAO);

    // binding VBO (int variable) to Array Buffer in GPU
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // create buffer size in GPU and send the vertex data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int vertexShader = complie_shader_code(vertexShaderSource, GL_VERTEX_SHADER);
    unsigned int fragmentShader = complie_shader_code(fragmentShaderSource, GL_FRAGMENT_SHADER);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    /*
        1st parm > vertex attribute we want to configure, 
            in vertex shader we have spicified layout location = 0
            we set vertex attribute to 0
        2nd parm > size of vertex attribute we are using vec3 so 3 elements
        3rd parm > is data type in this case GL_FLOAT (float),
            all vec* in GLSL in float
        4th parm > should the vertex data be normilised (0 -> 1)
            if the data type is int, byte we have to normilize it using GL_TRUE
            in this case as the vertex data is between 0 -> 1 we pass GL_FALSE
        5th parm > stride which tells us space between consecutive vertex attributes
            here we are passing 3 floats for each vertex attributes, so 3 * float
        6th parm > offset of the begining of vertex data here it is at start so 0
    */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // enable vertex array attribute so OpenGL can display the vertices
    glEnableVertexAttribArray(0);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram);


    // setting loop so the window will not immediately close
    while (!glfwWindowShouldClose(window))
    {
        // input handeling
        processInput(window);
        
        // rendering commands
        
        // set background color value
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // clear previously rendered image using background color
        glClear(GL_COLOR_BUFFER_BIT);

        // to draw the primitives using current active shader
        // and defined VBO and VAO we use glDrawArrays
        // here we are drawing triangle a promitive
        // 2nd attribute start of vertex array just leave it to 0
        // last is number of vertices we want to draw here we want to draw 3
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // check and call events and swap buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // deleting all the glfw allocated resources
    glfwTerminate();

    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
