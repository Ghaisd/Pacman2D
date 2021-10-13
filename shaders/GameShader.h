#ifndef __GAMESHADER_H_
#define __GAMESHADER_H_

#include <string>

static const std::string gameVertexShaderSrc = R"(
#version 430 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_texCoords;
out vec2 outTexCoords;
out vec2 pos_model;
//We specify our uniforms. We do not need to specify locations manually, but it helps with knowing what is bound where.
/*layout(location=0)*/ uniform mat4 u_TransformationMat = mat4(1);
/*layout(location=1) */uniform mat4 u_ViewMat           = mat4(1);
/*layout(location=2)*/ uniform mat4 u_ProjectionMat     = mat4(1);
uniform vec3 aPositions;


void main()
{
//We multiply our matrices with our position to change the positions of vertices to their final destinations.
outTexCoords=a_texCoords;
pos_model=a_Position.xy;
gl_Position = u_ProjectionMat * u_ViewMat * u_TransformationMat * vec4(a_Position, 1.0f);
}
)";

static const std::string gameFragmentShaderSrc = R"(
#version 430 core
out vec4 color;
sample smooth in vec2 outTexCoords;
in vec2 pos_model;
uniform vec4 u_Color;
uniform sampler2D aTexture;
uniform int usesTexture;
uniform int isCircle;
uniform int is_Magic;
void main()
{
	if(usesTexture==0)
	{
		color=u_Color;
	}

else
{
color = texture(aTexture,outTexCoords);
if(color.x>0.95&&color.y>0.95&&color.z>0.95) discard;
}
if(isCircle==1)
	{

	vec2 center=vec2(-0.5,-0.5);
	float dist=length(pos_model-center);
	if (is_Magic==0)
	{

	if(dist>0.15){
		discard;
	}

  }
else 
{
if (dist>0.3)
	discard;
	/*color.r=0.929f;
	color.g=0.580f;
	color.b= 0.3290f;*/
	color = vec4(0.929f,0.580f,0.3290f, 1.0f);
}

	}

//color=u_Color;
}
)";


#endif 
