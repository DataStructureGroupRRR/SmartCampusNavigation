// DepartmentMenu.h
// Purpose: Menu handlers for the department features (add, search, hierarchy
//          display, preorder traversal). main.cpp only needs to call these;
//          all prompting, validation and output for departments lives here.
// Author: Rainier Velasco

#ifndef DEPARTMENT_MENU_H
#define DEPARTMENT_MENU_H

#include "DepartmentTree.h"

// M1 menu option 6: prompts for a name (and a parent unless the tree is
// empty), then adds the department in memory only.
void HandleAddDepartment(DepartmentTree& tree);

// M1 menu option 7: prompts for a name and shows its name, parent
// ("None" for the root), direct-child count and depth.
void HandleSearchDepartment(const DepartmentTree& tree);

// M1 menu option 8: displays the hierarchy indented four spaces per depth.
void HandleDisplayHierarchy(const DepartmentTree& tree);

// M1 menu option 9: displays the preorder sequence without indentation.
void HandlePreorderTraversal(const DepartmentTree& tree);

#endif // DEPARTMENT_MENU_H
