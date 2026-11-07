// DepartmentMenu.cpp
// Purpose: Implementation of the department menu handlers. Names are read
//          with getline so they may contain spaces; blank names are rejected
//          with an error and control returns to the menu.
// Author: Rainier Velasco

#include <iostream>
#include <string>

#include "DepartmentMenu.h"
#include "DepartmentUtil.h"

using namespace std;
using namespace deptutil;

namespace {
    // Prompts and reads one full line, trimmed. Returns false if input ended.
    bool PromptLine(const string& prompt, string& out) {
        cout << prompt << flush;
        string line;
        if (!getline(cin, line)) {
            cin.clear();
            cout << endl << "No input received." << endl;
            return false;
        }
        out = Trim(line);
        return true;
    }
}

// Adds a department: root without a parent prompt when the tree is empty.
void HandleAddDepartment(DepartmentTree& tree) {
    string name;
    if (!PromptLine("Enter new department name: ", name)) {
        return;
    }
    if (name.empty()) {
        cout << "Error: department name cannot be blank." << endl;
        return;
    }

    string error;

    if (tree.IsEmpty()) {
        if (tree.AddDepartment(name, "", error)) {
            cout << "Department '" << tree.GetRoot()->GetName()
                 << "' added as the root of the hierarchy." << endl;
        } else {
            cout << "Error: " << error << "." << endl;
        }
        return;
    }

    // Reject a duplicate before asking for a parent.
    const DepartmentNode* existing = tree.FindDepartment(name);
    if (existing != nullptr) {
        cout << "Error: duplicate department name '" << name
             << "' (already exists as '" << existing->GetName() << "'). Tree unchanged." << endl;
        return;
    }

    string parentName;
    if (!PromptLine("Enter parent department name: ", parentName)) {
        return;
    }
    if (parentName.empty()) {
        cout << "Error: parent department name cannot be blank." << endl;
        return;
    }

    if (tree.AddDepartment(name, parentName, error)) {
        const DepartmentNode* added = tree.FindDepartment(name);
        cout << "Department '" << added->GetName() << "' added under '"
             << added->GetParent()->GetName() << "'." << endl;
    } else {
        cout << "Error: " << error << ". Tree unchanged." << endl;
    }
}

// Searches by name and shows name, parent, child count and depth.
void HandleSearchDepartment(const DepartmentTree& tree) {
    string name;
    if (!PromptLine("Enter department name to search: ", name)) {
        return;
    }
    if (name.empty()) {
        cout << "Error: department name cannot be blank." << endl;
        return;
    }
    if (tree.IsEmpty()) {
        cout << "No departments are loaded." << endl;
        return;
    }

    const DepartmentNode* node = tree.FindDepartment(name);
    if (node == nullptr) {
        cout << "Department '" << name << "' was not found." << endl;
        return;
    }

    cout << "Department found:" << endl;
    cout << "  Name: " << node->GetName() << endl;
    cout << "  Parent: "
         << (node->GetParent() == nullptr ? string("None") : node->GetParent()->GetName())
         << endl;
    cout << "  Direct children: " << node->GetChildCount() << endl;
    cout << "  Depth: " << node->GetDepth() << endl;
}

// Shows the indented hierarchy (or an empty-tree message).
void HandleDisplayHierarchy(const DepartmentTree& tree) {
    if (!tree.IsEmpty()) {
        cout << "Department hierarchy:" << endl;
    }
    tree.PrintHierarchy(cout);
}

// Shows the preorder sequence, one numbered department per line, no indentation.
void HandlePreorderTraversal(const DepartmentTree& tree) {
    if (tree.IsEmpty()) {
        cout << "No departments are loaded." << endl;
        return;
    }

    vector<string> names = tree.PreorderNames();
    cout << "Preorder traversal:" << endl;
    for (size_t i = 0; i < names.size(); ++i) {
        cout << (i + 1) << ". " << names[i] << endl;
    }
}
