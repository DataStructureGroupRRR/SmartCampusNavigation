Smart Campus Navigation and Facility Analytics System

C++ campus facility, graph and department project. This checkout currently has
working M1 graph display, degree statistics and BFS reachability. Facility and
department menu integration remains team work; their menu entries say so.

Build from the project root with CMake and a C++11-compatible compiler:
  cmake -S . -B build
  cmake --build build
Run the resulting SmartCampusNavigation executable from the project root:
  ./build/SmartCampusNavigation
  ./build/SmartCampusNavigation testdata/graph-validation
Executable location may differ by generator (e.g. build/Debug on Windows).
The existing Windows VS Code launch configuration uses build/ninja; build it:
  cmake --build build/ninja

The optional first argument selects the data directory; the default is data/.
Paths are relative to the working directory, so run from the project root.
Graph options: 3 display, 4 counts/degrees, 5 BFS; 0 exits.
The remaining M1 menu entries await integration by their module owners.

Layout:
  src/ and include/ : C++ implementations and headers
  data/            : unchanged instructor starter data
  testdata/        : separate graph validation and empty fixtures
  test_results.txt : actual graph/menu test output 
  design_document.txt : current graph/BFS design notes

Manual graph test:
  1. Run with the default data directory. Choose 3 to inspect the graph,
     then 4 to check counts and degrees.
  2. Choose 5 and enter Library; repeat with Observatory and an unknown name.
  3. Try blank input, letters and an out-of-range menu number, then choose 4
     to confirm the menu still works. Choose 0 to exit.
  4. Run with testdata/graph-validation and repeat options 3, 4 and 5.
     Try Island and Alpha Hall as BFS starts.
  5. Run with testdata/graph-empty to check empty-graph behavior.
  6. Run with a nonexistent data-directory argument to check missing files.
See test_results.txt for exact input sequences, expected and actual outcomes.


