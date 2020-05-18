#pragma once
class Node
{
private:
    std::vector<Node *> _children;
    bool _isVisible = false;


public:
    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void AddChild(Node* child, int tag);
};
