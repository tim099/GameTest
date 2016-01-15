#ifndef LIGHTCONTROL_H_
#define LIGHTCONTROL_H_

#define MAX_LIGHT 100
#include "class/display/light/PointLight.h"
#include "class/display/light/ParallelLight.h"
#include "class/display/light/shadow/ShadowData.h"
#include "class/display/draw/Draw.h"
#include <vector>

class Shader;
class Camera;
class FrameBuffer;
class LightControl {
public:
	LightControl(float draw_dis);
	virtual ~LightControl();
	void sent_uniform(Shader *shader,glm::vec3 camera_pos);

	unsigned parallel_light_size()const;
	unsigned point_light_size()const;
	PointLight* get_point_light(int i)const;
	ParallelLight* get_parallel_light(int i)const;

	void push_point_light(PointLight* l);
	void push_parallel_light(ParallelLight* l);
	void gen_shadow(Camera *camera,double shadow_dis,Draw *d_obj);
	std::vector<ParallelLight*>parallel_lights;
	std::vector<PointLight*>point_lights;
	ShadowData *shadowData;

protected:
	float draw_dis;
};

#endif /* LIGHTCONTROL_H_ */
