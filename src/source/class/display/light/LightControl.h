#ifndef LIGHTCONTROL_H_
#define LIGHTCONTROL_H_


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
static const int MAX_LIGHT=100;
static const int MAX_POINT_LIGHT=100;

	/*
	 * draw distance determined how far a point light will be render
	 * if distance from point light to camera is farther than draw_distance
	 * than this point light will not be draw
	 */
	LightControl(float draw_distance);
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
	/*
	 * find the point lights to draw this frame
	 */
	void choose_point_light(glm::vec3 camera_pos);
	/*
	 * point lights buffer of point lights to draw at current frame
	 */
	std::vector<PointLight*>tmp_point_lights;
	float draw_dis;
};

#endif /* LIGHTCONTROL_H_ */
