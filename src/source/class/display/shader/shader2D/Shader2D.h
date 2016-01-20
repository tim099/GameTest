#ifndef SHADER2D_H_
#define SHADER2D_H_
#include <glm/glm.hpp>
#include "class/display/shader/Shader.h"
const int SobelMode=1<<0;
const int AddOnMode=1<<1;
const int ColorAlterMode=1<<2;
//==================================
const int Type_RGB=0;
const int Type_RGBA=1;
const int Type_GrayScale=2;
class Texture;
class Shader2D : public Shader{
public:
	Shader2D(std::string name=std::string("default"));
	virtual ~Shader2D();
	void set_format(GLenum format);

protected:
	int textureData;
};

#endif /* SHADER2D_H_ */
