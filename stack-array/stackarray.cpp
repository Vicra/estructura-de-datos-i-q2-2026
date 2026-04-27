#include "stackarray.h"
#include <iostream>

using std::cout;
using std::endl;

StackArray::StackArray() {
    size=0;
}

void StackArray::push(int x){
    this->stack[this->size] = x;
    this->size++;
}

int StackArray::pop(){
    return this->stack[size--];
}

void StackArray::print(){
    for(int i=0; i<size; i++){
        cout << stack[i] << ", ";
    }
    cout << "size:" << this->size << endl;
}

void StackArray::peek(){
    cout << "El que sigue es "
         << this->stack[this->size - 1]
         << endl;
    return;
}
