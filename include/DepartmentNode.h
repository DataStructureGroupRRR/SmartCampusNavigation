// DepartmentNode.h
// Purpose: One node of the general department tree. A node may have any
//          number of children, kept in insertion order. Nodes are owned by
//          DepartmentTree; a node never deletes its children.
// Author: Rainier Velasco

#ifndef DEPARTMENT_NODE_H
#define DEPARTMENT_NODE_H

#include <string>
#include <vector>

class DepartmentNode {
    public:
        // Creates a node with the given name and parent (nullptr for the root).
        DepartmentNode(const std::string& name, DepartmentNode* parent);

        const std::string& GetName() const;
        DepartmentNode* GetParent() const;
        const std::vector<DepartmentNode*>& GetChildren() const;

        // Number of direct children.
        int GetChildCount() const;

        // True when the node has no children.
        bool IsLeaf() const;

        // Number of edges from the root (root depth is 0).
        int GetDepth() const;

        // Appends a child at the end of the child list (insertion order).
        void AddChild(DepartmentNode* child);
    private:
        std::string name;
        DepartmentNode* parent;
        std::vector<DepartmentNode*> children;
};

#endif // DEPARTMENT_NODE_H
