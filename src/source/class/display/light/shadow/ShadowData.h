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
/*
 * require initialize when window render on(can access to GPU)
 * because this class create shadow mapping shader itself
 */
class Shader;


namespace Display{
static const unsigned ShadowHighQuality=4096;
static const unsigned ShadowNormalQuality=2048;
static const unsigned ShadowLowQuality=1024;
/*
enum shadowMode{
	Normal,PSSM
};
*/
class ShadowData{
public:
	/*max_l_shadow=max shadows number for the parallel lights
	 * max_pl_shadow=max shadows number for the point lights
	 * shadow_quality is the quality of the shadow
	 */
	ShadowData(unsigned max_l_shadow,unsigned max_pl_shadow,
			unsigned shadow_quality=ShadowNormalQuality);
	virtual ~ShadowData();
	void sent_uniform(Shader *shader);
	void gen_shadow_map(Shader *shaderShadowMapping,std::vector<PointLight*>&point_lights,
			std::vector<ParallelLight*>&lights,Camera *camera,
			double shadow_dis,Display::Draw *d_obj);
	void gen_parallelLights_LVP(std::vector<ParallelLight*>&lights,Camera *camera,double shadow_dis);
	void gen_pointLight_LVP(std::vector<PointLight*>&point_lights);
	void gen_shadows_texture(Shader* shader,FrameBuffer* FBO,glm::mat4 *LVP,int num,Display::Draw *d_obj
			,int start_layer=0);

	glm::mat4 *LVP;
	glm::mat4 *PLVP;

	FrameBuffer* SFBO;
	FrameBuffer* PSFBO;

	bool enable_PSSM;
	//shadowMode shadow_mode;
	int s_num;
	int ps_num;

	unsigned shadow_quality;
	unsigned max_l_shadow;
	unsigned max_pl_shadow;
	int PSSM_split_num;

};
}
#endif /* SHADOWDATA_H_ */
