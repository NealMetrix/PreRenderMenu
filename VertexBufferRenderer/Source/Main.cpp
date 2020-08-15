#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "shaderClass.h"
#include "Debug.h"
#include "verticies.h"
#include "UserActions.h"

/*Here I want to make a program that requires the user to create their own shape by putting values into the user input
I don't really know if I can have the user change values... Especially with only being familiar with static draw for
the time being. But one thing that I could do is write a sort of console menu that asks the user for different inputs and
then generates a shape based on those values that you entered. I could even have a color questions with a string to rgb value
converter. Where based on the string that's typed in it generates a different rgb value... I would probably just use switch
statements.

But how would I like the input values to work? I could write a function for asking the user for info that way I could test
to see if I could change how the object is drawn in the program. That would mean that I have to use arrays instead of vectors.
Let's just try and make the simpler version. The one that I can build with just an array at the beginning of the program.

Actually it's probably best to make it with vectors anyways... Because this way I can have a buffer that I can push objects
into. But 1st I need to have 2 vectors that can have a vec4 class.*/

int main()
{
    /*If I want x to be called before y I will need to be more explicit than I am here. It automatically does
    the coordinate input in the y value before it does x. I could store them in variables before they are called that*/
    verticyBuffer shapeDrawer;
    std::string userinput = "";
    while (userinput != "generate" && userinput != "quit")
    {
        std::cout << "What action would you like to perform on your shapes" << std::endl;
        std::cout << "Enter help for possible actions" << std::endl << std::endl;
        std::cin >> userinput;
        action(userinput, shapeDrawer);
    }
    if (userinput == "quit")
        return 0;

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1080, 720, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    int initGlewValue = glewInit();

    shader testShader("Shaders/testShader.shader");
    int uniLocation = testShader.uniformPrep();/*This needs to be function before program is ever bound... Look at glGetUniformLocation documentation for mor details*/
    testShader.bind();
    testShader.setUniformWithVerticy(&shapeDrawer, uniLocation);/*This needs to be called after the shader has become part of the current state.
                                                                Check glUniform documentation for more details*/

    unsigned int vertexArrayTester;
    GLcheckError(glGenVertexArrays(1, &vertexArrayTester));
    GLcheckError(glBindVertexArray(vertexArrayTester));

    unsigned int testBuffer;
    glGenBuffers(1, &testBuffer);
    GLcheckError(glBindBuffer(GL_ARRAY_BUFFER,testBuffer));
    GLcheckError(glBufferData(GL_ARRAY_BUFFER, shapeDrawer.getVerticies().size() * sizeof(vertex), shapeDrawer.getVerticies().data(), GL_STATIC_DRAW));
    /*Remember that when using glBUfferData it assigns memory and data based on what is currently bound.
    This means that this function won't work and/or will activate/change the data of the wrong buffer.
    I believe that if you want to do it with a buffer that isn't bound you can use the function glNamedBufferData*/

    GLcheckError(glEnableVertexAttribArray(0));
    GLcheckError(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr));

    unsigned int indexTester;
    GLcheckError(glGenBuffers(1, &indexTester));
    GLcheckError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexTester));
    GLcheckError(glBufferData(GL_ELEMENT_ARRAY_BUFFER, shapeDrawer.getIndices().size() * sizeof(unsigned int), shapeDrawer.getIndices().data(), GL_STATIC_DRAW));
    /*Use getIndeces instead of trying to create a refrence to the vector data. It seems like that might matter.
    Maybe to understand why OpenGL doesn't work with a vector refrence think through what that would actually mean if we pass that in for our buffer data*/

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLcheckError(glClear(GL_COLOR_BUFFER_BIT));

        GLcheckError(glDrawElements(GL_TRIANGLES, shapeDrawer.getIndices().size(), GL_UNSIGNED_INT, NULL));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}