#Shader Vertex
#version 330

layout(location = 0) in vec4 verticyPositions;

void main()
{
	gl_Position = verticyPositions;
}

#Shader Fragment
/*A note on how getline seems to work in our shaderClass parse method... at the very least how it works with !=npos
The .find didn't register <#>Shader when it came after Fragment or Vertex. I used <#> because my parser will actually
read <#>Shader in the comments and then read active if Vertex is on the same line.*/
#version 330

layout(location = 0) out vec4 color;
uniform vec4 vertColor;

void main()
{
	color = vertColor;
}