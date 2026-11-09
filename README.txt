Smart Campus Navigation and Facility Analytics System

This C++ project loads campus data and lets users explore buildings and
facilities. My Milestone 1 work covers the campus graph and BFS reachability.
Graph display, counts, degrees and BFS work through menu options 3, 4 and 5.
Option 0 exits. Facility and department menu options still need team integration.

Building and running
Use CMake and a C++11-compatible compiler. From the project root:
  cmake -S . -B build
  cmake --build build
  ./build/SmartCampusNavigation
The executable location depends on the generator. On Windows it may be under
build/Debug. Our existing VS Code launch setup uses build/ninja:
  cmake --build build/ninja
  ./build/ninja/SmartCampusNavigation.exe

The first argument optionally selects a data directory:
  ./build/ninja/SmartCampusNavigation.exe testdata/graph-validation
Without an argument, the program reads data/. Run from the project root so
these relative paths resolve correctly.

Files
  src/ and include/    C++ source and header files
  data/                Original instructor data
  testdata/graph-validation/  Extra graph records, including invalid records
  testdata/graph-empty/       Comment-only files for an empty graph
  test_results.txt     Inputs, expected results, actual results and pass/fail
  design_document.txt  My graph/BFS design notes
  CONTRIBUTIONS.txt    My contributions so far

Testing
No separate test script is needed. Follow the input sequences in
test_results.txt. With the sample data, try options 3 and 4, then run BFS from
Library, Observatory and an unknown building. Also try a blank name and invalid
menu input, then run another operation to check recovery.

Use testdata/graph-validation for duplicate names, bad connections and separate
groups of buildings. Use testdata/graph-empty for empty-graph behavior.
For missing-file handling, pass a directory that does not exist, such as
testdata/graph-missing. That directory is intentionally not included.

The Windows build and all ten recorded graph/menu tests passed. These results
cover my part, not the full team project. Before submission, we still need to
finish facility/hash-table and department integration, add the other members'
design notes, contributions and tests, and verify compilation and execution
on CELL.
