#include "cameraortho.h"

namespace BS
{
CameraOrtho::CameraOrtho()
    : mPosition(0.0f, 0.0f, 0.0f), mNearPlane(0.01f), mFarPlane(1000.0f)
{}

void CameraOrtho::setPosition(const glm::vec3& pos)
{
    mPosition = pos;
}

const glm::vec3& CameraOrtho::getPosition() const
{
    return mPosition;
}
}
