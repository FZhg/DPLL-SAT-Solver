//
// Created by Zhang Fan on 2022-12-05.
//

#include <iostream>
#include <utility>
#include "DPLLSolver.h"
#include "tseitinTransformer.h"





bool DPLLSolver::dpll(std::vector<std::vector<int>> cnf) {

    cnf = bcp(cnf);
    cnf = plp(cnf);

    if(cnf.empty()){
        return true;
    }

    for (const std::vector<int>& clause : cnf) {
        if( clause.empty()){
            return false;
        }
    }


    int literal = cnf[0][0];
    int variableId = abs(literal);
    assignment.push(variableId, true);




    if(dpll(cnf)){
        return true;
    } else{

        assignment.push(variableId, false);
        return dpll(cnf);
    }
}




bool DPLLSolver::solve(std::vector<std::vector<int>> cnf) {
    return dpll(cnf);

}

std::vector<std::vector<int>> DPLLSolver::bcp(std::vector<std::vector<int>> cnf) {

    while(!assignment.empty()){

        std::pair<int, bool> variableIdValuePair = assignment.front();



        int variableId = variableIdValuePair.first;
        bool value = variableIdValuePair.second;
        std::vector<std::vector<int>>::iterator clauseIterator = cnf.begin();


        while(clauseIterator != cnf.end()){
            bool isClauseDropped = false;


            std::vector<int>::iterator literalIterator = (* clauseIterator).begin();

            while(literalIterator !=(* clauseIterator).end() ){
                int literal = *literalIterator;
                int  variableIdInLiteral = abs(literal);

                if (variableIdInLiteral == variableId){
                    // do the surgery
                    if ( (literal > 0 and value  ) or ( literal < 0 and !value )){
                        // drop satisfied clauses
                        clauseIterator = cnf.erase(clauseIterator);
                        isClauseDropped = true;
                        break;
                    } else {
                        //drop unsatisfied literal
                        literalIterator = (* clauseIterator).erase(literalIterator);
                    }


                } else{
                    literalIterator ++;
                }
            }

            // Unit resolution

            if((* clauseIterator).size() == 1) { // hasn't been assigned yet
                int unitLiteral = (* clauseIterator)[0];
                int unitVariableId = abs(unitLiteral);
                if(assignment.isKeyNew(unitVariableId)){
                    if(unitLiteral > 0){
                        assignment.push(unitVariableId, true);
                    } else{
                        assignment.push(unitVariableId, false);
                    }
                }
            }

            if(!isClauseDropped){
                clauseIterator ++;
            }
        }
        assignment.pop();
    }
    return cnf;
}

std::vector<std::vector<int>> DPLLSolver::plp(std::vector<std::vector<int>> cnf) {
    // Just like bucket sort
    // find the variable that appears only positively or negatively

    std::map<int, int> variableNegPos = std::map<int, int>();
    // the value is +1 for positive appearance
    // the value is 0 for mixing appearance
    // the value is -1 for negative appearance


    for(std::vector<int> clause : cnf){
        for(int literal : clause){
            int  variableId = abs(literal);
            if(variableNegPos.find(variableId) == variableNegPos.end()){
                if(literal > 0){
                    variableNegPos[variableId] = 1;
                } else{
                    variableNegPos[variableId] = -1;
                }
            } else{
                if(variableNegPos[variableId] == 0){
                    continue;
                } else if (variableNegPos[variableId] == 1){
                    if(literal < 0){
                        variableNegPos[variableId] = 0;
                    }
                } else{
                    if(literal > 0){
                        variableNegPos[variableId] = 0;
                    }
                }
            }
        }
    }



    // drop clauses with pure literals
    for (auto const& pair : variableNegPos){
        int variableId = pair.first;
        int appearance = pair.second;
        if (appearance != 0){
            std::vector<std::vector<int>>::iterator  clauseIterator = cnf.begin();
           while(clauseIterator != cnf.end()){
               bool isClauseDropped = false;
               for(int literal : (* clauseIterator)){
                    int variableIdInLiteral  = abs(literal);
                    if(variableId == variableIdInLiteral){
                        clauseIterator = cnf.erase(clauseIterator);
                        isClauseDropped = true;
                        break;
                    }
               }

               if(!isClauseDropped){
                   clauseIterator ++;
               }
           }

        }
    }
    return cnf;
}



DPLLSolver::DPLLSolver() {
    assignment  = QueMap<int, bool>();
}




