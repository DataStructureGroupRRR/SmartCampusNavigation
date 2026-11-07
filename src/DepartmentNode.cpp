// DepartmentNode.cpp
// Purpose: Implementation of DepartmentNode (one node of the general tree).
// Author: Rainier Velasco

#include "DepartmentNode.h"

using namespace std;

// Stores the name and parent link; the child list starts empty.
DepartmentNode::DepartmentNode(const string& name, DepartmentNode* parent)
    : name(name), parent(parent) {
}

// Returns the department name (spelling from the first accepted record).
const string& DepartmentNode::GetName() const {
    return name;
}

// Returns the parent node, or nullptr for the root.
DepartmentNode* DepartmentNode::GetParent() const {
    return parent;
}

// Returns the children in insertion order.
const vector<DepartmentNode*>& DepartmentNode::GetChildren() const {
    return children;
}

// Returns how many direct children this node has.
int DepartmentNode::GetChildCount() const {
    return static_cast<int>(children.size());
}

// A leaf has no children.
bool DepartmentNode::IsLeaf() const {
    return children.empty();
}

// Counts edges up to the root by following parent links.
int DepartmentNode::GetDepth() const {
    int depth = 0;
    const DepartmentNode* current = parent;
    while (current != nullptr) {
        ++depth;
        current = current->parent;
    }
    return depth;
}

// Adds a child to the end of the list so siblings keep insertion order.
void DepartmentNode::AddChild(DepartmentNode* child) {
    children.push_back(child);
}
