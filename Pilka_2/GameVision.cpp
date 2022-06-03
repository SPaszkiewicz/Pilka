#include "GameVision.h"
#include <math.h>
#include <iostream>

void GameVision::draw_dot(Position const p)
{
    if (p.get_is_ball() == true || p.get_was_used() == true) {
        CircleShape circle(2);
        circle.setFillColor(Color::White);
        circle.setOrigin(1.0f, 1.0f);
        circle.setPosition(p.get_x_pos(), p.get_y_pos());
        this->window->draw(circle);
    }
    else {
        CircleShape circle(1.2f);
        circle.setFillColor(Color::White);
        circle.setOrigin(0.6f, 0.6f);
        circle.setPosition(p.get_x_pos(), p.get_y_pos());
        this->window->draw(circle);
    }
}

void GameVision::draw_line(Position const p1, Position const p2)
{
    float len;
    if (p1.get_x_pos() != p2.get_x_pos() && p1.get_y_pos() != p2.get_y_pos()) {
        len = sqrt((p1.get_x_pos() - p2.get_x_pos()) * (p1.get_x_pos() -
            p2.get_x_pos()) + (p1.get_y_pos() - p2.get_y_pos()) * (p1.get_y_pos() - p2.get_y_pos()));
    }
    else {
        len = 50.0f;
    }
    RectangleShape line(Vector2f(2, len));
    line.setOrigin(0.0f, 0.0f);
    float x1 = p1.get_x_pos();
    float y1 = p1.get_y_pos();
    float x2 = p2.get_x_pos();
    float y2 = p2.get_y_pos();

    if (len < 60 && p2.get_y_pos() == p1.get_y_pos()) {
        line.setRotation(270.0f);
        if (x1 > x2) {
            x1 = x2;
        }
        if (y1 > y2) {
            y1 = y2;
        }
    }
    else if (len > 60) {
        if (y1 > y2) {
            y1 = y2;
            x1 = x2;
        }
        if ((p2.get_y_pos() < p1.get_y_pos() && p2.get_x_pos() < p1.get_x_pos()) ||
            (p2.get_y_pos() > p1.get_y_pos() && p2.get_x_pos() > p1.get_x_pos())) {
            line.setRotation(315.0f);
        }
        else {
            line.setRotation(45.0f);
        }
    }
    line.setFillColor(Color::White);
    line.setPosition(x1, y1);
    this->window->draw(line);

}

void GameVision::eng_game(GameStage situation)
{
    Text p1_text;
    Font font;
    if (!font.loadFromFile("Montserrat-Regular.ttf"))
    {
        cout << "OPPS" << endl;
    }
    p1_text.setFont(font);
    p1_text.setCharacterSize(16);
    p1_text.setFillColor(Color::White);
    p1_text.setStyle(Text::Bold);
    p1_text.setPosition(240, 240);
    if ((situation == WIN && this->game->get_game_map()->get_ball_y() == 12) || (situation == DEFEAT && this->game->get_player() == true))
    {
        p1_text.setString("Player B WON\n\nPress ENTER to close game \n\nPress E to start again");
    }
    else {
        p1_text.setString("Player A WON\n\nPress ENTER to close game \n\nPress E to start again");
    }

    RectangleShape background(Vector2f(700, 700));
    background.setFillColor(Color::Red);
    this->window->draw(background);
    this->window->draw(p1_text);
    this->window->display();
    Event e;
    while (this->window->isOpen())
    {
        while (this->window->pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                this->window->clear();
                this->window->close();
                delete this->game;
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
                this->window->clear();
                this->window->close();
                delete this->game;
                return;
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::E)) {
                delete this->game;
                this->game = new GameEngine();
                this->window->clear();
                this->one_tick();
                return;
            }
        }
    }
}

void GameVision::starting_screen()
{
    Text p1_text;
    Font font;
    if (!font.loadFromFile("Montserrat-Regular.ttf"))
    {
        cout << "OPPS" << endl;
    }
    p1_text.setFont(font);
    p1_text.setCharacterSize(16);
    p1_text.setFillColor(Color::White);
    p1_text.setStyle(Text::Bold);
    p1_text.setPosition(50, 50);
    p1_text.setString("Celem gry jest dotarcie do bramki przeciwnika\n"
        "Gra pozwala na odbicie sie po sladach wczesniej zostawionych\n\n"
        "Sterowanie:\n W - ruch w gore\n E - ruch w prawy gorny rog\n D - ruch w prawo\n "
        "C - ruch w prawy dolny rog \n X - ruch w dol\n Z - ruch w lewy dolny rog"
        "\n A - ruch w lewo\n Q - ruch w lewy gorny rog\n\n Nacisnij ENTER aby kontynuowac");


    RectangleShape background(Vector2f(700, 700));
    background.setFillColor(Color(20, 150, 20));
    this->window->draw(background);
    this->window->draw(p1_text);
    this->window->display();
    Event e;
    GameStage situation = CONT;
    while (this->window->isOpen())
    {
        while (this->window->pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                this->window->clear();
                this->window->close();
                delete this->game;
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
                this->window->clear();
                return;
            }
        }
    }
}



void GameVision::init_background()
{
    RectangleShape field(Vector2f(500, 700));
    RectangleShape stats(Vector2f(200, 700));

    stats.setFillColor(Color(220, 220, 220));
    stats.setPosition(500, 0);
    field.setFillColor(Color(20, 150, 20));

    this->window->draw(field);
    this->window->draw(stats);
}

void GameVision::init_map()
{
    Map * game_map = this->game->get_game_map();
    Position point;
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            point = game_map->get_point(j, i);
            //std::cout << point.get_x_pos() << " " << point.get_y_pos() << std::endl;
            this->draw_dot(point);
            if (point.get_position_type(RIGHT) == LINE) {
                this->draw_line(point, game_map->get_point(j + 1, i));
            }
            if (point.get_position_type(DOWN_RIGHT) == LINE) {
                this->draw_line(point, game_map->get_point(j + 1, i-1));
            }
            if (point.get_position_type(DOWN) == LINE) {
                this->draw_line(point, game_map->get_point(j, i-1));
            }
            if (point.get_position_type(DOWN_LEFT) == LINE) {
                this->draw_line(point, game_map->get_point(j - 1, i - 1));
            }
        }
    }
}

void GameVision::prepare_label()
{
    Text p1_text;
    Text p2_text;
    Font font;
    if (!font.loadFromFile("Montserrat-Regular.ttf"))
    {
        cout << "OPPS" << endl;
    }
    p1_text.setFont(font);
    p1_text.setCharacterSize(24);
    p1_text.setFillColor(Color::Black);
    p1_text.setStyle(Text::Bold);
    p2_text.setFont(font);
    p2_text.setCharacterSize(24);
    p2_text.setFillColor(Color::Black);
    p2_text.setStyle(Text::Bold);
    p1_text.setPosition(510, 50);
    p2_text.setPosition(510, 650);

    if (this->game->get_player()) {
        p1_text.setString(">>  Player A");
        p2_text.setString("    Player B");
    }
    else {
        p1_text.setString("    Player A");
        p2_text.setString(">>  Player B");
    }
    this->window->draw(p1_text);
    this->window->draw(p2_text);
}

void GameVision::one_tick()
{
    this->window->clear();
    this->init_background();
    this->init_map();
    this->prepare_label();
    this->window->display();
    sleep(Time(milliseconds(500)));
}

void GameVision::start_game()
{
    this->init_background();
    this->init_map();
    this->prepare_label();
    this->window->display();
    Event e;
    GameStage situation = BEGIN;
    while (this->window->isOpen())
    {
        while (this->window->pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                this->window->clear();
                this->window->close();
                delete this->game;
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
                situation = this->game->react_on_move(UP);
                this->one_tick();
            }
            else if (Keyboard::isKeyPressed(Keyboard::Key::E)) {
                situation = this->game->react_on_move(UP_RIGHT);
                this->one_tick();
            }
            else if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
                situation = this->game->react_on_move(RIGHT);
                this->one_tick();
            }
            else if (Keyboard::isKeyPressed(Keyboard::Key::C)) {
                situation = this->game->react_on_move(DOWN_RIGHT);
                this->one_tick();
            }
            else if (Keyboard::isKeyPressed(Keyboard::Key::X)) {
                situation = this->game->react_on_move(DOWN);
                this->one_tick();
            }
            else if (Keyboard::isKeyPressed(Keyboard::Key::Z)) {
                situation = this->game->react_on_move(DOWN_LEFT);
                this->one_tick();
            }
            else if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
                situation = this->game->react_on_move(LEFT);
                this->one_tick();
            }
            else if (Keyboard::isKeyPressed(Keyboard::Key::Q)) {
                situation = this->game->react_on_move(UP_LEFT);
                this->one_tick();
            }
            if (situation == WIN || situation == DEFEAT) {
                this->eng_game(situation);
                situation = BEGIN;
            }
        }
    }
}


GameVision::GameVision()
{
    this->window = new RenderWindow(VideoMode(700, 700), "Symulator kopania galy", Style::Titlebar | Style::Close);
    this->game = new GameEngine();
    this->starting_screen();
}

