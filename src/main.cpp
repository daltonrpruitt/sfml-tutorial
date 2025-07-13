#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

const int windowWidth = 800;
const int windowHeight = 600;
const int numCircles = 1000;
const float circleRadius = 5.0f;
const float circleSpeed = 2.0f;

struct Circle {
    sf::CircleShape shape;
    sf::Vector2f velocity;

    Circle(float radius, float x, float y, float vx, float vy) : shape(radius) {
        shape.setPosition(x, y);
        velocity.x = vx;
        velocity.y = vy;
    }
};

void handleCollision(Circle& circle, const sf::FloatRect& bounds) {
    sf::FloatRect circleBounds = circle.shape.getGlobalBounds();

    if (circleBounds.left <= 0 || circleBounds.left + circleBounds.width >= windowWidth) {
        circle.velocity.x = -circle.velocity.x;
    }

    if (circleBounds.top <= 0 || circleBounds.top + circleBounds.height >= windowHeight) {
        circle.velocity.y = -circle.velocity.y;
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, sf::Rect<T> rect)
{
    os << "Rect at (" << rect.left << ", " << rect.top << ") with dim of " << rect.width << "x" <<rect.height;
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, sf::Vector2<T> vec)
{
    os << "<" << vec.x << ", " << vec.y << ">";
    return os;
}

int main()
{
    auto window = sf::RenderWindow{ sf::VideoMode(windowWidth, windowHeight), "CMake SFML Project" };
    window.setFramerateLimit(144);

    std::vector<Circle> circles;
    auto clock = sf::Clock();

    std::cout << "Frame bounds of "<< window.getDefaultView().getViewport() << std::endl;
    for (int i = 0; i < numCircles; ++i) {
        float x = static_cast<float>(rand() % (windowWidth - 2 * static_cast<int>(circleRadius))) + circleRadius;
        float y = static_cast<float>(rand() % (windowHeight - 2 * static_cast<int>(circleRadius))) + circleRadius;
        float vx = static_cast<float>(rand() % 200 - 100); // Random velocity in range [-100, 100]
        float vy = static_cast<float>(rand() % 200 - 100);
        if(i<5) std::cout << "Circle with "<< x << "," << y << "," << vx << "," << vy << std::endl;
        circles.emplace_back(circleRadius, x, y, vx, vy);
    }

    clock.restart();
    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        auto elapsed_time = clock.restart().asSeconds();
        for (Circle& circle : circles) {
            auto move_vector = circle.velocity * circleSpeed * elapsed_time;
            circle.shape.move(move_vector);
            handleCollision(circle, window.getDefaultView().getViewport());
            window.draw(circle.shape);
        }

        window.display();
    }
}