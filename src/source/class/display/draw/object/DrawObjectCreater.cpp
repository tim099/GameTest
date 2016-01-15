#include "class/display/draw/object/DrawObjectCreater.h"
#include "class/display/draw/object/DrawObject.h"
#include "class/display/model/Model.h"
#include "class/display/buffer/BufferObject.h"
#include "class/display/texture/Texture.h"
#include "class/display/texture/texture2D/Texture2D.h"
DrawObjectCreater::DrawObjectCreater() {

}
DrawObjectCreater::~DrawObjectCreater() {
	for(unsigned i=0;i<b_objs.size();i++){
		delete b_objs.at(i);
	}
	for(unsigned i=0;i<m_objs.size();i++){
		delete m_objs.at(i);
	}
	for(unsigned i=0;i<texturebuffers.size();i++){
		delete texturebuffers.at(i);
	}
}
DrawObject *DrawObjectCreater::creat_draw_obj(const char* obj_path,const char* tex_path
		,float size,bool to_o){
	Model *m=Model::load_obj(obj_path,size,to_o);
	BufferObject *b_obj=new BufferObject(m);
	Texture* texture=Texture2D::loadBMP(tex_path);
	DrawObject *d_obj=new DrawObject(b_obj,texture);
	b_objs.push_back(b_obj);
	m_objs.push_back(m);
	texturebuffers.push_back(texture);
	return d_obj;
}
