#include "class/game/scene/LoadingScene.h"
#include "class/display/draw/Draw.h"
#include <cmath>
LoadingScene::LoadingScene() {
	timer=0;
	texture=0;
	loop_time=100;
}
LoadingScene::~LoadingScene() {
	if(texture)delete texture;
}
void LoadingScene::scene_initialize(){
	texture=Display::Texture2D::loadImage("files/texture/Loading.png");
}
void LoadingScene::scene_terminate(){

}
void LoadingScene::scene_update(){
	if(timer<loop_time)timer++;
	else timer=0;
}
void LoadingScene::scene_draw(){
	float font_size=0.04;
	std::string loading_str("Now Loading....");
	float del=0.1;
	float y;
	float time_val=(timer/(double)loop_time);
	for(unsigned i=0;i<loading_str.size();i++){
		y=0.5+0.03*sinf(2*M_PI*(i*del+time_val));
		draw->push(new Display::RenderString(loading_str.substr(i,1),
					font_size,glm::vec2(0.4+
					i*font_size*Display::RenderString::Font_Interval,y)));
	}
	draw->push(new Display::DrawTexture(texture,
			new Display::DrawData2D(1.0,glm::vec2(0,1),1.0)));
}

