#ifndef TEXTURE_H_
#define TEXTURE_H_
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include "class/display/texture/image/Image.h"
#include "class/display/draw/drawData/DrawData.h"

const int P_NONE=0;
const int P_MipMap=1;
const int P_Linear=2;
const int P_Nearest=3;
//===========================

class Texture2D;
class Shader2D;
class Shader;
class Texture {
public:
	Texture(GLuint TexID,GLenum target,GLenum type,GLenum format);
	Texture();
	virtual ~Texture();
	virtual Texture2D* Tex2D();
	virtual void draw_texture(Shader2D* shader2D,DrawData *data);
	virtual int layer()const;
	virtual void sent_uniform(Shader* shader,int num,const char *name)const;

	virtual double get_aspect();


	static void sent_textureVec(Shader* shader,std::vector<Texture*>& texvec,int num,const char *name);
	static GLuint gen_texture_vertex(glm::vec2 size);
	static GLuint gen_texture_uv();

	void bind_texture();


	GLuint TexID;
	GLenum target;
	GLenum format;
	GLenum type;
protected:
	virtual void draw(Shader2D* shader2D,DrawData *data);
	static void TexFilterParameteri(GLenum target,int Parameteri);
};

#endif /* TEXTURE_H_ */
