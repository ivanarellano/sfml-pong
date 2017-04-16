#include "Pong.hpp"

namespace Pong
{
	const int WindowInfo::k_width{800};
	const int WindowInfo::k_height{600};

	bool can_go_up(const sf::RectangleShape& shape)
	{
		return shape.getPosition().y >= 0;
	}

	bool can_go_down(const sf::RectangleShape& shape)
	{
		return shape.getPosition().y + shape.getSize().y <= WindowInfo::k_height;
	}

	Window::Window(const std::string& title, Screen* screen)
		: m_sf_render_thread{&Window::render_thread, this}
	{
		m_sf_window.create(sf::VideoMode(WindowInfo::k_width, WindowInfo::k_height), title);

		set_screen(screen);

		m_sf_window.setActive(false);

		m_sf_render_thread.launch();

		while (m_sf_window.isOpen())
		{
			poll_input_events();

			update_game_state();
		}

		shutdown();
	}

	void Window::poll_input_events()
	{
		sf::Event event;

		while (m_sf_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_sf_window.close();
			}
			else
			{
				m_screen->handle_input(event);
			}
		}
	}

	void Window::update_game_state()
	{
		m_screen->update(m_frame_time.restart().asSeconds());
	}

	void Window::draw_frame()
	{
		while (m_sf_window.isOpen())
		{
			m_sf_window.clear();

			m_screen->draw(&m_sf_window);

			m_sf_window.display();
		}
	}

	void Window::shutdown() const
	{
		m_screen->on_stop();
	}

	void Window::render_thread()
	{
		draw_frame();
	}

	void Window::set_screen(Screen* screen)
	{
		m_screen = screen;
		m_screen->on_start();
	}

	GameScreen::GameScreen() : GameScreen {35.f, 40.f, 3}
	{
		m_player_1.set_name("P1");
		m_player_2.set_name("P2");

		m_winner_text.set_size(80);
		m_press_key_text.set_size(20);
	}

	void GameScreen::on_start()
	{
		m_ball.set_visibility(Visibility::Gone);
		m_winner_text.set_visibility(Visibility::Gone);
		m_press_key_text.set_visibility(Visibility::Gone);

		m_p1_score = 0;
		m_p2_score = 0;
		m_p1_score_view.set_text(std::to_string(m_p1_score));
		m_p2_score_view.set_text(std::to_string(m_p1_score));

		m_p1_score_view.set_position(WindowInfo::k_width * .25f - m_p1_score_view.get_width() / 2, k_score_offset);
		m_p2_score_view.set_position(WindowInfo::k_width * .75f - m_p2_score_view.get_width() / 2, k_score_offset);

		const float player_2_x_pos{-k_paddle_offset + WindowInfo::k_width - m_player_1.get_width()};
		const float player_vertical_center{WindowInfo::k_height / 2 - m_player_1.get_height() / 2};

		m_player_1.set_position(k_paddle_offset, player_vertical_center);
		m_player_2.set_position(player_2_x_pos, player_vertical_center);

		m_server = coin_toss() ? &m_player_1 : &m_player_2;

		m_state = PlayState::Serving;
	}

	void GameScreen::serve()
	{
		if (m_server == nullptr)
			return;

		Ball::Direction dir;

		if (m_server == &m_player_1)
		{
			dir = coin_toss() ? Ball::Direction::NE : Ball::Direction::SE;
		}
		else
		{
			dir = coin_toss() ? Ball::Direction::NW : Ball::Direction::SW;
		}

		const float ball_pos_x{WindowInfo::k_width / 2 - m_ball.get_width() / 2};
		const float ball_pos_y{static_cast<float>(random(static_cast<int>(m_ball.get_height()), WindowInfo::k_height)) - m_ball.get_height() / 2};

		m_ball.set_direction(dir);
		m_ball.reset_velocity();
		m_ball.set_position(ball_pos_x, ball_pos_y);
		m_ball.set_visibility(Visibility::Visible);

		m_state = PlayState::Playing;
	}

	void GameScreen::update(float dt)
	{
		if (PlayState::Playing == m_state || PlayState::Serving == m_state)
		{
			const bool did_press_up{sf::Keyboard::isKeyPressed(sf::Keyboard::Up)};
			const bool did_press_down{sf::Keyboard::isKeyPressed(sf::Keyboard::Down)};
			const bool did_press_w{sf::Keyboard::isKeyPressed(sf::Keyboard::W)};
			const bool did_press_s{sf::Keyboard::isKeyPressed(sf::Keyboard::S)};

			m_player_1.move_up(did_press_w && can_go_up(m_player_1.get_shape()));
			m_player_1.move_down(did_press_s && can_go_down(m_player_1.get_shape()));

			m_player_2.move_up(did_press_up && can_go_up(m_player_2.get_shape()));
			m_player_2.move_down(did_press_down && can_go_down(m_player_2.get_shape()));

			m_player_1.update(dt);
			m_player_2.update(dt);
		}

		if (PlayState::Won == m_state)
		{
			/* Wait for any key event to restart */
		}
		else if (PlayState::Serving == m_state)
		{
			m_time += m_clock.getElapsedTime().asSeconds();
			m_clock.restart();

			if (m_time >= k_serve_delay)
			{
				serve();
				m_time = 0;
				m_clock.restart();
			}
		}
		else if (PlayState::Playing == m_state)
		{
			Paddle* m_winner = did_player_win();

			if (m_winner != nullptr)
			{
				m_ball.set_visibility(Visibility::Gone);

				show_winner(m_winner->get_name());
				m_state = PlayState::Won;
				return;
			}

			const bool did_p1_score{m_ball.get_shape().getPosition().x > WindowInfo::k_width};
			const bool did_p2_score{m_ball.get_shape().getPosition().x + m_ball.get_width() < 0};

			if (did_p1_score)
			{
				m_p1_score_view.set_text(std::to_string(++m_p1_score));
				m_server = &m_player_1;
			}

			if (did_p2_score)
			{
				m_p2_score_view.set_text(std::to_string(++m_p2_score));
				m_server = &m_player_2;
			}

			if (did_p1_score || did_p2_score)
			{
				m_state = PlayState::Serving;
				return;
			}

			const bool did_hit_p1{m_ball.get_shape().getGlobalBounds().intersects(m_player_1.get_shape().getGlobalBounds())};
			const bool did_hit_p2{m_ball.get_shape().getGlobalBounds().intersects(m_player_2.get_shape().getGlobalBounds())};

			if (did_hit_p1 || did_hit_p2)
				m_ball.reflect_on_paddle();

			if (!can_go_up(m_ball.get_shape()) || !can_go_down(m_ball.get_shape()))
				m_ball.reflect_on_court();

			m_ball.update(dt);
		}
	}

	void GameScreen::draw(sf::RenderWindow* window)
	{
		m_half_court_line.draw(window);
		m_player_1.draw(window);
		m_player_2.draw(window);
		m_ball.draw(window);
		m_p1_score_view.draw(window);
		m_p2_score_view.draw(window);
		m_winner_text.draw(window);
		m_press_key_text.draw(window);
	}

	void GameScreen::handle_input(sf::Event event)
	{
		if (PlayState::Won == m_state)
			on_start();
	}

	Paddle* GameScreen::did_player_win()
	{
		bool did_p1_win{m_p1_score > 5};
		bool did_p2_win{m_p2_score > 5};

		return did_p1_win ? &m_player_1 : did_p2_win ? &m_player_2 : nullptr;
	}

	void GameScreen::show_winner(std::string name)
	{
		m_winner_text.set_text("GG.\n" + name + " Wins!");
		m_winner_text.set_position(WindowInfo::k_width / 2 - m_winner_text.get_width() / 2,
		                           WindowInfo::k_height / 2 - m_winner_text.get_height() / 2);

		m_press_key_text.set_text("Press any key\nto play again.");
		m_press_key_text.set_position(m_winner_text.get_position().x,
		                              m_winner_text.get_position().y + m_winner_text.get_height());

		m_winner_text.set_visibility(Visibility::Visible);
		m_press_key_text.set_visibility(Visibility::Visible);
	}

	Paddle::Paddle() : Paddle {sf::Vector2f{16.f, 50.f}, 375.f}
	{
	}

	void Paddle::update(float dt)
	{
		if (m_move_up)
		{
			move(0, -m_move_speed * dt);
		}
		else if (m_move_down)
		{
			move(0, m_move_speed * dt);
		}
	}

	Ball::Ball() : Ball {sf::Vector2f{10.f, 10.f}, 300, 500, 50}
	{
		m_bounce_sound.load(Sound::Asset::blip);
	}

	void Ball::update(float dt)
	{
		const float time_adjusted_speed = m_velocity * dt;
		switch (m_direction)
		{
		case Direction::NW:
			move(-time_adjusted_speed, -time_adjusted_speed);
			break;
		case Direction::NE:
			move(time_adjusted_speed, -time_adjusted_speed);
			break;
		case Direction::SW:
			move(-time_adjusted_speed, time_adjusted_speed);
			break;
		case Direction::SE:
			move(time_adjusted_speed, time_adjusted_speed);
			break;
		case Direction::None:
			break;
		}
	}

	void Ball::increase_velocity(float vel)
	{
		float new_vel = m_velocity + vel;

		if (new_vel < k_max_velocity)
		{
			m_velocity = new_vel;
		}
		else
		{
			m_velocity = k_max_velocity;
		}
	}

	void Ball::reflect_on_court()
	{
		m_bounce_sound.play();

		switch (m_direction)
		{
		case Direction::NW:
			m_direction = Direction::SW;
			break;
		case Direction::NE:
			m_direction = Direction::SE;
			break;
		case Direction::SW:
			m_direction = Direction::NW;
			break;
		case Direction::SE:
			m_direction = Direction::NE;
			break;
		default:
			m_direction = Direction::None;
		}
	}

	void Ball::reflect_on_paddle()
	{
		m_bounce_sound.play();
		increase_velocity(k_spring_force);

		switch (m_direction)
		{
		case Direction::NW:
			m_direction = Direction::NE;
			break;
		case Direction::NE:
			m_direction = Direction::NW;
			break;
		case Direction::SW:
			m_direction = Direction::SE;
			break;
		case Direction::SE:
			m_direction = Direction::SW;
			break;
		default:
			m_direction = Direction::None;
		}
	}

	HalfCourtLine::HalfCourtLine() : HalfCourtLine {sf::Vector2f{6.f, 20.f}, 30}
	{
	}

	HalfCourtLine::HalfCourtLine(sf::Vector2f size, float gap)
		: m_dash_width {size.x}
		, m_dash_height {size.y}
	{
		if (gap < 1 || m_dash_width < 1 || m_dash_height < 1)
			return;

		for (float y_offset = 0; y_offset < WindowInfo::k_height; y_offset += m_dash_height + gap)
		{
			sf::RectangleShape rect{sf::Vector2f{m_dash_width, m_dash_height}};

			rect.setPosition(static_cast<float>(WindowInfo::k_width / 2 - m_dash_width / 2), m_dash_height + y_offset);
			m_notches.push_back(rect);
		}
	}

	void HalfCourtLine::draw(sf::RenderWindow* window)
	{
		for (auto& notch : m_notches)
			window->draw(notch);
	}
}
