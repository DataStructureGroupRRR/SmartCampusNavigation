// DepartmentTree.cpp
// Purpose: Implementation of the general department tree: loading and
//          validating departments.txt, adding/searching departments, the
//          indented hierarchy display and preorder traversal.
// Author: Rainier Velasco

#include <fstream>

#include "DepartmentTree.h"
#include "DepartmentUtil.h"

using namespace std;
using namespace deptutil;

namespace {
    const char* const DEPARTMENTS_FILENAME = "departments.txt";
    const char* const ROOT_PARENT_MARKER = "NONE";
    const int INDENT_PER_DEPTH = 4;
}

// Starts with an empty tree.
DepartmentTree::DepartmentTree() : root(nullptr) {
}

// Releases every node.
DepartmentTree::~DepartmentTree() {
    Clear();
}

// Deletes all nodes (the tree owns them) and resets to empty.
void DepartmentTree::Clear() {
    for (size_t i = 0; i < nodes.size(); ++i) {
        delete nodes[i];
    }
    nodes.clear();
    root = nullptr;
}

// Linear search by name, ignoring case and outer whitespace.
DepartmentNode* DepartmentTree::FindMutable(const string& name) const {
    string wanted = Trim(name);
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (EqualsIgnoreCase(nodes[i]->GetName(), wanted)) {
            return nodes[i];
        }
    }
    return nullptr;
}

// Public search: same as FindMutable but read-only.
const DepartmentNode* DepartmentTree::FindDepartment(const string& name) const {
    return FindMutable(name);
}

bool DepartmentTree::IsEmpty() const {
    return root == nullptr;
}

int DepartmentTree::GetSize() const {
    return static_cast<int>(nodes.size());
}

const DepartmentNode* DepartmentTree::GetRoot() const {
    return root;
}

// Validates and adds one department. Check order: blank name, (root case),
// blank parent, unknown parent, duplicate name. The tree is unchanged on error.
bool DepartmentTree::AddDepartment(const string& name, const string& parentName,
                                   string& errorMessage) {
    string cleanName = Trim(name);
    string cleanParent = Trim(parentName);

    if (cleanName.empty()) {
        errorMessage = "department name cannot be empty";
        return false;
    }

    // Empty tree: the first department becomes the root, no parent needed.
    if (root == nullptr) {
        root = new DepartmentNode(cleanName, nullptr);
        nodes.push_back(root);
        return true;
    }

    if (cleanParent.empty()) {
        errorMessage = "parent department cannot be empty";
        return false;
    }

    DepartmentNode* parent = FindMutable(cleanParent);
    if (parent == nullptr) {
        errorMessage = "unknown parent department '" + cleanParent + "'";
        return false;
    }

    DepartmentNode* existing = FindMutable(cleanName);
    if (existing != nullptr) {
        errorMessage = "duplicate department name '" + cleanName +
                       "' (already exists as '" + existing->GetName() + "')";
        return false;
    }

    DepartmentNode* node = new DepartmentNode(cleanName, parent);
    parent->AddChild(node);
    nodes.push_back(node);
    return true;
}

// Reads departments.txt line by line, validating each record (Section 5.5).
DepartmentLoadResult DepartmentTree::LoadFromFile(const string& dataDir) {
    Clear();

    DepartmentLoadResult result;
    result.accepted = 0;
    result.rejected = 0;

    string path = dataDir.empty() ? string("data") : dataDir;
    if (path[path.size() - 1] != '/' && path[path.size() - 1] != '\\') {
        path += "/";
    }
    path += DEPARTMENTS_FILENAME;

    ifstream file(path.c_str());
    if (!file.is_open()) {
        cout << "ERROR: Could not open " << path
             << "; treating " << DEPARTMENTS_FILENAME << " as empty." << endl;
        cout << DEPARTMENTS_FILENAME << ": " << result.accepted << " accepted, "
             << result.rejected << " rejected" << endl;
        return result;
    }

    string line;
    int lineNumber = 0;
    while (getline(file, line)) {
        ++lineNumber;

        // Skip a UTF-8 byte order mark if the file starts with one.
        if (lineNumber == 1 && line.size() >= 3 &&
            static_cast<unsigned char>(line[0]) == 0xEF &&
            static_cast<unsigned char>(line[1]) == 0xBB &&
            static_cast<unsigned char>(line[2]) == 0xBF) {
            line = line.substr(3);
        }

        string trimmed = Trim(line); // also removes '\r'
        if (trimmed.empty() || trimmed[0] == '#') {
            continue; // blank line or comment line
        }

        string reason;
        vector<string> fields = SplitFields(trimmed, '|');

        if (fields.size() != 2) {
            reason = "expected 2 fields (DepartmentName|ParentName) but found " +
                     to_string(fields.size());
        } else {
            string name = Trim(fields[0]);
            string parent = Trim(fields[1]);

            if (name.empty()) {
                reason = "department name is empty";
            } else if (parent.empty()) {
                reason = "parent name is empty";
            } else if (root == nullptr) {
                // The first valid record is the root and must use NONE.
                if (!EqualsIgnoreCase(parent, ROOT_PARENT_MARKER)) {
                    reason = "the first department (root) must have parent NONE, found '" +
                             parent + "'";
                } else {
                    AddDepartment(name, "", reason);
                }
            } else if (EqualsIgnoreCase(parent, ROOT_PARENT_MARKER)) {
                reason = "only the root department may have parent NONE";
            } else {
                AddDepartment(name, parent, reason);
            }
        }

        if (reason.empty()) {
            ++result.accepted;
        } else {
            ++result.rejected;
            cout << "WARNING: " << DEPARTMENTS_FILENAME << " line " << lineNumber
                 << ": " << reason << " (record skipped)" << endl;
        }
    }
    file.close();

    cout << DEPARTMENTS_FILENAME << ": " << result.accepted << " accepted, "
         << result.rejected << " rejected" << endl;
    return result;
}

// Iterative preorder: visit node, then its children left to right.
// Children are pushed in reverse so the first child is popped first.
vector<pair<const DepartmentNode*, int> > DepartmentTree::PreorderWithDepth() const {
    vector<pair<const DepartmentNode*, int> > order;
    if (root == nullptr) {
        return order;
    }

    vector<pair<const DepartmentNode*, int> > stack;
    stack.push_back(make_pair(static_cast<const DepartmentNode*>(root), 0));

    while (!stack.empty()) {
        pair<const DepartmentNode*, int> current = stack.back();
        stack.pop_back();
        order.push_back(current);

        const vector<DepartmentNode*>& kids = current.first->GetChildren();
        for (size_t i = kids.size(); i > 0; --i) {
            stack.push_back(make_pair(static_cast<const DepartmentNode*>(kids[i - 1]),
                                      current.second + 1));
        }
    }
    return order;
}

// Returns the preorder sequence of names.
vector<string> DepartmentTree::PreorderNames() const {
    vector<string> names;
    vector<pair<const DepartmentNode*, int> > order = PreorderWithDepth();
    for (size_t i = 0; i < order.size(); ++i) {
        names.push_back(order[i].first->GetName());
    }
    return names;
}

// Prints one department per line, indented four spaces per depth level.
void DepartmentTree::PrintHierarchy(ostream& out) const {
    if (root == nullptr) {
        out << "No departments are loaded." << endl;
        return;
    }

    vector<pair<const DepartmentNode*, int> > order = PreorderWithDepth();
    for (size_t i = 0; i < order.size(); ++i) {
        out << string(order[i].second * INDENT_PER_DEPTH, ' ')
            << order[i].first->GetName() << "\n";
    }
    out << flush;
}
