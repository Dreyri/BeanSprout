#ifndef CAMERA_H
#define CAMERA_H


#include "graphics/node.h"
#include <glm/glm.hpp>

namespace BS
{
class Camera : public Node
{
private:
public:
    Camera();
    virtual ~Camera() = 0;

    virtual void setPosition(const glm::vec3& pos) = 0;
    virtual const glm::vec3& getPosition() const = 0;
};
}

#endif // CAMERA_H
