#include <iostream>
#include "sokoban_solver.h"

using namespace std;

int main() {
    Sokoban::Solver solver;
    if (!solver.read_level_data(cin)) {
        cout << "Invalid input data" << endl;
        return EXIT_FAILURE;
    }
    solver.print_information();

    if (solver.solve()) {
        solver.print_solution_format1(cout);
    }
}
