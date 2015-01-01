
class Menu : public Screen
{
public:
	enum widget_flag_t
	{
		CLICKABLE = 0x01
	};

	class Widget
	{
	public:
		placement2d place;
		bool mouse_over;
		BitFlags<int> flags;
		Widget(float x, float y, float w, float h)
			: place(x, y, w, h)
			, mouse_over(false)
			, flags()
		{}
		virtual void draw()
		{
			place.start_transform();
			al_draw_rectangle(0, 0, place.size.x, place.size.y, mouse_over ? color::white : color::orange, 2.0);
			place.restore_transform();
			draw_crosshair(place.position.x, place.position.y, mouse_over ? color::white : color::orange);
		}
		virtual void on_click() {}
		virtual void on_enter() {}
		virtual void on_leave() {}
		virtual void on_cursor_move() {}
		void cursor_change_func(float mouse_x, float mouse_y)
		{
			bool collides_now = place.collide(mouse_x, mouse_y);
			if (collides_now && !mouse_over) on_enter();
			else if (!collides_now && mouse_over) on_leave();
			mouse_over = collides_now;
		}
	};

	vec2d pointer_cursor;
	vec2d pointer_cursor_velocity;
	float pointer_cursor_speed;

	Motion motion;
	std::vector<Widget *> widgets;
	
	Menu(Display *display)
		: Screen(display)
		, pointer_cursor(0, 0)
		, pointer_cursor_velocity(0, 0)
		, pointer_cursor_speed(10.0)
		, widgets()
		, motion(50)
	{
	}

	void simulate_click()
	{
		for (unsigned i=0; i<widgets.size(); i++)
		{
			if (widgets[i]->flags.has(CLICKABLE))
			{
				widgets[i]->on_click();
				break;
			}
		}
	}

	void primary_timer_func() override
	{
		// logic
		pointer_cursor += pointer_cursor_velocity;
		pointer_cursor.x = limit<float>(0, display->width(), pointer_cursor.x);
		pointer_cursor.y = limit<float>(0, display->height(), pointer_cursor.y);


		for (unsigned i=0; i<widgets.size(); i++)
			widgets[i]->cursor_change_func(pointer_cursor.x, pointer_cursor.y);


		// drawing
		for (unsigned i=0; i<widgets.size(); i++)
			widgets[i]->draw();


		// draw the cursor
		draw_crosshair(pointer_cursor, color::green);
	}

	void joy_axis_func() override
	{
		bool change = false;
		if (af::current_event->joystick.stick == 0)
		{
			if (af::current_event->joystick.axis == 0) // left-right
			{
				pointer_cursor_velocity.x = af::current_event->joystick.pos * pointer_cursor_speed;
			}
			if (af::current_event->joystick.axis == 1) // up-down
			{
				pointer_cursor_velocity.y = af::current_event->joystick.pos * pointer_cursor_speed;
			}
		}
		else if (af::current_event->joystick.stick == 1)
		{
			if (af::current_event->joystick.axis == 0) // stick 2, left-right
			{
			}
			if (af::current_event->joystick.axis == 1) // stick 1, up-down
			{
			}
		}
	}

	void mouse_axes_func() override
	{
		pointer_cursor += vec2d(af::current_event->mouse.dx, af::current_event->mouse.dy);
	}
};


