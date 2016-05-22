#ifndef LightControl_H_
#define LightControl_H_


#include "class/display/light/PointLight.h"
#include "class/display/light/ParallelLight.h"
#include "class/display/light/CubeLight.h"
#include "class/display/light/shadow/ShadowData.h"

#include <vector>



namespace Display{
class Shader;
class Camera;
class FrameBuffer;
class Draw;
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
	void gen_shadow(Shader *shaderShadowMapping,Camera *camera,Draw *d_obj);


	unsigned parallel_light_size()const;
	unsigned point_light_size()const;
	PointLight* get_point_light(int i)const;
	ParallelLight* get_parallel_light(int i)const;

	void push_light(Display::PointLight* l);
	void push_light(Display::ParallelLight* l);
	void push_light(Display::CubeLight* l);

	void push_temp_light(Display::PointLight* l);
	void push_temp_light(Display::ParallelLight* l);
	void push_temp_light(Display::CubeLight* l);

	void remove_light(Display::PointLight* l);
	void remove_light(Display::ParallelLight* l);
	void remove_light(Display::CubeLight* l);

	void clear_temp_data();
	std::vector<ParallelLight*>parallel_lights;
	std::vector<PointLight*>point_lights;
	std::vector<CubeLight*>cube_lights;
	std::vector<ParallelLight*>temp_parallel_lights;
	std::vector<PointLight*>temp_point_lights;
	std::vector<CubeLight*>temp_cube_lights;
	ShadowData *shadowData;
	double shadow_dis;
protected:
	/*
	 * find the point lights to draw this frame
	 */
	void choose_point_light(glm::vec3 camera_pos);
	/*
	 * point lights buffer of point lights to draw at current frame
	 */
	std::vector<PointLight*>selected_point_lights;
	float draw_dis;
};
}
#endif /* Display::LightControl_H_ */
