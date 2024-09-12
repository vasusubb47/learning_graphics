#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

int main(void)
{
    // 
    if (!glfwInit())
        return -1;

    GLFWwindow* window = window = glfwCreateWindow(640, 480, "learning graphics", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window))
	{
		int width = 0, height = 0;

		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		//I'm using the old pipeline here just to test, you shouldn't learn this,
		//Also It might not work on apple
		glBegin(GL_TRIANGLES);
		glVertex2f(0, 1);
		glVertex2f(1, -1);
		glVertex2f(-1, -1);
		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

    return 0;
}