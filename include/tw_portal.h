#ifndef TW_PORTAL_H
#define TW_PORTAL_H

#include <ijengine/engine.h>
#include <ijengine/collidable.h>
#include <ijengine/canvas.h>
#include <ijengine/texture.h>
#include <ijengine/game_object.h>
#include <ijengine/events_translator.h>

class TWPortal : public GameObject, public Collidable {
	public:
		TWPortal();
		~TWPortal();
        double x();
        double y();
        double height();
        double width();
        shared_ptr<Texture> texture();

    protected:
        void update_self(unsigned now, unsigned last);
        void draw_self(Canvas *canvas, unsigned now, unsigned last);

        void set_x(double cx);
        void set_y(double cy);
        void set_height(double ch);
        void register_self(int current_x);

        bool active() const;
        pair<double, double> direction() const;

        const Rectangle& bounding_box() const;
        const list<Rectangle>& hit_boxes() const;

        void on_collision(const Collidable *who, const Rectangle& where, const unsigned now, const unsigned last);

	private:
        double m_x, m_y;
        double m_height, m_width;
		double m_sprite_counter, m_sprite_speed;
		int m_start;
		Rectangle m_bounding_box;
        shared_ptr<Texture> m_texture;
};

#endif
