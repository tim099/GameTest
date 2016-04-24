#include "class/game/scene/LoadingScene.h"
#include "class/display/draw/Draw.h"
LoadingScene::LoadingScene() {
	timer=0;
	texture=0;
}
LoadingScene::~LoadingScene() {
	if(texture)delete texture;
}
void LoadingScene::scene_initialize(){
	texture=Texture2D::loadImage("files/texture/jannealter.png");
}
void LoadingScene::scene_terminate(){

}
void LoadingScene::scene_update(){
	if(timer<100)timer++;
	else timer=0;
}
void LoadingScene::scene_draw(){
	if(timer<25){
		draw->push(new RenderString("Now Loading.",0.04,glm::vec2(0.4,0.5)));
	}else if(timer<50){
		draw->push(new RenderString("Now Loading..",0.04,glm::vec2(0.4,0.5)));
	}else if(timer<75){
		draw->push(new RenderString("Now Loading...",0.04,glm::vec2(0.4,0.5)));
	}else{
		draw->push(new RenderString("Now Loading....",0.04,glm::vec2(0.4,0.5)));
	}
	draw->push(new DrawTexture(texture,new DrawData2D(1.0,glm::vec2(0,1),0.5)));
}

