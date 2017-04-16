#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>

#ifdef TARGET_OS_MAC
	#include "ResourcePath.hpp"
#endif

namespace Pong
{
	struct WindowInfo
	{
		const static int k_width;
		const static int k_height;
	};

	bool can_go_up(const sf::RectangleShape& shape);

	bool can_go_down(const sf::RectangleShape& shape);

	inline int random(int min, int max)
	{
		static std::default_random_engine random_engine;
		random_engine.seed(std::random_device{}());
		return std::uniform_int_distribution<>{min, max}(random_engine);
	}

	inline bool coin_toss() { return random(0, 1); }

	inline std::string get_assets_path()
	{
		std::string project_assets_path{"assets/"};
		#ifdef TARGET_OS_MAC
			return resourcePath() + project_assets_path;
		#else
			return project_assets_path;
		#endif
	}

	class Drawable
	{
	public:
		enum class Visibility
		{
			Visible, Gone
		};

		virtual ~Drawable() {}

		virtual void draw(sf::RenderWindow* window) = 0;
	};

	class Measurement
	{
	public:
		virtual ~Measurement() {}

		virtual float get_width() const = 0;
		virtual float get_height() const = 0;
	};

	class Movable
	{
	public:
		virtual ~Movable() {}

		virtual void set_position(float x, float y) = 0;
		virtual void move(float x, float y) = 0;
	};

	struct Font
	{
		enum Asset
		{
			forward
		};

		static std::string get_path(Asset type)
		{
			std::string base = get_assets_path();

			switch (type)
			{
			case forward: return base + "FFFFORWA.TTF";
			default: return "";
			}
		}
	};

	class Sound
	{
	public:
		enum Asset
		{
			blip
		};

		Sound() {}

		void load(const Asset& asset)
		{
			if (m_buffer.loadFromFile(get_path(asset)))
				m_sound.setBuffer(m_buffer);
		}

		void play() { if (m_sound.getBuffer() != nullptr) m_sound.play(); }

		static std::string get_path(Asset asset)
		{
			std::string base = get_assets_path();

			switch (asset)
			{
			case blip: return base + "blip.wav";
			default: return "";
			}
		}

	private:
		sf::SoundBuffer m_buffer;
		sf::Sound m_sound;
	};

	struct Screen : Drawable
	{
		virtual ~Screen() {}

		virtual void on_start() = 0;
		virtual void update(float dt) = 0;
		virtual void handle_input(sf::Event event) = 0;
		virtual void on_stop() = 0;

		Screen(const Screen&) = delete;
		Screen& operator=(const Screen&) = delete;
	protected:
		Screen() {}
	};

	class Window
	{
	public:
		Window(const std::string& title, Screen* screen);
	private:
		sf::RenderWindow m_sf_window;
		sf::Thread m_sf_render_thread;
		sf::Clock m_frame_time;
		Screen* m_screen;

		void poll_input_events();
		void update_game_state();
		void draw_frame();
		void shutdown() const;

		void set_screen(Screen* screen);
		void render_thread();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
	};

	struct Text : Drawable, Measurement, Movable
	{
		explicit Text(Font::Asset asset = Font::forward, int size = 50) : m_visibility(Visibility::Visible)
		{
			m_font.loadFromFile(Font::get_path(asset));

			m_text.setFont(m_font);
			m_text.setFillColor(sf::Color::White);

			set_size(size);
		}

		float get_width() const override { return m_text.getGlobalBounds().width; }
		float get_height() const override { return m_text.getGlobalBounds().height; }

		void draw(sf::RenderWindow* window) override { if (is_visible()) window->draw(m_text); }
		void set_position(float x, float y) override { m_text.setPosition(x, y); }
		void move(float x, float y) override { m_text.move(x, y); }

		sf::Vector2f get_position() const { return m_text.getPosition(); }
		bool is_visible() const { return m_visibility == Visibility::Visible ? true : false; }

		void set_text(const std::string& text) { m_text.setString(text); }
		void set_size(int size) { m_text.setCharacterSize(size); }
		void set_visibility(Visibility vis) { m_visibility = vis; }
	private:
		sf::Text m_text;
		sf::Font m_font;
		Visibility m_visibility;
	};

	struct Actor : Drawable, Measurement, Movable
	{
		explicit Actor(sf::Vector2f size)
			: m_rect {size}
			, m_visibility {Visibility::Visible} {}

		virtual void update(float dt) = 0;

		const std::string& get_name() const { return m_name; }
		void set_name(std::string name) { m_name = name; }

		float get_width() const override { return m_rect.getSize().x; }
		float get_height() const override { return m_rect.getSize().y; }

		void draw(sf::RenderWindow* window) override { if (is_visible()) window->draw(get_shape()); }
		void set_position(float x, float y) override { m_rect.setPosition(x, y); }
		void move(float x, float y) override { m_rect.move(x, y); }

		sf::RectangleShape get_shape() const { return m_rect; }
		bool is_visible() const { return m_visibility == Visibility::Visible ? true : false; }

		void set_visibility(Visibility vis) { m_visibility = vis; }
	private:
		sf::RectangleShape m_rect;
		Visibility m_visibility;
		std::string m_name;
	};

	class Paddle : public Actor
	{
	public:
		Paddle();

		explicit Paddle(sf::Vector2f size, float move_speed)
			: Actor {size}
			, m_move_speed {move_speed}
			, m_move_up {false}
			, m_move_down {false} {}

		void update(float dt) override;

		void move_up(bool can_move_up) { m_move_up = can_move_up; }
		void move_down(bool can_move_down) { m_move_down = can_move_down; }
	private:
		float m_move_speed;
		bool m_move_up;
		bool m_move_down;
	};

	class Ball : public Actor
	{
	public:
		enum class Direction
		{
			None, NW, NE, SW, SE
		};

		Ball();

		explicit Ball(sf::Vector2f size, float start_velocity, float max_velocity, float spring_force)
			: Actor {size}
			, k_start_velocity {start_velocity}
			, k_max_velocity {max_velocity}
			, k_spring_force {spring_force}
			, m_velocity {start_velocity}
			, m_direction {Direction::None} {}

		void update(float dt) override;

		void increase_velocity(float vel);
		void reflect_on_court();
		void reflect_on_paddle();

		void reset_velocity() { m_velocity = k_start_velocity; }
		void set_direction(Direction dir) { m_direction = dir; }
	private:
		const float k_start_velocity;
		const float k_max_velocity;
		const float k_spring_force;

		float m_velocity;
		Direction m_direction;
		Sound m_bounce_sound;
	};

	/*
	* A half court line with a dashed line effect.
	* The width and height set the size of a single dash.
	*/
	class HalfCourtLine : public Drawable
	{
	public:
		HalfCourtLine();

		explicit HalfCourtLine(sf::Vector2f size, float gap);

		void draw(sf::RenderWindow* window) override;
	private:
		float m_dash_width;
		float m_dash_height;
		std::vector<sf::RectangleShape> m_notches;
	};

	class GameScreen : public Screen
	{
	public:
		enum class PlayState
		{
			Playing, Serving, Won
		};

		GameScreen();

		GameScreen(float paddle_offset, float score_offset, int serve_delay)
			: k_serve_delay {serve_delay}
			, k_paddle_offset {paddle_offset}
			, k_score_offset {score_offset}
			, m_p1_score {0}
			, m_p2_score {0}
			, m_state {PlayState::Serving}
			, m_server {nullptr}
			, m_time {0} {}

		virtual void serve();

		void on_start() override;
		void update(float dt) override;
		void draw(sf::RenderWindow* window) override;
		void handle_input(sf::Event event) override;

		void on_stop() override {}

	private:
		const int k_serve_delay;
		const float k_paddle_offset;
		const float k_score_offset;

		int m_p1_score;
		int m_p2_score;
		PlayState m_state;

		Ball m_ball;
		Paddle m_player_1;
		Paddle m_player_2;
		Text m_p1_score_view;
		Text m_p2_score_view;
		HalfCourtLine m_half_court_line;
		Text m_winner_text;
		Text m_press_key_text;

		Paddle* m_server;
		sf::Clock m_clock;
		float m_time;

		Paddle* did_player_win();
		void show_winner(std::string name);
	};
}
