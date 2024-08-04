#shader vertex
#version 330 core

// the zero here is the same is the index 0 that is the first parameter of
// the glVertexAttribPointer, indicating we're using the attribute we defined
// in the call to that function as something called 'position' that's a vec4.
//
// we're calling it a vec4 because gl_Position will need a vec4. The attribute
// specification knows that each attribute is 2 floats, it will stuff those
// two floats into a vec4 inthe first two positions, and have zeros for the
// other positions (which we're not using anyway).

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TextCoord;   // variant output to frag shader

uniform mat4 u_mvpMatrix;

void main() {
    gl_Position = u_mvpMatrix * position;
    v_TextCoord = texCoord;
}

#shader fragment
#version 330 core

// the layout doesn't change, we're still looking at the same layout, so no
// need to change that. We are changing the variable parameter from an "in"
// parameter in the vertex shader that expected position to be passed in, to 
// an "out" parameter of type vec4 called "color". This is what we need to
// set before leaving the shader, and is the output color of the fragment
// (pixel) that we're currently working on.

layout(location = 0) out vec4 color;

in vec2 v_TextCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main() {
    vec4 texColor = texture(u_Texture, v_TextCoord);
    // color = vec4(v_TextCoord, 0.0f, 1.0f);
    color = texColor;
}