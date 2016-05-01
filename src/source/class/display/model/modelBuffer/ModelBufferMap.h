#ifndef SOURCE_CLASS_DISPLAY_BUFFER_MODEL_MODELBUFFERMAP_H_
#define SOURCE_CLASS_DISPLAY_BUFFER_MODEL_MODELBUFFERMAP_H_
#include "class/display/model/modelBuffer/ModelBuffer.h"
#include "class/tim/map/MapContainer.h"
#include "class/tim/parser/Parser.h"
namespace Display{
class ModelBufferMap : public Tim::Parser{
public:
	ModelBufferMap();
	ModelBufferMap(std::string script_path);
	virtual ~ModelBufferMap();
	std::string get_name()const;
	void set_name(std::string name);

	void push(std::string name,ModelBuffer* buffer);
	ModelBuffer* get(std::string name);
	std::string folder_path;
protected:
	virtual inline std::string Script_name()const{
		return "#LOAD_MODELBUFFERMAP_SCRIPT";
	}
	virtual void Parse_Script(std::istream &is,std::string &line);
	virtual void Parse_Header(std::istream &is,std::string &line);

	void Parse_ModelBuffer(std::istream &is);
	Tim::MapContainer<std::string,ModelBuffer>mbuffer_map;

	std::string name;
};
}
#endif /* SOURCE_CLASS_DISPLAY_BUFFER_MODEL_MODELBUFFERMAP_H_ */
