#ifndef SHADER2D_H_
#define SHADER2D_H_
#include <glm/glm.hpp>
#include "class/display/shader/Shader.h"
const int SobelMode=1<<0;
const int AddOnMode=1<<1;
const int ColorAlterMode=1<<2;
class Texture;
class Shader2D : public Shader{
public:
	Shader2D();
	virtual ~Shader2D();

};

#endif /* SHADER2D_H_ */
