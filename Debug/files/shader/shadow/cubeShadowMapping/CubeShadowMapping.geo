#version 400 core
#define MAX_LVP 6 //
#define MAX_VERTICES 18 //=3*MAX_LVP

layout(triangles)in;
layout(triangle_strip,max_vertices=MAX_VERTICES)out;

#include <files/shader/shadow/multiShadowCommon.geo>

void main(){
	multiShadowCommon();
}  