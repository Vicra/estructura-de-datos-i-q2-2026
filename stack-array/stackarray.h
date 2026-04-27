#ifndef STACKARRAY_H
#define STACKARRAY_H

class StackArray
{
public:
    // properties
    int stack[100];
    int size;

    // operations
    // fn de insertar
    void push(int x);

    // fn de eliminar
    int pop();

    void print();

    // fn mostrar el siguiente (top)
    void peek();

    StackArray();
};

#endif // STACKARRAY_H
