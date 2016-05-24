#ifndef TRAVELING_WILL_LEVEL_H
#define TRAVELING_WILL_LEVEL_H

#include <string>
#include <memory>
#include <ijengine/level.h>
#include <ijengine/texture.h>
#include <ijengine/events_translator.h>
#include <ijengine/game_events_listener.h>

#include <vector>

using std::string;
using std::shared_ptr;

using namespace ijengine;

class Button;

class TravelingWillLevel : public Level, public GameEventsListener {
    public:
        TravelingWillLevel(int r, int g, int b, const string& current_level, const string& next_level = "", const string audio_path = "", int audio_duration = -1);
        ~TravelingWillLevel();

        bool done() const;
        string next() const;
        string audio() const;

        bool on_event(const GameEvent& event);

    protected:
        void update_self(unsigned now, unsigned last);
        void draw_self(Canvas *canvas, unsigned now, unsigned last);

    private:
        typedef enum { RUNNING, JUMPING, SLIDING, SELECTING, NOTHING, FALLING, GAME_OVER } State;
        int m_r, m_g, m_b;
        bool m_done;
        int collectable_it;
        string m_next;
        int m_start, current_image, change, n_screens, n_collectables;
        double platform_height[200];
        double collectable_height[200], enemy_height[200];
        int collectable[200], enemy[200];
        int enemy_type[200];
        double sprite_counter, m_sprite_speed;
        double m_camera_x, m_camera_y, m_reverse_camera_x, m_reverse_camera_y;
        double m_will_x, m_will_y, m_will_floor, m_will_collectable;
        double m_boss_x, m_boss_y;
        double m_x_speed, m_y_speed;
        string m_current_level, m_audio, level_image_path[20];
        State m_state;
        shared_ptr<Texture> m_background[3], m_level[20], m_enemy[4], m_collectable, m_will[20], m_boss;
        vector< Button* > m_buttons;
        int m_audio_duration, m_audio_start;
};

#endif