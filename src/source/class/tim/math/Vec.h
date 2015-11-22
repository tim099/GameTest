#ifndef VEC_H_
#define VEC_H_
#include <algorithm>
namespace Tim {
template <class Type,unsigned len>
class Vec {
public:
	Vec();
	Vec(Vec* vec);
	virtual ~Vec();
	unsigned get_len()const;
	Type *data;
};
//-----------------------------cpp
template <class Type,unsigned len>
Vec<Type,len>::Vec() {
	data=new Type[len];
}
template <class Type,unsigned len>
Vec<Type,len>::Vec(Vec* vec) {
	data=new Type[len];
	std::copy(vec->data,vec->data+len,data);
}
template <class Type,unsigned len>
Vec<Type,len>::~Vec() {
	delete[] data;
}
template <class Type,unsigned len>
unsigned Vec<Type,len>::get_len()const{
	return len;
}





} /* namespace Tim */






#endif /* VEC_H_ */
