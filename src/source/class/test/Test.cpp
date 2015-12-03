#include "class/test/Test.h"
#include "class/display/texture/texture3D/Texture2DArr.h"
#include "class/display/texture/texture2D/Texture2D.h"
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>

Test::Test() {
	sun_col1=glm::vec3(2.2,2.3,2.5);
	sun_col2=glm::vec3(1.2,0.9,0.5);
	timeloop=0;
	loop_time=10000;
	tiger_ry=0;
	shadow_dis=1.0;

	end=false;
	stop_the_sun=false;
	to_sobel=false;
	display_time=false;
	shader_at=0;

	max_point_light=5;
	map=new Map();

	window=new Window(glm::ivec2(1366,733),"Age of Cube",false);//must before any draw obj
	//window=new Window(glm::ivec2(1920,1080),"Age of Cube",true);//must before any draw obj
	d_obj=new Draw();
	texmap=new TextureMap(std::string("files/script/loadTexture/loadTestTexture.txt"));
	dmap=new DisplayMap(map,d_obj,texmap,window);
	//window=new Window(glm::ivec2(1920,1080),"hello tim",true);

	lightControl=new LightControl(5000);


	keyboard=new KeyBoard();
	mouse=new Mouse();
	camera=new Camera(glm::vec3(36.0,24.0,24.0),glm::vec3(34.0,22.0,27.0),
			glm::vec3(0,1,0),60.0,0.1f,50000.0f);

	VertexArrayID=Buffer::GenVertexArray();
	callback_rigister(window->get_window(),keyboard,mouse);
	creat_shader();

    map->load_map("files/maps/map011");

    creat_light();//
    prepare_draw_obj();

    render_thread=new Tim::Thread(REALTIME_PRIORITY_CLASS);
    renderer=new Renderer(lightControl,d_obj,window,(&cur_shader),camera,mouse,texmap,&shadow_dis);
    thread_pool=new Tim::ThreadPool(4);
    render_task=new RenderTask(renderer,window);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    window->render_off();
    dmap->gen_map_obj(thread_pool);
}
Test::~Test() {

}
void Test::terminate(){

	delete texmap;

	delete dmap;
	delete lightControl;
	delete keyboard;
	delete mouse;

	delete camera;
	delete thread_pool;
	delete render_task;
	render_thread->Terminate();
	for(unsigned i=0;i<shaders.size();i++){
		delete shaders.at(i);
	}
	for(unsigned i=0;i<b_objs.size();i++){
		delete b_objs.at(i);
	}
	delete d_obj;
	delete map;
	delete window;
	glfwTerminate();
}
void Test::input(){
	if(mouse->mid){
		//std::cout<<"move"<<(int)(mouse->pos.x)<<","<<(int)mouse->prev_pos.x<<std::endl;
		camera->rotate(glm::vec3(0,1,0),-0.15*mouse->pos_delta().x);
		camera->rotate(camera->yaw_vec(),0.15*mouse->pos_delta().y);
	}
	if(keyboard->pressed('Q')){
		ico->push_position(new Position(mouse->world_pos,glm::vec3()));
	}
	if(keyboard->get('E')){
		camlight->shadow^=1;
	}
	if(keyboard->get(256)){//ESC
		std::cout<<"END"<<std::endl;
		end=true;
	}
	if(mouse->right){
		camera->vel+=(float)(0.001f*sqrt(camera->look_dis()+0.001)*mouse->pos_delta().y)*camera->look_vec_xz();
		camera->vel+=(float)(-0.001f*sqrt(camera->look_dis()+0.001)*mouse->pos_delta().x)*
				glm::cross(camera->look_vec_xz(),glm::vec3(0,1,0));
	}
	if(mouse->left){
		camera->vel+=(float)(-0.0005f*sqrt(camera->look_dis()+0.001)*mouse->pos_delta().y)*glm::vec3(0,1,0);
		camera->vel+=(float)(-0.001f*sqrt(camera->look_dis()+0.001)*mouse->pos_delta().x)*
				glm::cross(camera->look_vec_xz(),glm::vec3(0,1,0));
	}
	if(mouse->scroll){
		camera->dis_alter_v+=sqrt(camera->look_dis()+0.1)*(0.05*mouse->scroll);
	}
	if(keyboard->pressed('M')){
		timeloop++;
		if(timeloop>=loop_time)timeloop=0;
		//sunlight->pos=glm::vec3(glm::rotate(0.5f,glm::vec3(-1,0,1))*glm::vec4(sunlight->pos,1));
	}
	if(keyboard->pressed('J')){
		timeloop--;
		if(timeloop<0)timeloop=loop_time-1;
		//sunlight->pos=glm::vec3(glm::rotate(-0.5f,glm::vec3(-1,0,1))*glm::vec4(sunlight->pos,1));
	}
	if(keyboard->get('H')){
		loop_time*=1.05;
		timeloop*=1.05;
	}
	if(keyboard->get('Y')){
		loop_time*=0.95;
		timeloop*=0.95;
		if(loop_time<10)loop_time=10;
	}
	if(keyboard->get('N')){
		stop_the_sun^=1;
	}
	if(keyboard->get('U')){
		to_sobel^=1;
	}
	if(keyboard->pressed('B')){
		int x=(int)fabs(camera->look_at.x),y=(int)fabs(camera->look_at.y),z=(int)fabs(camera->look_at.z);
		if(!map->get(x,y,z)){
			map->set(x,y,z,1);
			dmap->update_map(x,y,z);
		}
	}
	if(keyboard->pressed('V')){
		int x=(int)fabs(camera->look_at.x),y=(int)fabs(camera->look_at.y),z=(int)fabs(camera->look_at.z);
		if(map->get(x,y,z)){
			map->set(x,y,z,0);
			dmap->update_map(x,y,z);
		}
	}
	if(keyboard->get('O')){
		cur_shader=shaderBasic;
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	if(keyboard->get('P')){
		cur_shader=shaderNormalMapping;
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	if(keyboard->get('L')){
		cur_shader=shaderLightScatter;
	}
	if(keyboard->get(GLFW_KEY_LEFT)){
		if(shader_at>0)shader_at--;
		else shader_at=shaders.size()-1;
		cur_shader=shaders.at(shader_at);
	}
	if(keyboard->get(GLFW_KEY_RIGHT)){
		if(shader_at<(int)shaders.size()-1)shader_at++;
		else shader_at=0;
		cur_shader=shaders.at(shader_at);
	}
	if(keyboard->pressed(GLFW_KEY_UP)){
		if(shadow_dis>0.01)shadow_dis*=0.98;
	}
	if(keyboard->pressed(GLFW_KEY_DOWN)){
		if(shadow_dis<30.0)shadow_dis*=1.01;
	}
	if(keyboard->get('C')){
		look_at->push_position(new Position(camera->look_at+glm::vec3(0,0.1,0),
				glm::vec3(0,camera->look_ry(),0)));
		lightControl->push_point_light(new PointLight(camera->look_at,camlight->color,
				camlight->shadow));
	}
	if(keyboard->get('1')){
		camlight->color+=glm::vec3(0.3,0.0,0.0);
	}
	if(keyboard->get('2')){
		camlight->color+=glm::vec3(-0.3,0.0,0.0);
	}
	if(keyboard->get('3')){
		camlight->color+=glm::vec3(0.0,0.3,0.0);
	}
	if(keyboard->get('4')){
		camlight->color+=glm::vec3(0.0,-0.3,0.0);
	}
	if(keyboard->get('5')){
		camlight->color+=glm::vec3(0.0,0.0,0.3);
	}
	if(keyboard->get('6')){
		camlight->color+=glm::vec3(0.0,0.0,-0.3);
	}
	if(keyboard->pressed('7')){
		camlight->color+=glm::vec3(0.05,0.05,0.05);
	}
	if(keyboard->get('8')){
		camlight->color+=glm::vec3(-0.05,-0.05,-0.05);
	}
	if(keyboard->get('9')){
		camlight->color=glm::vec3(0.05,0.05,0.05);
	}
	if(keyboard->get('0')){
		camlight->color=glm::vec3(((rand()%10000)/4000.0),((rand()%10000)/4000.0),((rand()%10000)/4000.0));
	}
	if(keyboard->get('I')){
		dmap->range+=10;
	}
	if(keyboard->get('K')){
		if(dmap->range>10)dmap->range-=10;
		else dmap->range=0;
	}

	if(keyboard->pressed('T')){
		camera->rotate(camera->yaw_vec(),1);
	}
	if(keyboard->pressed('G')){
		camera->rotate(camera->yaw_vec(),-1);
	}
	if(keyboard->pressed('Z')){
		camera->move(glm::vec3(0,0.03,0));
	}
	if(keyboard->pressed('X')){
		camera->move(glm::vec3(0,-0.03,0));
	}
	if(keyboard->pressed('W')){
		if(dmap->max_y<dmap->MY)dmap->max_y++;
		dmap->gen_map_obj(thread_pool);
		//dmap->gen_map_obj();
	}
	if(keyboard->pressed('S')){
		if(dmap->max_y>0)dmap->max_y--;
		dmap->gen_map_obj(thread_pool);
	}
	if(keyboard->pressed('A')){
		camera->move_side(0.04f);
	}
	if(keyboard->pressed('D')){
		camera->move_side(-0.04f);
	}
	if(keyboard->pressed('R')){
		camera->dis_alter(-0.05);
	}
	if(keyboard->pressed('F')){
		camera->dis_alter(0.05);
	}
}
void Test::set_obj_pos(Camera *camera){
	static Position starpos(glm::vec3(0,0,0),glm::vec3());
	static Position sunpos(glm::vec3(5.1,80.6,0.1),glm::vec3());
    //obj move
    tiger_ry=360.0f*((float)timeloop/loop_time);
    starpos.r.y=360.0f*((float)timeloop/loop_time);
    //if(!stop_the_sun)sunlight->pos=glm::vec3(glm::rotate(0.02f,glm::vec3(-1,0,1))*glm::vec4(sunlight->pos,1));
    glm::vec3 sun_pos=glm::vec3(glm::rotate(360.0f*((float)timeloop/loop_time),glm::vec3(-1,0,1))
    *glm::vec4(glm::vec3(300,0,500),1));
    s_light->vec=-sun_pos;

    s_light->color=(1.0f-((float)timeloop/loop_time))*sun_col1+((float)timeloop/loop_time)*sun_col2;

    sunpos.pos=sun_pos;
    sun->push_temp_position(new Position(sunpos));
    tiger->push_temp_position(new Position(glm::vec3(33.0,21.47,26.0),glm::vec3(0,tiger_ry,0)));
    //Position* look_at_pos=
    look_at->push_temp_position(new Position(camera->look_at,glm::vec3(0,camera->look_ry(),0)));
    //look_at->push_temp_position(new Position(glm::vec3(0,0,-1),glm::vec3(0,0,0),look_at_pos));
    stars->push_temp_position(new Position(starpos));
    galaxy->push_temp_position(new Position(starpos));
    //ico->push_temp_position(new Position(mouse->world_pos,glm::vec3()));
}
void Test::update_map(Camera *camera){
	dmap->draw_map(camera);//push position
    camlight->pos=camera->look_at;
    set_obj_pos(camera);
}
void Test::draw_all_objects(Shader *shader,FrameBuffer *FBO,Camera *camera,double &time){
    if(display_time){
        time=glfwGetTime();
    }
    lightControl->gen_shadow(camera,shadow_dis,d_obj);
    shader->active_shader();
	FBO->bind_buffer();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//clear buffer
    //sent uniform
    camera->sent_uniform(shader->programID,FBO->aspect());
    lightControl->sent_uniform(shader,camera->pos);
    //start draw

    d_obj->draw(shader);
    if(display_time){
        std::cout<<"range="<<dmap->range<<"drawtime="<<(glfwGetTime()-time)<<std::endl;
        time=glfwGetTime();
    }
}
void Test::prepare_draw_obj(){
	Model* m=Model::load_obj("files/obj/tiger.obj",2.0);
	Model* m2=Model::load_obj("files/obj/cube.obj",40.0);
	Model* m3=Model::load_obj("files/obj/ico.obj",0.05);
	Model* m4=Model::load_obj("files/obj/stars.obj",10000.0);
	Model* m5=Model::load_obj("files/obj/celestialSphere.obj",16000.0);
	Model* m6=Model::load_obj("files/obj/cube.obj",40000.0);
	Model* m7=Model::load_obj("files/obj/base.obj",3.0);
	Model* m8=Model::load_obj("files/obj/celestialSphere.obj",15.0);
	Model* m9=Model::load_obj("files/obj/celestialSphere.obj",6.0);
	m->mat=glm::vec4(0.1,1.0,0.02,0.05);
	m2->mat=glm::vec4(0.1,0.1,0.02,1.0);
	m3->mat=glm::vec4(0.1,0.05,0.02,0.05);
	m4->mat=glm::vec4(0.4,0.05,0.02,1.7);
	m5->mat=glm::vec4(0.0,0.0,0.02,0.1);
	m6->mat=glm::vec4(0.0,0.0,0.02,0.8);
	m8->mat=glm::vec4(0.1,0.1,0.02,0.5);
	m9->mat=glm::vec4(0.1,0.1,0.02,0.5);
	models.push_back(m);
	models.push_back(m2);
	models.push_back(m3);
	models.push_back(m4);
	models.push_back(m5);
	models.push_back(m6);
	models.push_back(m7);
	models.push_back(m8);
	models.push_back(m9);
    b_objs.push_back(new BufferObject(m,false));
    b_objs.push_back(new BufferObject(m2,false));
    b_objs.push_back(new BufferObject(m3,false));
    b_objs.push_back(new BufferObject(m4,false));
    b_objs.push_back(new BufferObject(m5,false));
    b_objs.push_back(new BufferObject(m6,false));
    b_objs.push_back(new BufferObject(m7,false));
    b_objs.push_back(new BufferObject(m8,false));
    b_objs.push_back(new BufferObject(m9,false));

    tiger=new DrawObject(b_objs.at(0),texmap->get_tex(std::string("test")));
    //,texmap->get_tex(std::string("NormalTexture"))

    d_obj->push(tiger);
    sun=new DrawObject(b_objs.at(1),texmap->get_tex(std::string("test2")),
    		texmap->get_tex(std::string("NormalTexture")));
    sun->draw_shadow=false;
    d_obj->push(sun);
    look_at=new DrawObject(b_objs.at(2),texmap->get_tex(std::string("test3")),
    		texmap->get_tex(std::string("NormalTexture6")));
    look_at->draw_shadow=false;
    d_obj->push(look_at);
    stars=new DrawObject(b_objs.at(3),texmap->get_tex(std::string("test3")),
    		texmap->get_tex(std::string("NormalTexture")));
    stars->draw_shadow=false;
    d_obj->push(stars);
    galaxy=new DrawObject(b_objs.at(4),texmap->get_tex(std::string("galaxy")),
    		texmap->get_tex(std::string("NormalTexture")));
    d_obj->push(galaxy);
    DrawObject* doge=new DrawObject(b_objs.at(5),texmap->get_tex(std::string("doge")),
    		texmap->get_tex(std::string("NormalTexture")));
    doge->draw_shadow=false;
    d_obj->push(doge);
    doge->push_position(new Position(glm::vec3(0,0,0),glm::vec3()));
    base=new DrawObject(b_objs.at(6),texmap->get_tex(std::string("test2")),
    		texmap->get_tex(std::string("NormalTexture")));
    d_obj->push(base);
    base->push_position(new Position(glm::vec3(54.0,21.75,26.0),glm::vec3(0,0,0)));
    ico=new DrawObject(b_objs.at(2),texmap->get_tex(std::string("test3")),
    		texmap->get_tex(std::string("NormalTexture6")));
    d_obj->push(ico);
    moon=new DrawObject(b_objs.at(8),texmap->get_tex(std::string("doge")));
    d_obj->push(moon);
}
void Test::creat_shader(){
	shaderBasic=new Shader("Basic");
	shaderBasic->LoadShader("files/shader/basic/Basic.vert",
			"files/shader/basic/Basic.geo",
			"files/shader/basic/Basic.frag");
	shaders.push_back(shaderBasic);

	shaderNormalMapping=new Shader("NormalMapping");
	shaderNormalMapping->LoadShader("files/shader/normalMapping/NormalMapping.vert",
			"files/shader/normalMapping/NormalMapping.geo",
			"files/shader/normalMapping/NormalMapping.frag");
	shaders.push_back(shaderNormalMapping);

	shaderLightScatter=new Shader("LightScatter");
	shaderLightScatter->LoadShader("files/shader/lightScatter/LightScatter.vert",
			"files/shader/lightScatter/LightScatter.geo",
			"files/shader/lightScatter/LightScatter.frag");
	shaders.push_back(shaderLightScatter);

	shader2D=new Shader2D();
	shader2D->LoadShader("files/shader/2D/2D.vert","files/shader/2D/2D.frag");
	shaders.push_back(shader2D);

	shaderTest=new Shader();
	shaderTest->LoadShader("files/shader/test/test.vert",
			"files/shader/test/test.geo",
			"files/shader/test/test.frag");
	shaders.push_back(shaderTest);

	cur_shader=shaderNormalMapping;
}
void Test::creat_light(){
	camlight=new PointLight(glm::vec3(5.1,2.6,0.1),glm::vec3(3.2,3.2,3.2),true);
	lightControl->push_point_light(camlight);

	s_light=new ParallelLight(glm::vec3(-300,0,-500),sun_col1,true);

	//lightControl->push_parallel_light(new ParallelLight(glm::vec3(1.0,-1.2,0.2),glm::vec3(0.2,0.2,0.2),true));
	lightControl->push_parallel_light(s_light);

}
void Test::draw(double &time){
	//renderer->render_all();
    ///*
	//Renderer::enable_thread_render();
	//render_task=new RenderTask(renderer,window);
	render_thread->push_task(render_task);
	render_thread->start();

	//*/
	/*

	FrameBuffer::unbind_buffer(window->get_size());
	if(to_sobel){
		Image<unsigned char>*img=FBO->color_textures.at(1)->Tex2D()->convert_to_image();
		Image<unsigned char>::convert_to_sobel(img,glm::vec2(20.0,10.0),0.9);
		Texture* tmp_tex=Texture2D::gen_texture2D(img,GL_RGB);
		FBO->color_textures.at(0)->draw_texture(shader2D,window->aspect(),window->aspect(),1.0);
		tmp_tex->draw_texture(shader2D,window->aspect(),window->aspect(),0.2);
		delete img;
		delete tmp_tex;
	}else{
		FBO->color_textures.at(0)->draw_texture(shader2D,window->aspect(),window->aspect(),1.0);
	}
    glEnable(GL_BLEND);
    //do blend draw
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);
	*/
}
void Test::timer_tic(double &time){
	//=======================logical operation and input part==========================
    if(!stop_the_sun){
        if(timeloop<loop_time)timeloop++;
        else timeloop=0;
    }

    mouse->tic();//clear mouse delta pos before update
    keyboard->tic();
    glfwPollEvents();//get all input
    //=======================render data update==========================
    input();
    camera->tic();

    update_map(camera);
    std::cout<<"draw start"<<std::endl;
    //========================render thread start========================
    draw(time);
    //========================wait for rendering end=====================
    std::cout<<"draw end"<<std::endl;
    //render_thread->wait_for_this();
    int i=0,j=0;
	while(!render_thread->DONE()){//renderer->Rendering();!render_task->Done()
		//std::cout<<"wait!!"<<std::endl;
		if(i<10000)i++;
		else{
			i=0;j++;
		}
		if(j>10000){
			std::cerr<<"render time out!!"<<std::endl;
			break;
		}
	}
	std::cout<<"render end"<<std::endl;
	//render_thread->wait_for_this();
	//delete render_task;
	//renderer->disable_thread_render();
	d_obj->clear_tmp_pos();
	//===================================================================

    //std::cout<<"d_objs size="<<d_obj->obj_size()<<std::endl;
    //window->swap_buffer();
}
void Test::Mainloop(){
    double time=0;
    //void (Test::*ptr)(double&)=&Test::timer_tic;
    /*
    Model* m=Model::load_obj("files/obj/tiger.obj",2.0);

	for(int i=0;i<100;i++){
		BufferObject *test=new BufferObject(m);
		delete test;
	}
	*/
    //window->render_off();
    while(!window->WindowShouldClose()&&!end){
    	timer_tic(time);
    }
    window->render_on();
    terminate();


}
