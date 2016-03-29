#ifndef MAPDRAWOBJECT_H_
#define MAPDRAWOBJECT_H_
#include "class/display/draw/drawObject/DrawObject.h"
class MapDrawObject : public DrawObject{
public:
	MapDrawObject(std::string tex_str = "",
			std::string NormalTex_str = "");
	virtual ~MapDrawObject();
	virtual void init(std::string tex_str = "",
			std::string NormalTex_str = "");
	//inherited update function ,will be call per frame
	virtual void update();



	//mark the model as updated
	inline void update_model(){
		model_updated=true;
	}


	//if model_buffer not exist,create the model buffer,else update the model_buffer
	void update_model_buffer();
	Model *model;
	//bool updated;

	//draw_map==true if this MapDrawObje should be draw in this frame
	bool draw;
protected:
	//clear the model_buffer
	void clear_model_buffer();

	//if model is updated,then model_buffer should update before render
	bool model_updated;
};

#endif /* MAPDRAWOBJECT_H_ */
