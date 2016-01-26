#ifndef VEC_H_
#define VEC_H_
#include <algorithm>
namespace Tim {
template <class Type,unsigned len>
class Vec {
public:
	Vec();
	Vec(Vec* vec);
	Vec(Type x,...);
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
Vec<Type,len>::Vec(Type x,...){
	data=new Type[len];
	va_list para;
	va_start(para,x);
	for(unsigned i=0;i<len;i++){
		//Type[i] = va_arg(para,Type);
	}
	//va_end(para);
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
