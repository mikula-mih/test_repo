#version 400

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

void main()
{
  finalColor = texture(texture0, fragTexCoord)*fragColor(0, 1, 0, 1);
}
