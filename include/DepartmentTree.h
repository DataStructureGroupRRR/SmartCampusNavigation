// DepartmentTree.h
// Purpose: General tree of academic departments (any number of children per
//          node). Loads departments.txt, supports adding and searching
//          departments, indented hierarchy display and preorder traversal.
//          The tree owns every node and releases them in its destructor.
// Author: Rainier Velasco

#ifndef DEPARTMENT_TREE_H
#define DEPARTMENT_TREE_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "DepartmentNode.h"

// Counts reported in the load summary line.
struct DepartmentLoadResult {
    int accepted;
    int rejected;
};

class DepartmentTree {
    public:
        DepartmentTree();
        ~DepartmentTree();

        // The tree owns raw node pointers, so copying is disabled.
        DepartmentTree(const DepartmentTree&) = delete;
        DepartmentTree& operator=(const DepartmentTree&) = delete;

        // Loads <dataDir>/departments.txt. Prints a warning (filename, line
        // number, reason) for each rejected record, an error if the file
        // cannot be opened (treated as empty), and the load summary line.
        DepartmentLoadResult LoadFromFile(const std::string& dataDir);

        // Adds a department. If the tree is empty it becomes the root and
        // parentName is ignored; otherwise parentName must name an existing
        // department. On failure returns false, sets errorMessage and leaves
        // the tree unchanged. Names are trimmed; matching ignores case.
        bool AddDepartment(const std::string& name, const std::string& parentName,
                           std::string& errorMessage);

        // Finds a department by name (case-insensitive, trimmed); nullptr if absent.
        const DepartmentNode* FindDepartment(const std::string& name) const;

        bool IsEmpty() const;
        int GetSize() const;
        const DepartmentNode* GetRoot() const;

        // Prints the hierarchy in preorder, four spaces of indentation per
        // depth, one department per line. Prints a message if empty.
        void PrintHierarchy(std::ostream& out) const;

        // Returns department names in preorder (siblings in insertion order).
        std::vector<std::string> PreorderNames() const;

    private:
        // Returns (node, depth) pairs in preorder using an explicit stack.
        std::vector<std::pair<const DepartmentNode*, int> > PreorderWithDepth() const;

        // Deletes every node and resets the tree to empty.
        void Clear();

        DepartmentNode* FindMutable(const std::string& name) const;

        DepartmentNode* root;
        std::vector<DepartmentNode*> nodes; // every node, in insertion order (owner)
};

#endif // DEPARTMENT_TREE_H
