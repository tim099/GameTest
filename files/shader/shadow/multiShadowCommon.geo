uniform mat4 LVP[MAX_LVP];
uniform mat4 M; 
uniform int LVP_num;
uniform int start_layer;
void multiShadowCommon(){
	for(int n=0;n<LVP_num;n++){
		for(int i=0;i<3;i++){
			gl_Position=(LVP[n]*M*gl_in[i].gl_Position);//
			gl_Layer=n+start_layer;
			EmitVertex();
		}
		EndPrimitive();
	}

}