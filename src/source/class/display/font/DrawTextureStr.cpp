#include "class/display/font/DrawTextureStr.h"

DrawTextureStr::DrawTextureStr(Texture *_tex,DrawData* _data) : DrawTexture(_tex,_data){

}
DrawTextureStr::~DrawTextureStr() {
	delete tex;
}

