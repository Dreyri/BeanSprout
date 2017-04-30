#ifndef NODE_H
#define NODE_H

#include <vector>
#include <glm/glm.hpp>

namespace BS
{
class Node
{
private:
    Node* mParent;
    std::vector<Node*> mChildren;
    //do we need to recalculate transforms or not
    bool mIsTransformValid;
    bool mIsVisible;

    glm::mat4 mTransform;
    glm::mat4 mWorldTransform;


public:
    Node();
    Node(Node* parent);
    virtual ~Node();

    void add(Node* n);
    void remove(Node* n);

    void setTransform(const glm::mat4& transform);

    const glm::mat4& getWorldTransform() const;

    virtual void update(int milliElapsed);
    virtual void draw();

    void invalidateTransforms();

    virtual void transform();
    void treeDraw();


};
}

#endif // NODE_H
