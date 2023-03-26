//
// Created by Lavumi on 2023/02/22.
//

#ifndef WASM_NODE_H
#define WASM_NODE_H

namespace VumiEngine {
    class Node {
    private:
        std::vector<Node *> _children{};
        bool _isVisible = false;

    public:
//        virtual void Init() = 0;
        virtual void Update(float deltaTime) = 0;

        virtual void Render();

        virtual void AddChild(Node *child, int tag);

        virtual void RemoveChild(Node *child);
    };
}


#endif //WASM_NODE_H
