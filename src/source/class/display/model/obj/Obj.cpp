#include <class/display/model/obj/Obj.h>
#include "class/display/model/Model.h"
#include <cstring>
#include <string>
namespace Display{
#define WHITESPACE " \t\n\r"
Obj::Obj() {

}
Obj::~Obj() {

}
Obj* Obj::load_obj(const char* path){

	FILE* file = fopen(path,"r");
	if( file == NULL ){
	    printf("Impossible to open the obj file %s !\n",path);
	    return 0;
	}
	Obj* obj=new Obj();
	char cbuffer[256];
	int vertexIndex[3],uvIndex[3],normalIndex[3];
	while(true){
	    int res=fscanf(file,"%s",cbuffer);
	    if (res == EOF)break;

	    if(!strcmp(cbuffer,"v")){
	        glm::vec3 vertex;
	        fscanf(file,"%f %f %f\n",&vertex.x,&vertex.y,&vertex.z);
	        obj->v.push_back(vertex);
	    }else if (!strcmp(cbuffer,"vt")){
	        glm::vec2 uv;
	        fscanf(file,"%f %f\n",&uv.x,&uv.y);
	        obj->uv.push_back(uv);
	    }else if (!strcmp(cbuffer,"vn")){
	        glm::vec3 normal;
	        fscanf(file,"%f %f %f\n",&normal.x,&normal.y,&normal.z);
	        obj->vn.push_back(normal);
	    }else if (!strcmp(cbuffer,"f")){
	        int matches=fscanf(file,"%d/%d/%d %d/%d/%d %d/%d/%d\n",
	        		&vertexIndex[0],&uvIndex[0],&normalIndex[0],&vertexIndex[1],
	        		&uvIndex[1],&normalIndex[1],&vertexIndex[2],&uvIndex[2],&normalIndex[2]);

	        if (matches!=9){
	            printf("File can't be read by our simple parser:(Try exporting with other options\n");
	            delete obj;
	            return 0;
	        }
	        obj->fs.push_back(Face(vertexIndex,uvIndex,normalIndex));
	    }
	}
	fclose(file);
	return obj;
}
}
