#include "tw_result.h"

#include <ijengine/canvas.h>
#include <ijengine/engine.h>
#include <ijengine/keyboard_event.h>

#include <unistd.h>

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace ijengine;

TWResult::TWResult(const string &current_level, const string& next_level, const string audio_path, int){
	m_current_level = current_level;
	m_audio = audio_path;
	m_next = next_level;
	m_done = false;
	m_state = NOTHING;
	m_start = -1;

	FILE *result = fopen("result.dat", "rb");
	int v[2];

	if(not result){
		printf("Não foi possível abrir o arquivo result.dat\n");
		exit(1);
	}

	fread(&v[0], sizeof(int), 2, result);

	n_collectables = v[0];
	n_defeated_enemies = v[1];

	system("rm result.dat");

	//Isso precisa ser pego do arquivo geral de salvamento
	double max_col = 500;
	double percentage_col = (100.0 * v[0])/max_col;

	if(percentage_col >= MINIMUM_PERCENTAGE){
		final_texture = resources::get_texture(m_current_level + "/ganhou.png");
	}else{
		final_texture = resources::get_texture(m_current_level + "/perdeu.png");
	}

	
    numbers = resources::get_texture("numbers.png");

	m_buttons.push_back(new TWButton(0, m_current_level, 700, 410, "limbo-botao.png", 142, 50, 1));

	for(auto btn : m_buttons){
		add_child(btn);
	}

	event::register_listener(this);
}

TWResult::~TWResult(){
	event::unregister_listener(this);
}

bool TWResult::done() const{
	return m_done;
}

string TWResult::next() const{
	return m_next;
}

string TWResult::audio() const{
	return m_audio;
}

bool TWResult::on_event(const GameEvent& event){
	if(event.id() == GAME_MOUSE_CLICK){
		double mouse_x = event.get_property<double>("x");
		double mouse_y = event.get_property<double>("y");

		for(auto btn : m_buttons){
			if(btn->able_to_draw() == 0) continue;

			int min_x = btn->x(), max_x = min_x + btn->w();
			int min_y = btn->y(), max_y = min_y + btn->h();

			if(mouse_x >= min_x && mouse_x <= max_x && mouse_y >= min_y && mouse_y <= max_y){
				switch(btn->id()){
					case 0:
						m_done = true;
						break;
					default:
						break;
				}

				return true;
			}
		}
	}

	return false;
}

void TWResult::update_self(unsigned, unsigned){
	if(m_state == SELECTING){
		m_state = RUNNING;
		m_done = true;
	}
}

void TWResult::draw_self(Canvas *canvas, unsigned, unsigned){
	canvas->clear();
	
	canvas->draw(final_texture.get(), Rectangle(0, 0, 852, 480), 0, 0);

	int x_digit_col = 260;
	int counter_col = n_collectables;

	do{
		canvas->draw(numbers.get(), Rectangle(23 * (counter_col % 10), 0, 23, 36), x_digit_col, 17);
		counter_col /= 10;
		x_digit_col -= 25;
	}while(counter_col);


	int x_digit_enemie = 747;
	int counter_enemies = n_defeated_enemies;

	do{
		canvas->draw(numbers.get(), Rectangle(23 * (counter_enemies % 10), 0, 23, 36), x_digit_enemie, 17);
		counter_enemies /= 10;
		x_digit_enemie -= 25;
	}while(counter_enemies);

}
