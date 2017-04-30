#ifndef CAMERAORTHO_H
#define CAMERAORTHO_H

#include "graphics/camera.h"
#include <glm/glm.hpp>

namespace BS
{

class CameraOrtho : public Camera
{
private:
    glm::vec3 mPosition;
    float mNearPlane;
    float mFarPlane;
public:
    CameraOrtho();

    virtual void setPosition(const glm::vec3& pos);
    virtual const glm::vec3& getPosition() const;

};
}

#endif // CAMERAORTHO_H
