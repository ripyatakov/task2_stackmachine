////////////////////////////////////////////////////////////////////////////////
// Module Name:  stack_machine.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include "stack_machine.h"

#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>

namespace xi {

//==============================================================================
// Free functions -- helpers
//==============================================================================

// TODO: if you need any free functions, add their definitions here.
std::vector<std::string> getTokens(const std::string &expr){
    std::vector<std::string> answs;
    std::string buff = "";
        for (int i = 0; i < expr.size(); ++i) {
            if (expr[i] == ' ')
            {
                answs.push_back(buff);
                buff = "";
            }
            else
                buff += expr[i];
        }
        answs.push_back(buff);
        return answs;
}
bool isOperation(const std::string token){
    if (token.size() != 1)
        return false;
    if (token[0] >= '0' && token[0] <= '9')
        return false;
    return true;
}
bool isNumber(const std::string str){
    bool answ = true;
    for (int i = 0; i < str.size(); ++i) {
        answ = answ && (str[i] >= '0' && str[i] <= '9');
    }
    return answ;
}
//==============================================================================
// class PlusOp
//==============================================================================


int PlusOp::operation(char op, int a, int b, int /*c*/) // < just commented unused argument. This does not affect the code anyhow.
{
    if(op != '+')
        throw std::logic_error("Operation other than Plus (+) are not supported");

    // here we just ignore unused operands
    return a + b;
}

IOperation::Arity PlusOp::getArity() const
{
    return arDue;
}

//==============================================================================
// class InverOp
//==============================================================================
    int InverOp::operation(char op, int a, int /*b*/, int /*c*/) {
        if(op != '~')
            throw std::logic_error("Operation other than Inver (~) are not supported");

        // here we just ignore unused operands
        return ~a;
    }

    IOperation::Arity InverOp::getArity() const {
        return arUno;
    }

//==============================================================================
// class AndOp
//==============================================================================
    int AndOp::operation(char op, int a, int b, int /*c*/) {
        if(op != '&')
            throw std::logic_error("Operation other than And (&) are not supported");

        // here we just ignore unused operands
        return a&b;
    }

    IOperation::Arity AndOp::getArity() const {
        return arDue;
    }

//==============================================================================
// class PowOp
//==============================================================================
    int PowOp::operation(char op, int a, int b, int /*c*/) {
        if(op != '^')
            throw std::logic_error("Operation other than Pow (^) are not supported");

        // here we just ignore unused operands
        int pow = 1;
        for (int i = 0; i < b; ++i) {
            pow *= a;
        }
        return pow;
    }

    IOperation::Arity PowOp::getArity() const {
        return arDue;
    }

//==============================================================================
// class StackMachine
//==============================================================================

void StackMachine::registerOperation(char symb, xi::IOperation *oper) {
    SymbolToOperMapConstIter it = _opers.find(symb);
    if (it != _opers.end())
        throw std::logic_error("An operation if already reg...");
    _opers[symb] = oper;

}
IOperation* StackMachine::getOperation(char symb) {
    SymbolToOperMapConstIter it = _opers.find(symb);
    if (it == _opers.end())
        return nullptr;
    return _opers[symb];
}
int StackMachine::calculate(const std::string &expr, bool clearStack) {
    if (clearStack)
        _s.clear();
    std::vector<std::string> tokens = getTokens(expr);
    for (const auto &item : tokens) {
        if (isOperation(item)){
            if (item[0] != '+' && item[0] != '^' && item[0] != '&' && item[0] != '~')
                throw std::logic_error("The operation is not found");
            IOperation* op = getOperation(item[0]);
            int a;
            int b;
            int c;
            int res;
            switch (op->getArity()){
                case IOperation::Arity ::arUno:a = _s.pop(); res = op->operation(item[0],a); break;
                case IOperation::Arity ::arDue:b = _s.pop(); a = _s.pop(); res = op->operation(item[0],a,b); break;
                case IOperation::Arity ::arTre:c = _s.pop(); b = _s.pop(); a = _s.pop(); res = op->operation(item[0],a,b,c); break;
            }
            _s.push(res);
        }else
            if(isNumber(item)){
                _s.push(std::stoi(item));
            } else
                throw std::logic_error("Can't determine symbol");

    }
    return _s.top();
}
// TODO: put StackMachine methods implementation here


} // namespace xi
