#ifndef CAMERA_H_
#define CAMERA_H_
#include <glm/glm.hpp>
#include <GL/glew.h>
class Camera {
public:
	Camera(glm::vec3 pos,glm::vec3 look_at,glm::vec3 up,float fovy,float z_near,float z_far);
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

	glm::mat4 sent_uniform(GLuint programID,float aspect);

	void tic();
	glm::vec3 pos;
	glm::vec3 look_at;
	glm::vec3 up;
	glm::vec3 vel;
	float fovy,z_near,z_far;
	float dis_alter_v;
protected:

};

#endif /* CAMERA_H_ */
