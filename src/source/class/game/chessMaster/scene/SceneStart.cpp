#include "class/game/chessMaster/scene/SceneStart.h"
#include "class/game/chessMaster/common.h"
#include "class/display/light/LightControl.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/tim/math/Position.h"
#include "class/tim/string/String.h"
#include <stdlib.h>
#include <time.h>
namespace CM {
namespace scene{
SceneStart::SceneStart() {
	UI = 0;
	local_path = std::string("scene/start/");
	chess_board = 0;
	camera = 0;
	p1camera = 0,p2camera = 0;;
	lightControl = 0;
	destruct_mode=false;
	type=1;
	sx=0,sy=0,selected=false;
	prev_sx=0;prev_sy=0;
	turn=-1;
	total_compute=0;
	do_pruning=true;
	difficulty=3;
	edit_mode=false;
}
SceneStart::~SceneStart() {

}
void SceneStart::scene_initialize() {
	//draw->Enable3D=false;
	int sizex=8,sizey=3,sizez=8;
	chess_board=new ChessBoard(sizex,sizey,sizez);
	//chess_board->load_board(CM::folder_path+"game/chess/chessBoard/board");
	chess_board->load_script(CM::folder_path+"game/chess/chessBoard/boardscript.txt");

	glm::vec3 pos=glm::vec3(0.5*chess_board->cube_size*sizex,6,-3);
	p1camera = new Camera(pos,
			pos+glm::vec3(0,-4,0.5f*sizez),
			glm::vec3(0, 1, 0), 60.0, 0.1f,
			10000.0f);
	glm::vec3 pos2=glm::vec3(0.5*chess_board->cube_size*sizex,6,10);
	p2camera = new Camera(pos2,
			pos2+glm::vec3(0,-4,-0.5f*sizez),
			glm::vec3(0, 1, 0), 60.0, 0.1f,
			10000.0f);
	camera=p2camera;
	draw->set_camera(camera);

	lightControl = new LightControl(120);
	lightControl->shadow_dis=3.0f;
	lightControl->push_light(
			new ParallelLight(glm::vec3(1.0, -1.2, 0.2),
					glm::vec3(0.6, 0.6, 0.6), false));
	lightControl->push_light(
			new ParallelLight(glm::vec3(-0.5, -0.5, 2.1),
					glm::vec3(1.1, 1.1, 1.1), true));
	lightControl->push_light(
			new ParallelLight(glm::vec3(-0.2, -1.2, -1.1),
					glm::vec3(0.9, 0.9, 0.9), true));
	lightControl->push_light(
			new ParallelLight(glm::vec3(0.5, -0.4, -0.7),
					glm::vec3(0.4, 0.4, 0.4), false));
	draw->Enable3D = true;

	draw->set_lightControl(lightControl);
	UI = new UI::UI(CM::folder_path+local_path+"UI/startUI.txt");
	UI->Enable_Mode(UI::Mode::EDIT);
}
void SceneStart::scene_terminate() {

	delete chess_board;
	delete p1camera;
	delete p2camera;
	delete lightControl;
	delete UI;
}
void SceneStart::pause(){

}
void SceneStart::resume(){

}
void SceneStart::handle_signal(Signal *sig){
	if(sig->get_data()=="normal"){
		difficulty=5;
	}else if(sig->get_data()=="easy"){
		difficulty=3;
	}else if(sig->get_data()=="undo"){
		if(steps.size()>=2){
			chess_board->undo(*steps.back());
			delete steps.back();
			steps.pop_back();
			chess_board->undo(*steps.back());
			delete steps.back();
			steps.pop_back();
		}

	}else if(sig->get_data()=="auto"){
		selected=false;
		AI_move(turn);
	}
	std::cout<<sig->get_data()<<std::endl;
}
void SceneStart::next_turn(CM::Step step){
	turn*=-1;
	if(turn==1){
		camera=p1camera;
		draw->set_camera(camera);
	}else{
		camera=p2camera;
		draw->set_camera(camera);
	}
	steps.push_back(new CM::Step(&step));
	chess_board->move(*steps.back());
}
void SceneStart::camera_control(){
	if(input->keyboard->pressed('R')){
		camera->v.y += 0.01f* sqrt(camera->look_dis() + 0.001);
	}
	if(input->keyboard->pressed('F')){
		camera->v.y -= 0.01f* sqrt(camera->look_dis() + 0.001);
	}
	if(input->keyboard->get('V')){
		destruct_mode^=1;
	}
	if (input->mouse->mid_pressed()||input->keyboard->pressed('Z')) {
		//std::cout<<"move"<<(int)(mouse->pos.x)<<","<<(int)mouse->prev_pos.x<<std::endl;
		camera->rotate(glm::vec3(0, 1, 0), -0.15 * input->mouse->pos_delta().x);
		camera->rotate(camera->yaw_vec(), 0.15 * input->mouse->pos_delta().y);
	}
	//camera->rotate(glm::vec3(0, 1, 0), 1.0f);
	if(input->mouse->screen_pos.y>0.95){
		camera->v += (float) (-0.02f * sqrt(camera->look_dis() + 0.001))
				* camera->look_vec_xz();
	}
	if(input->mouse->screen_pos.y<-0.95){
		camera->v += (float) (0.02f * sqrt(camera->look_dis() + 0.001))
				* camera->look_vec_xz();
	}
	if(input->mouse->screen_pos.x>0.95){
		camera->v += (float) (-0.02f * sqrt(camera->look_dis() + 0.001))
		* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if(input->mouse->screen_pos.x<-0.95){
		camera->v += (float) (0.02f * sqrt(camera->look_dis() + 0.001))
		* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if (input->mouse->right_pressed()) {
		camera->v += (float) (0.001f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().y) * camera->look_vec_xz();
		camera->v += (float) (-0.001f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().x)
				* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}

	///*


	//*/
	if (input->mouse->scroll) {
		camera->dis_alter_v += sqrt(camera->look_dis() + 0.1)
				* (0.05 * input->mouse->scroll);
	}
	if(camera->look_at.x>chess_board->cube_size*chess_board->board->sizex){
		if(camera->v.x>0.0f){
			camera->v.x*=-0.9f;
		}
	}else if(camera->look_at.x<0.0f){
		if(camera->v.x<0.0f){
			camera->v.x*=-0.9f;
		}
	}
	if(camera->look_at.z>chess_board->cube_size*chess_board->board->sizez){
		if(camera->v.z>0.0f){
			camera->v.z*=-0.9f;
		}
	}else if(camera->look_at.z<0.0f){
		if(camera->v.z<0.0f){
			camera->v.z*=-0.9f;
		}
	}
}
CM::Step SceneStart::best_step(int player,int depth,int pruning){
	CM::Step cur;
	CM::Step best;
	std::vector<CM::Step>bests;
	best.score=-999999*player;
	int type;
	std::vector<glm::ivec2> next_step;
	for(int i=0;i<chess_board->chess_board->sizex;i++){
		for(int j=0;j<chess_board->chess_board->sizey;j++){
			type=chess_board->get_type(i,j);
			if(type*player>0){//player's chess
				cur.x=i;
				cur.y=j;
				chess_board->find_next_step(glm::ivec2(cur.x,cur.y),next_step);
				for(unsigned i=0;i<next_step.size();i++){
					cur.nx=next_step.at(i).x;
					cur.ny=next_step.at(i).y;
					chess_board->move(cur);
					if(depth<=1){
						total_compute++;
						cur.score=chess_board->evaluate_score(chess_board->chess_board,1);
					}else{
						cur.score=best_step(-player,depth-1,best.score).score;
					}
					if(player*cur.score>=player*best.score){
						if(player*cur.score==player*best.score){
							bests.push_back(cur);
						}
						best=cur;
						if(do_pruning&&player*pruning<player*best.score){
							//std::cout<<"pruning"<<std::endl;
							chess_board->undo(cur);
							return best;
						}
						//std::cout<<"best score="<<best.score<<std::endl;
					}
					chess_board->undo(cur);
				}
			}
		}
	}
	///*
	if(bests.size()>1){
		srand(time(NULL));
		std::vector<CM::Step>bests2;
		for(unsigned i=0;i<bests.size();i++){
			if(bests.at(i).score==best.score){
				bests2.push_back(bests.at(i));
			}
		}
		if(bests2.size()>2){
			int at=(rand()%bests2.size());
			best=bests2.at(at);
		}
	}
	//*/
	return best;
}
void SceneStart::AI_move(int player){
	selected=false;
	total_compute=0;
	do_pruning=true;
	CM::Step best=best_step(player,difficulty,player*999999);
	std::cout<<"total compute pruning="<<total_compute<<std::endl;
	/*
	total_compute=0;
	do_pruning=false;
	best=best_step(player,5,player*999999);
	std::cout<<"total compute="<<total_compute<<std::endl;
	*/
	//std::cout<<"find best step="<<best.x<<","<<best.y<<"to"<<best.nx<<","<<best.ny<<std::endl;
	//std::cout<<"find best score="<<player*best.score<<std::endl;
	next_turn(best);

}
void SceneStart::handle_input(){
	if(edit_mode){
		if (input->mouse->left_clicked()) {
			if(!destruct_mode){
				//chess_board->set_type(chess_board->selected_on.x,
									//chess_board->selected_on.y,
									//chess_board->selected_on.z,type);

				chess_board->set_type(chess_board->selected_on.x,
						chess_board->selected_on.z,type);
			}else{
				//chess_board->set_type(chess_board->selected_cube.x,
									//chess_board->selected_cube.y,
									//chess_board->selected_cube.z,0);
				chess_board->set_type(chess_board->selected_on.x,
						chess_board->selected_on.z,-type);
			}

		}
	}else{
		if(input->mouse->left_clicked()){
			prev_sx=sx;
			prev_sy=sy;
			sx=chess_board->selected_piece.x;
			sy=chess_board->selected_piece.y;

			if(selected){
				for(unsigned i=0;i<next_step.size();i++){
					if(sx==next_step.at(i).x&&
					   sy==next_step.at(i).y){
						selected=false;
						next_turn(CM::Step(prev_sx,prev_sy,sx,sy));
						break;
					}
				}
			}
			if(sx>=0&&sy>=0&&sx<chess_board->chess_board->sizex&&
					sy<chess_board->chess_board->sizey){
				int type=chess_board->chess_board->get(sx,sy);
				if(type*turn>0){
					chess_board->find_next_step(glm::ivec2(sx,sy),next_step);
					selected=true;
				}else{
					selected=false;
				}
			}
		}
	}
	if(input->keyboard->get('E')){
		edit_mode^=1;
	}
	if(input->keyboard->get('S')){
		chess_board->save_board(CM::folder_path+"game/chess/chessBoard/board.txt");
	}
	if(input->keyboard->get('L')){
		chess_board->load_board(CM::folder_path+"game/chess/chessBoard/board.txt");
	}
	if(input->keyboard->get('Q')&&type<11){
		type++;
	}
	if(input->keyboard->get('E')&&type>0){
		type--;
	}
	camera_control();
}
void SceneStart::scene_update(){

	handle_input();
	camera->update();
	UI->update_UIObject();
	chess_board->find_select_cube();
	if(turn==1){
		AI_move(turn);
	}
}
void SceneStart::scene_draw(){
	if(turn==1){
		draw->push(new RenderString("Black's turn",0.02,glm::vec2(0,0.95)));
	}else{
		draw->push(new RenderString("White's turn",0.02,glm::vec2(0,0.95)));
	}
	if(difficulty==3){
		draw->push(new RenderString("Easy AI",0.02,glm::vec2(0.4,0.95)));
	}else{
		draw->push(new RenderString("Normal AI",0.02,glm::vec2(0.4,0.95)));
	}
	int score=chess_board->evaluate_score(chess_board->chess_board,turn);
	draw->push(new RenderString("score:"+Tim::String::to_string(score),0.02,glm::vec2(0,0.85)));
	if(score<-99999){
		if(turn==-1)draw->push(new RenderString("Black win!!",0.05,glm::vec2(0.3,0.5)));
		else draw->push(new RenderString("White win!!",0.05,glm::vec2(0.3,0.5)));
	}
	CubeLight* cl=new CubeLight();
	cl->size=1.01f*chess_board->cube_size;
	lightControl->push_temp_light(cl);
	if(destruct_mode){
		cl->color=glm::vec3(1,0,0);
		cl->pos=glm::vec3((chess_board->selected_cube.x+0.5f)*chess_board->cube_size,
						  (chess_board->selected_cube.y+0.5f)*chess_board->cube_size,
						  (chess_board->selected_cube.z+0.5f)*chess_board->cube_size);
	}else{
		cl->color=glm::vec3(0,1,0);
		cl->pos=glm::vec3((chess_board->selected_on.x+0.5f)*chess_board->cube_size,
				  (chess_board->selected_on.y+0.5f)*chess_board->cube_size,
				  (chess_board->selected_on.z+0.5f)*chess_board->cube_size);
	}

	UI->draw_UIObject(draw);
	chess_board->draw();
	static Position pos=Position(glm::vec3(), glm::vec3());
	pos.set_pos(glm::vec3((chess_board->selected_on.x+0.5f)*chess_board->cube_size,
			  (chess_board->selected_on.y+0.5f)*chess_board->cube_size,
			  (chess_board->selected_on.z+0.5f)*chess_board->cube_size));

	//chess_board->pieces.at(type-1)->draw(&pos,!destruct_mode);
	if(!steps.empty()){
		cl=new CubeLight();
		cl->size=1.01f*chess_board->cube_size;
		lightControl->push_temp_light(cl);
		cl->color=glm::vec3(0.5,0.5,0.5);
		cl->pos=glm::vec3((steps.back()->nx+0.5f)*chess_board->cube_size,
						  (2.5f)*chess_board->cube_size,
						  (steps.back()->ny+0.5f)*chess_board->cube_size);
		cl=new CubeLight();
		cl->size=1.01f*chess_board->cube_size;
		lightControl->push_temp_light(cl);
		cl->color=glm::vec3(0.5,0.5,0.5);
		cl->pos=glm::vec3((steps.back()->x+0.5f)*chess_board->cube_size,
						  (2.5f)*chess_board->cube_size,
						  (steps.back()->y+0.5f)*chess_board->cube_size);
	}


	if(selected){
		draw_step();
	}
}
void SceneStart::draw_step(){
	//std::cout<<"selected="<<sx<<","<<sy<<std::endl;

	CubeLight* cl;
	cl=new CubeLight();
	cl->size=1.01f*chess_board->cube_size;
	lightControl->push_temp_light(cl);
	cl->color=glm::vec3(0.5,0.5,0.5);
	cl->pos=glm::vec3((sx+0.5f)*chess_board->cube_size,
					  (2.5f)*chess_board->cube_size,
					  (sy+0.5f)*chess_board->cube_size);
	for(unsigned i=0;i<next_step.size();i++){
		cl=new CubeLight();
		cl->size=1.01f*chess_board->cube_size;
		lightControl->push_temp_light(cl);
		int type2=chess_board->get_type(next_step.at(i).x,next_step.at(i).y);
		if(chess_board->chess_board->get(sx,sy)*type2<0){
			cl->color=glm::vec3(0.5,0,0);
		}else{
			cl->color=glm::vec3(0,0.5,0);
		}

		cl->pos=glm::vec3((next_step.at(i).x+0.5f)*chess_board->cube_size,
						  (2.5f)*chess_board->cube_size,
						  (next_step.at(i).y+0.5f)*chess_board->cube_size);



	}
}


}
} /* namespace CM */
