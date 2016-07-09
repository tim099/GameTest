/*
 * Age Of Cube version -1.0
 * Copyright (C) 2016, Tim Yeh<tim11251994@gmail.com>
 *
 * This program is free software;
 * you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation;
 */
#ifndef SOURCE_CLASS_GAME_GAME_H_
#define SOURCE_CLASS_GAME_GAME_H_
#include "class/game/scene/Scene.h"

#include "class/display/window/Window.h"
#include "class/display/draw/Draw.h"
#include "class/display/render/Renderer.h"
#include "class/display/UI/UIObjectCreator.h"
#include "class/game/scene/LoadingScene.h"
#include "class/input/Input.h"
#include "class/controller/ControllerSystem.h"

#include "class/tim/thread/ThreadPool.h"

#include "class/game/SceneInitTask.h"
#include "class/tim/math/vec2.h"

#include "class/game/Config.h"
#include <vector>

class Game {
	friend SceneInitTask;
public:
	Game();
	virtual ~Game();
	virtual void mainloop();
	void initialize();
	void terminate();
	bool restart;
protected:
	void init();
	virtual void update();
	virtual void initialize_game()=0;
	virtual void terminate_game()=0;
	virtual void game_update()=0;
	virtual std::string window_name(){
		return std::string("default window name");
	}
	virtual Display::Window* create_window();

	virtual Tim::ThreadPool* create_thread_pool();

	Scene* get_cur_scene();

	void handle_game_signal();
	void swap_buffer();
	void push_scene(Scene* scene);
	void scene_loading(Scene* scene);
	void pop_scene();
	game::Config config;

	std::vector<Scene*>scenes;
	Display::Window* window;
	Display::Draw *draw;
	Display::Renderer *renderer;

	Input::Receiver* game_receiver;
	Tim::ThreadPool *thread_pool;

	Input::Input* input;
	ControllerSystem *controller_system;
	UI::UIObjectCreator *UIObj_Creator;

	LoadingScene* s_loading;

	std::string folder_path;

	bool loading;
	bool end,terminated;
	double fps,max_fps;
	double frame_start_time;
};

#endif /* SOURCE_CLASS_GAME_GAME_H_ */
