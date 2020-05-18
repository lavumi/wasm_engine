#include "precompiled.h"
#include "Node.h"


void Node::AddChild(Node* child, int tag = 0){
    this->_children.push_back(child);
    //todo  tag 어떻게 쓸지 고민해보실?
}