#include "stackarray.h"
#include <iostream>

using std::cout;
using std::endl;

int main(){
    StackArray a;
    a.push(10);
    a.print();
    a.push(20);
    a.print();
    a.pop();
    a.print();
    a.push(30);
    a.print();
    a.peek();
    a.peek();
    a.peek();
    return 0;
}
