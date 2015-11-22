#ifndef SOBELTASK_H_
#define SOBELTASK_H_
#include "class/tim/Thread/task/Task.h"
#include <glm/glm.hpp>
template <class DataType>class Image;

template <class DataType>
class SobelTask{
public:
	SobelTask(Image<DataType>* image,glm::vec2 dv,glm::ivec2 se,float clip);
	virtual ~SobelTask();
protected:
	virtual void ExecuteTask();
};

#endif /* SOBELTASK_H_ */
