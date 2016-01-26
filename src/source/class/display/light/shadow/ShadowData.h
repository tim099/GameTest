#ifndef SHADOWDATA_H_
#define SHADOWDATA_H_
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "class/display/buffer/frameBuffer/FrameBuffer.h"
#include "class/display/camera/Camera.h"
#include "class/display/light/ParallelLight.h"
#include "class/display/light/PointLight.h"
#include "class/display/draw/Draw.h"
class Shader;
class ShadowData{
public:
	ShadowData(unsigned max_l_shadow,unsigned max_pl_shadow);
	virtual ~ShadowData();
	void sent_uniform(Shader *shader);
	void gen_shadow_map(std::vector<PointLight*>&point_lights,
			std::vector<ParallelLight*>&lights,Camera *camera,
			double shadow_dis,Draw *d_obj);
	void gen_parallelLights_LVP(std::vector<ParallelLight*>&lights,Camera *camera,double shadow_dis);
	void gen_pointLight_LVP(std::vector<PointLight*>&point_lights);
	void gen_shadows(Shader* shader,FrameBuffer* FBO,glm::mat4 *LVP,int num,Draw *d_obj,int depth_tex=0
			,int start_layer=0);

	glm::mat4 *LVP;
	glm::mat4 *PLVP;

	FrameBuffer* SFBO;
	FrameBuffer* PSFBO;

	int s_num;
	int ps_num;
	unsigned max_l_shadow;
	unsigned max_pl_shadow;
	Shader *shaderMultiShadowMapping;
	Shader *shaderCubeShadowMapping;
};

#endif /* SHADOWDATA_H_ */
