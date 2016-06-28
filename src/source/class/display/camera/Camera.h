#ifndef CAMERA_H_
#define CAMERA_H_
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>
#include "class/tim/geometry/3D/AABB.h"
namespace Display{
class Camera {
public:
	Camera(glm::vec3 pos,glm::vec3 look_at,glm::vec3 up,float fovy,float z_near,float z_far);
	Camera(Camera* camera);
	virtual ~Camera();

	glm::mat4 view_matrix(float aspect);
	glm::mat4 view()const;
	glm::mat4 perspective(float aspect);


	glm::vec3 look_vec()const;
	glm::vec3 look_vec_xz()const;
	float look_ry()const;
	float look_dis()const;

	glm::vec3 yaw_vec()const;

	void move(glm::vec3 del);
	void move_foward(float val);
	void move_side(float val);

	void rotate(glm::vec3 v,float degrees);
	void dis_alter(float dis);

	glm::mat4 sent_uniform(GLuint programID,float aspect,
			std::string name=std::string("VP"));

	void gen_PSSM_AABB(int split_num, float aspect);
	std::vector<Tim::AABB> * get_PSSM_AABBs();

	void update();

	glm::vec3 pos;
	glm::vec3 look_at;
	glm::vec3 up;
	glm::vec3 v;
	float fovy,z_near,z_far;
	float shadow_far;
	float dis_alter_v;

	std::vector<Tim::AABB> PSSM_AABBs;
	int PSSM_split_num;
protected:

};
}
#endif /* CAMERA_H_ */
