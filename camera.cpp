#include <SFML/Graphics.hpp>

class Camera
{
public:
    Camera();
    ~Camera();

    void setCenter(float x, float y);
    sf::View view();

private:
    sf::View _view;
};

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::setCenter(float x, float y)
{
    _view.setCenter(x, y);
}

sf::View Camera::view()
{
    return _view;
}
