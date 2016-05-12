#ifndef SOURCE_CLASS_DISPLAY_TEXTURE_DRAWDATA_DRAWDATAEX_COLORALTER_H_
#define SOURCE_CLASS_DISPLAY_TEXTURE_DRAWDATA_DRAWDATAEX_COLORALTER_H_

#include <glm/glm.hpp>
#include "class/display/draw/drawData/drawDataEX/DrawDataEX.h"
namespace Display{
namespace drawDataEX{
class ColorAlter: public DrawDataEX {
public:
	ColorAlter(glm::vec3 alter_value);
	virtual ~ColorAlter();
	virtual void prepare_to_draw(Shader* shader2D);
	virtual void draw_end(Shader* shader2D);
	glm::vec3 alter_value;
};
}
}

#endif /* SOURCE_CLASS_DISPLAY_TEXTURE_DRAWDATA_DRAWDATAEX_COLORALTER_H_ */
