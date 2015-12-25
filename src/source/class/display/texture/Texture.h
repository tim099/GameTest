#ifndef TEXTURE_H_
#define TEXTURE_H_
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "class/display/texture/image/Image.h"
#include "class/display/texture/drawData/DrawData.h"
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
	virtual void draw_texture(Shader* shader2D,DrawData *data);
	virtual int layer()const;
	virtual void sent_uniform(Shader* shader,int num,const char *name)const;

	static void usetextureVec(Shader* shader,std::vector<Texture*>& texvec,int num,const char *name);
	static GLuint gen_texture_vertex(glm::vec2 size);
	static GLuint gen_texture_uv();
	static glm::vec2 convert_to_texcoord(glm::vec2 pos);
	static glm::vec2 convert_to_wincoord(glm::vec2 pos);
	void bind_texture();

	GLuint TexID;
	GLenum target;
	GLenum format;
	GLenum type;
protected:
	static void TexFilterParameteri(GLenum target,int Parameteri);
};

#endif /* TEXTURE_H_ */
