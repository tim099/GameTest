#ifndef TEXTURE_H_
#define TEXTURE_H_
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "class/display/texture/image/Image.h"

const int P_NONE=0;
const int P_MipMap=1;
const int P_Linear=2;
const int P_Nearest=3;
class Texture2D;
class Shader2D;
class Shader;
class Texture {
public:
	Texture(GLuint TexID,GLenum target,GLenum type,GLenum format);
	virtual ~Texture();
	virtual Texture2D* Tex2D();


	static void usetextureVec(Shader* shader,std::vector<Texture*>& texvec,int num,const char *name);
	static GLuint gen_texture_vertex(GLfloat width,GLfloat height,glm::vec3 pos=glm::vec3(0,0,0));
	virtual void draw_texture(Shader* shader2D,double winaspect=1.0,double texaspect=1.0,GLfloat alpha=1.0,
			glm::vec3 pos=glm::vec3(0,0,0),double size=1.0);
	virtual int layer()const;
	virtual void sent_uniform(Shader* shader,int num,const char *name)const;
	GLuint TexID;
	GLenum target;
	GLenum format;
	GLenum type;
protected:
	static void TexFilterParameteri(GLenum target,int Parameteri);
};

#endif /* TEXTURE_H_ */
