#ifndef DRAWDATAEX_H_
#define DRAWDATAEX_H_
namespace Display{
class Shader;
namespace drawDataEX{
class DrawDataEX {
public:
	DrawDataEX();
	virtual ~DrawDataEX();
	/*
	 * can sent extra data to shader before draw
	 */
	virtual void prepare_to_draw(Shader* shader);
	/*
	 * clear the extra data sent to shader
	 */
	virtual void draw_end(Shader* shader);
};
}
}
#endif /* DRAWDATAEX_H_ */
