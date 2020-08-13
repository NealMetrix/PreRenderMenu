# PreRenderMenu
An attempt to create a menu that controls what you draw in OpenGL.

I am busy trying to figure out if I can make a menu that generates the buffer that will be used to draw shapes and I might create a variable that gets fed into
uniforms so that the user can also change the color of the shape they are drawing also. The menu consists of console commands that don't look too different from
your typical console functions. However the section I am currently having trouble with is that I have stored the buffers using vectors and so I am busy trying to
design a way to convert the vector into a buffer so I can use it in my OpenGL functions. I haven't done much looking into getting OpenGL to read vectors... So if that is
possible I am currently unaware of it.
