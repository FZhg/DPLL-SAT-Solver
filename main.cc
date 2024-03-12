#include "tseitinTransformer.h"
#include "satSolver.h"
#include <iostream>
#include "error.h"


// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
    std::string line; // store each input line
    SATSolver satSolver = SATSolver();
    while (not std::cin.eof()) // continuously asking for new inputs from standard input
    {
        try {
            // your code starts here
            std::getline(std::cin, line);

            if(std::cin.eof()){
                break; // the last new line
            }



            if (line.empty()){
                throw InvalidInput();
            }

            bool result = satSolver.solve(line);
            // currently the SatSolver is just a skeleton.

            if (result) {
                std::cout << "sat" << std::endl;
            } else {
                std::cout << "unsat" << std::endl;
            }




        } catch( std::exception& e){
            std::cout <<"Error: " << e.what() << std::endl;
        }
    }

    exit(0); // stop the program with grace

}