#ifndef SOURCE_CLASS_DISPLAY_BUFFER_MODEL_ALLMODELBUFFERS_H_
#define SOURCE_CLASS_DISPLAY_BUFFER_MODEL_ALLMODELBUFFERS_H_
#include "class/tim/map/MapTree.h"
#include "class/tim/globalObject/GlobalObject.h"
#include "class/display/model/modelBuffer/ModelBufferMap.h"
#include "class/tim/globalObject/GlobalObject.h"
namespace Display{
class AllModelBuffers: public Tim::MapTree<ModelBufferMap, ModelBuffer>,
		public Tim::Parser,
		public Tim::GlobalObject<AllModelBuffers> {
public:
	AllModelBuffers();
	AllModelBuffers(std::string script_path);
	static ModelBuffer *get_cur_model(std::string obj_path);
	virtual ~AllModelBuffers();
protected:
	virtual inline std::string Script_name() const {
		return "#LOAD_ALL_MODELBUFFERS_SCRIPT";
	}
	virtual void Parse_Script(std::istream &is, std::string &line);
	virtual void Parse_Header(std::istream &is, std::string &line);
	virtual void Parse_map(std::istream &is);
	virtual void Parse_dir(std::istream &is);
	std::string folder_path;
};
}
#endif /* SOURCE_CLASS_DISPLAY_BUFFER_MODEL_ALLMODELBUFFERS_H_ */
