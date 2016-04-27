#ifndef FACE_H_
#define FACE_H_
namespace Display{
class Face {
public:
	Face(int v[3],int uv[3],int n[3]);
	virtual ~Face();
	int v[3],uv[3],n[3];
};
}
#endif /* FACE_H_ */
