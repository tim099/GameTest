#ifndef SOURCE_CLASS_DISPLAY_DRAW_DRAWOBJECT_DYNAMICDRAWOBJECT_H_
#define SOURCE_CLASS_DISPLAY_DRAW_DRAWOBJECT_DYNAMICDRAWOBJECT_H_

#include "class/display/draw/drawObject/DrawObject.h"
#include "class/display/model/Model.h"
namespace Display{
class DynamicDrawObject: public DrawObject {
public:
	DynamicDrawObject();
	virtual ~DynamicDrawObject();
	virtual void update();
	//mark the model as updated
	inline void update_model(){
		model_updated=true;
	}

	//if model_buffer not exist,create the model buffer,else update the model_buffer
	void update_model_buffer();
	Model *model;
	//draw==true if this MapDrawObje should be draw in this frame
	bool draw;
protected:
	//clear the model_buffer
	void clear_model_buffer();

	//if model is updated,then model_buffer should update before render
	bool model_updated;
};
}
#endif /* SOURCE_CLASS_DISPLAY_DRAW_DRAWOBJECT_DYNAMICDRAWOBJECT_H_ */
