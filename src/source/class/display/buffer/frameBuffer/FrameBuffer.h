#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_
#include <vector>
#include "class/display/buffer/Buffer.h"
#include "class/display/texture/Texture.h"
#include "class/tim/math/vec2.h"
#include "class/tim/math/vec4.h"
namespace Display{
class FrameBuffer {
public:
	FrameBuffer(math::vec2<int> size);
	virtual ~FrameBuffer();

	static void unbind_buffer(math::vec2<int> size);
	void bind_buffer(bool attach_all_texture=true);
	void bind_depth_texture(int i);
	void ReadPixels(glm::ivec2 pos,glm::ivec2 size,GLenum format,GLenum type,GLvoid * data);
	glm::vec4 get_world_space_pos(math::vec2<float> screen_space_pos,glm::mat4 inverseMat);
	float aspect()const;

	GLuint GenFramebuffer();
	Texture* gen_color_texture(GLint internalformat,GLenum format
			,GLenum type=GL_UNSIGNED_BYTE,int Parameteri=P_MipMap);
	Texture* gen_depth_texture(GLint internalformat,GLenum format
			,GLenum type=GL_UNSIGNED_BYTE,int Parameteri=P_MipMap);
	void gen_depth_buffer();
	static void check_frame_buffer();
	Texture* push_depth_texture(Texture* tex);
	Texture* push_color_texture(Texture* tex);
	glm::ivec2 size;
	Texture* depth_buffer;
	GLuint FBOID;
	std::vector<Texture*>color_textures;
	std::vector<Texture*>depth_textures;
};
}
#endif /* FRAMEBUFFER_H_ */
