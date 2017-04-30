#include "node.h"

#include <OpenGL/gl.h>

namespace BS
{
Node::Node(Node* parent)
    : mParent(parent), mIsTransformValid(false), mIsVisible(true), mTransform(), mWorldTransform()
{}
Node::Node()
    : Node(nullptr)
{}

Node::~Node()
{
    for(auto& n : mChildren)
    {
        delete n;
    }
}

void Node::add(Node* n)
{
    mChildren.push_back(n);
}

void Node::remove(Node* n)
{
    mChildren.erase(std::remove(mChildren.begin(), mChildren.end(), n), mChildren.end());
}

void Node::setTransform(const glm::mat4& transform)
{
    mTransform = transform;
    Node* parent = mParent;

    if(parent)
        mWorldTransform = parent->getWorldTransform() * mTransform;
    else
        mWorldTransform = mTransform;

    mIsTransformValid = true;

    for(auto& child : mChildren)
        child->invalidateTransforms();
}


void Node::invalidateTransforms()
{
    mIsTransformValid = false;

    for(auto& n : mChildren)
    {
        n->invalidateTransforms();
    }
}

void Node::treeDraw()
{
    if(!mIsVisible)
        return;

    if(!mIsTransformValid)
        transform();



}

void Node::transform()
{
    return;
}
}
