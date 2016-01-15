#include "class/test/Test.h"
#include "class/display/texture/texture3D/Texture2DArr/Texture2DArr.h"
#include "class/display/texture/texture2D/Texture2D.h"
#include "class/display/draw/texture/DrawTexture.h"
#include "class/display/texture/drawData/drawDataEX/SobelData.h"
#include "class/display/texture/drawData/drawDataEX/ColorAlter.h"
#include "class/test/TestTask.h"
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <windows.h>
//#include <wglew.h>
//#include <chrono>
Test::Test() {
	sun_col1=glm::vec3(2.2,2.3,2.5);
	sun_col2=glm::vec3(1.2,0.9,0.5);
	timeloop=0;
	loop_time=10000;
	shadow_dis=1.0;
	start_time=0.0;

	end=false;
	stop=false;
	display_time=false;
	shader_at=0;

	position_pool=new Tim::ObjPool<Position>(100);

	map=new Map();
	//window=new Window(glm::ivec2(1366,733),"Age of Cube",false);//must before any draw obj
	window=new Window(glm::ivec2(1920,1080),"Age of Cube",true);//must before any draw obj
	d_obj=new Draw();
	texmap=new TextureMap(std::string("files/script/loadTexture/loadTestTexture.txt"));
	dmap=new DisplayMap(map,d_obj,texmap,window);
	//window=new Window(glm::ivec2(1920,1080),"hello tim",true);

	lightControl=new LightControl(120);


	input=new Input(window->get_window());
	camera=new Camera(glm::vec3(36.0,24.0,24.0),glm::vec3(34.0,22.0,27.0),
			glm::vec3(0,1,0),60.0,0.1f,50000.0f);

	VertexArrayID=Buffer::GenVertexArray();

    map->load_map("files/maps/map011");

    creat_light();//
    prepare_draw_obj();

    render_thread=new Tim::Thread(REALTIME_PRIORITY_CLASS);
    renderer=new Renderer(lightControl,d_obj,window,camera,input->mouse,texmap,&shadow_dis);
    thread_pool=new Tim::ThreadPool(8);
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
	delete input;

	delete camera;
	delete render_task;
	thread_pool->Terminate();
	render_thread->Terminate();

	for(unsigned i=0;i<b_objs.size();i++){
		delete b_objs.at(i);
	}
	delete d_obj;
	delete map;
	delete window;

	delete position_pool;
	glfwTerminate();
}
void Test::handle_input(){
	if(input->mouse->mid){
		//std::cout<<"move"<<(int)(mouse->pos.x)<<","<<(int)mouse->prev_pos.x<<std::endl;
		camera->rotate(glm::vec3(0,1,0),-0.15*input->mouse->pos_delta().x);
		camera->rotate(camera->yaw_vec(),0.15*input->mouse->pos_delta().y);
	}
	if(input->keyboard->pressed('Q')){
		ico->push_position(new Position(input->mouse->world_pos,glm::vec3()));
	}
	if(input->keyboard->get('E')){
		camlight->shadow^=1;
	}
	if(input->keyboard->get(256)){//ESC
		std::cout<<"END"<<std::endl;
		end=true;
	}
	if(input->mouse->right){
		camera->v+=(float)(0.001f*sqrt(camera->look_dis()+0.001)*input->mouse->pos_delta().y)*camera->look_vec_xz();
		camera->v+=(float)(-0.001f*sqrt(camera->look_dis()+0.001)*input->mouse->pos_delta().x)*
				glm::cross(camera->look_vec_xz(),glm::vec3(0,1,0));
	}
	if(input->mouse->left){
		camera->v+=(float)(-0.0005f*sqrt(camera->look_dis()+0.001)*input->mouse->pos_delta().y)*glm::vec3(0,1,0);
		camera->v+=(float)(-0.001f*sqrt(camera->look_dis()+0.001)*input->mouse->pos_delta().x)*
				glm::cross(camera->look_vec_xz(),glm::vec3(0,1,0));
	}
	if(input->mouse->scroll){
		camera->dis_alter_v+=sqrt(camera->look_dis()+0.1)*(0.05*input->mouse->scroll);
	}
	if(input->keyboard->pressed('M')){
		timeloop++;
		if(timeloop>=loop_time)timeloop=0;
		//sunlight->pos=glm::vec3(glm::rotate(0.5f,glm::vec3(-1,0,1))*glm::vec4(sunlight->pos,1));
	}
	if(input->keyboard->pressed('J')){
		timeloop--;
		if(timeloop<0)timeloop=loop_time-1;
		//sunlight->pos=glm::vec3(glm::rotate(-0.5f,glm::vec3(-1,0,1))*glm::vec4(sunlight->pos,1));
	}
	if(input->keyboard->get('H')){
		loop_time*=1.05;
		timeloop*=1.05;
	}
	if(input->keyboard->get('Y')){
		loop_time*=0.95;
		timeloop*=0.95;
		if(loop_time<10)loop_time=10;
	}
	if(input->keyboard->get('N')){
		stop^=1;
	}
	if(input->keyboard->pressed('B')){
		glm::ivec3 pos=Map::convert_position(camera->look_at);
		if(!map->get(pos.x,pos.y,pos.z)){
			if(map->set(pos.x,pos.y,pos.z,1)){
				dmap->update_map(pos);
			}
		}
	}
	if(input->keyboard->pressed('V')){
		glm::ivec3 pos=Map::convert_position(camera->look_at);
		if(map->get(pos.x,pos.y,pos.z)){
			if(map->set(pos.x,pos.y,pos.z,0)){
				dmap->update_map(pos);
			}
		}
	}
	if(input->keyboard->get('O')){
		renderer->switch_shader("Basic");
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	if(input->keyboard->get('P')){
		renderer->switch_shader("NormalMapping");
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	if(input->keyboard->get('L')){
		renderer->switch_shader("LightScatter");
	}
	if(input->keyboard->get(GLFW_KEY_LEFT)){

	}
	if(input->keyboard->get(GLFW_KEY_RIGHT)){

	}
	if(input->keyboard->pressed(GLFW_KEY_UP)){
		if(shadow_dis>0.01)shadow_dis*=0.98;
	}
	if(input->keyboard->pressed(GLFW_KEY_DOWN)){
		if(shadow_dis<30.0)shadow_dis*=1.01;
	}
	if(input->keyboard->get('C')){
		look_at->push_position(new Position(camera->look_at+glm::vec3(0,0.1,0),
				glm::vec3(0,camera->look_ry(),0)));
		lightControl->push_point_light(new PointLight(camera->look_at,camlight->color,
				camlight->shadow));
	}
	if(input->keyboard->get('1')){
		camlight->color+=glm::vec3(0.3,0.0,0.0);
	}
	if(input->keyboard->get('2')){
		camlight->color+=glm::vec3(-0.3,0.0,0.0);
	}
	if(input->keyboard->get('3')){
		camlight->color+=glm::vec3(0.0,0.3,0.0);
	}
	if(input->keyboard->get('4')){
		camlight->color+=glm::vec3(0.0,-0.3,0.0);
	}
	if(input->keyboard->get('5')){
		camlight->color+=glm::vec3(0.0,0.0,0.3);
	}
	if(input->keyboard->get('6')){
		camlight->color+=glm::vec3(0.0,0.0,-0.3);
	}
	if(input->keyboard->pressed('7')){
		camlight->color+=glm::vec3(0.05,0.05,0.05);
	}
	if(input->keyboard->get('8')){
		camlight->color+=glm::vec3(-0.05,-0.05,-0.05);
	}
	if(input->keyboard->get('9')){
		camlight->color=glm::vec3(0.05,0.05,0.05);
	}
	if(input->keyboard->get('0')){
		camlight->color=glm::vec3(((rand()%10000)/4000.0),((rand()%10000)/4000.0),((rand()%10000)/4000.0));
	}
	if(input->keyboard->get('I')){
		dmap->range+=10;
	}
	if(input->keyboard->get('K')){
		if(dmap->range>10)dmap->range-=10;
		else dmap->range=0;
	}

	if(input->keyboard->pressed('T')){
		camera->rotate(camera->yaw_vec(),1);
	}
	if(input->keyboard->pressed('G')){
		camera->rotate(camera->yaw_vec(),-1);
	}
	if(input->keyboard->pressed('Z')){
		camera->move(glm::vec3(0,0.03,0));
	}
	if(input->keyboard->pressed('X')){
		camera->move(glm::vec3(0,-0.03,0));
	}
	if(input->keyboard->pressed('W')){
		dmap->max_y_alter(1,thread_pool);
	}
	if(input->keyboard->pressed('S')){
		dmap->max_y_alter(-1,thread_pool);
	}
	if(input->keyboard->pressed('A')){
		//renderer->set_window(window2);
		camera->move_side(0.04f);
	}
	if(input->keyboard->pressed('D')){
		//renderer->set_window(window);
		camera->move_side(-0.04f);
	}
	if(input->keyboard->pressed('R')){
		camera->dis_alter(-0.05);
	}
	if(input->keyboard->pressed('F')){
		camera->dis_alter(0.05);
	}
}
void Test::set_obj_pos(Camera *camera){
	static Position starpos(glm::vec3(0,0,0),glm::vec3());
	static Position sunpos(glm::vec3(5.1,80.6,0.1),glm::vec3());
    //obj move
    starpos.r.y=360.0f*((float)timeloop/loop_time);
    glm::vec3 sun_pos=glm::vec3(glm::rotate(360.0f*((float)timeloop/loop_time),glm::vec3(-1,0,1))
    *glm::vec4(glm::vec3(300,0,500),1));
    s_light->vec=-sun_pos;

    s_light->color=(1.0f-((float)timeloop/loop_time))*sun_col1+((float)timeloop/loop_time)*sun_col2;

    sunpos.pos=sun_pos;

    sun->push_temp_position(new Position(sunpos));

    tiger->push_temp_position(new Position(glm::vec3(33.0,21.47,26.0),
    		glm::vec3(0,360.0f*((float)timeloop/loop_time),0)));

    look_at->push_temp_position(new Position(camera->look_at,glm::vec3(0,camera->look_ry(),0)));

    stars->push_temp_position(new Position(starpos));

    galaxy->push_temp_position(new Position(starpos));

}
void Test::update_map(Camera *camera){
	dmap->draw_map(camera);//push position
    camlight->pos=camera->look_at;
    set_obj_pos(camera);
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
	m2->mat=glm::vec4(0.1,0.1,0.02,1.0);//x=diffuse,y=specular_value,z=ambient,w=emissive
	//m3->mat=glm::vec4(0.1,0.05,0.02,0.05);
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
void Test::creat_light(){
	camlight=new PointLight(glm::vec3(5.1,2.6,0.1),glm::vec3(3.2,3.2,3.2),true);
	lightControl->push_point_light(camlight);

	s_light=new ParallelLight(glm::vec3(-300,0,-500),sun_col1,true);

	//lightControl->push_parallel_light(new ParallelLight(glm::vec3(1.0,-1.2,0.2),glm::vec3(0.2,0.2,0.2),true));
	lightControl->push_parallel_light(s_light);
}
void Test::draw(){
	render_thread->push_task(render_task);
	render_thread->start();
}
void Test::timer_tic(double &time){
	//=======================logical operation and input part==========================
    if(!stop){
        if(timeloop<loop_time)timeloop++;
        else timeloop=0;
    }

    input->update(window->get_size());//world space pos update by renderer


    //=======================render data update=======================================
    glm::vec2 pos=Tim::Math::convert_to_texcoord(input->mouse->screen_pos);

    //std::cout<<"pos.x="<<pos.x<<"pos.y="<<pos.y<<std::endl;

    DrawData* data=new DrawData2D(window->aspect(),1.0,pos,0.2);
    data->ex_datas.push_back(new SobelData(glm::vec2(20,10)));
    data->ex_datas.push_back(new ColorAlter(glm::vec3(0.3,0,0)));
    d_obj->push(new DrawTexture(texmap->get_tex(std::string("doge")),data));//texmap->get_tex(std::string("test"))

    handle_input();
    map->tic();
    camera->tic();
    update_map(camera);

    //std::cout<<"draw start"<<std::endl;
    //thread_pool->push_task(new TestTask());
    //thread_pool->push_task(new TestTask());
    //========================render thread start========================
    draw();
    //========================wait for rendering end=====================
    render_thread->join();
	swap_buffer();
	d_obj->clear_tmp_pos();
	//===================================================================

}
void Test::swap_buffer(){
	while((1.0/(glfwGetTime()-start_time))>60.0);
	std::cout<<"fps="<<(1.0/(glfwGetTime()-start_time))<<std::endl;
	start_time=glfwGetTime();
	window->render_on();
	window->swap_buffer();
	window->render_off();//release thread using this window
}
void Test::Mainloop(){
    double time=0;
    //wglSwapIntervalEXT(1);
    //window->render_off();
    //int i=WAIT_ABANDONED;
    //glfwSwapInterval(60);
    start_time=glfwGetTime();

    while(!window->WindowShouldClose()&&!end){
    	timer_tic(time);
    }
    window->render_on();
    terminate();


}
