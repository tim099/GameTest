#ifndef DRAWDATAEX_H_
#define DRAWDATAEX_H_
class Shader;
class DrawDataEX {
public:
	DrawDataEX();
	virtual ~DrawDataEX();
	virtual void prepare_to_draw(Shader* shader2D);
	virtual void draw_end(Shader* shader2D);
};

#endif /* DRAWDATAEX_H_ */
