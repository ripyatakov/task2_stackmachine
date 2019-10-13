////////////////////////////////////////////////////////////////////////////////
// Module Name:  int_stack.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include <stdexcept>
#include "int_stack.h"

// TODO: add necessary headers here
// #include <...

namespace xi {

// TODO: add method definitions here

    IntStack::IntStack(size_t sz) {
        _ssize = sz;
        _stack = new int[_ssize];
        _head = 0;

    }

    void IntStack::push(int el) {
        if (_head == _ssize)
            throw std::logic_error("Stack is overflow");
        _stack[_head++] = el;
    }

    int IntStack::pop() {
        if (_head == 0)
            throw std::logic_error("Stack is empty");
        return _stack[--_head];
    }

    int IntStack::top() {
        if (_head == 0)
            throw std::logic_error("Stack is empty");
        return _stack[_head-1];
    }

    void IntStack::clear() {
        _head = 0;
    }

    bool IntStack::isEmpty() const {
        return (_head == 0);
    }

    bool IntStack::isFull() const {
        return (_head >= _ssize);
    }

    IntStack::~IntStack() {
        delete[] _stack;
    }
} // namespace xi

