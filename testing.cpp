#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(200, 200), "SFML works!");
    
    CircleShape shape(20.f);
    shape.setFillColor(Color::Blue);
    shape.setOrigin(Vector2f(20, 20));
    shape.setPosition(Vector2f(100, 20));

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            } else if (Keyboard::isKeyPressed(Keyboard::Left)) {
                Vector2f pose = shape.getPosition();
                pose.x--;
                shape.setPosition(pose);
            } else if (Keyboard::isKeyPressed(Keyboard::Right)) {
                Vector2f pose = shape.getPosition();
                pose.x++;
                shape.setPosition(pose);
            } else if (Keyboard::isKeyPressed(Keyboard::Up)) {
                Vector2f pose = shape.getPosition();
                pose.y--;
                shape.setPosition(pose);
            } else if (Keyboard::isKeyPressed(Keyboard::Down)) {
                Vector2f pose = shape.getPosition();
                pose.y++;
                shape.setPosition(pose);
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}