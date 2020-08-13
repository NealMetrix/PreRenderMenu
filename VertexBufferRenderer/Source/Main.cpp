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
    while (userinput != "generate")
    {
        std::cout << "What action would you like to perform on your shapes" << std::endl;
        std::cout << "Enter help for possible actions" << std::endl << std::endl;
        std::cin >> userinput;
        action(userinput, shapeDrawer);
    }
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
    //std::cout << (initGlewValue == GLEW_OK) << std::endl;/*Debugging code to be sure glew is initialized properly.*/

    float verticyPositions[] =
    {
        0.0f, 0.0f,
        -0.5f,-0.5f,
        0.5f, -0.5f
    };

    unsigned int indexBufferTest[] =
    {
        0,1,2
    };
    /*I need to find a way to generate an array with the vectors that I have created. I could make it so I have a function that
    creates the buffer. But then I would risk using unallocated memory. So how do I generate it this memory. Let's try creating
    some sort of method that generates a heap allocated array and returns the pointer to the heap memory. I'll see if I can use
    a type vertex buffer for now.*/
    //vertex* vertexBufferPtr=verticyGeneratedBuffer(shapeDrawer);
    //unsigned int* indexBufferPtr = indicyGeneratedBuffer(shapeDrawer);'
    //Code temporarily disabled until it's solved.
    /*All of this is valid code.*/
    unsigned int i =1;
    unsigned int floor[2] = { 0,1 };
    unsigned int p = shapeDrawer.getIndices().at(i);
    floor[0] = p;
    //floor[0] = shapeDrawer.getVerticies()[*ptr].xCoordinate;

    /*std::cout << "Verticies" << std::endl;
    for (int i = 0; i < sizeof(*verticyPositions); i++)
        vertexBufferPtr[i].printCoordinates();

    std::cout << std::endl << "IndexBuffer elements" << std::endl;
    for (int i = 0; i < sizeof(*indexBufferPtr); i++)
        std::cout << indexBufferPtr[i] << std::endl;
        */
    /*Now how do I want to use the index buffer. The big thing is giving the person the ability to reorder how the index buffer
    is drawn. Let's try and create something similar as we made with the vertexes but for the index buffer*/
    shader testShader("Shaders/testShader.shader");
    testShader.bind();

    unsigned int vertexArrayTester;
    glGenVertexArrays(1, &vertexArrayTester);
    glBindVertexArray(vertexArrayTester);

    unsigned int testBuffer;
    glGenBuffers(1, &testBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,testBuffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * 2 * sizeof(float), verticyPositions, GL_STATIC_DRAW);
    /*Remember that when using glBUfferData it assigns memory and data based on what is currently bound.
    This means that this function won't work and/or will activate/change the data of the wrong buffer.
    I believe that if you want to do it with a buffer that isn't bound you can use the function glNamedBufferData*/

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

    unsigned int indexTester;
    glGenBuffers(1, &indexTester);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexTester);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int), indexBufferTest, GL_STATIC_DRAW);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}