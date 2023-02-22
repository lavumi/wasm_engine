//
// Created by Lavumi on 2023/02/22.
//
#include "../precompiled.h"
#include "Node.h"

using namespace std;
using namespace VumiEngine;


void Node::Init(){

}

void Node::AddChild(Node* child, int tag = 0){
    this->_children.push_back(child);
    //todo  tag 어떻게 쓸지 고민해보실?
}

void Node::Update(float deltaTime) {
    for (int i = 0; i < _children.size(); ++i) {
        _children[i]->Update(deltaTime);
    }

//    for_each(this->_children.begin(), this->_children.end(), [&deltaTime](Node& node){
//        node.Update(deltaTime);
//    });
}

void Node::Render() {
    for (int i = 0; i < _children.size(); ++i) {
        _children[i]->Render();
    }

//    for_each(this->_children.begin(), this->_children.end(), [](Node& node){
//        node.Render();
//    });
}

void Node::RemoveChild(Node *child) {

}
