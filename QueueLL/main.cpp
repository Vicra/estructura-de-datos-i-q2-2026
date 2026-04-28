#include "queue.h"
#include <iostream>
using std::cout;
using std::endl;
int main(){
    Queue q;
    q.enqueue(1);
    q.print();
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.print();

    cout << "Dequeued: " << q.dequeue() << endl;
    q.print();
    cout << "Dequeued: " << q.dequeue() << endl;
    q.print();
    cout << "Dequeued: " << q.dequeue() << endl;
    q.print();
    cout << "Dequeued: " << q.dequeue() << endl;
    q.print();
    cout << "Dequeued: " << q.dequeue() << endl;
    q.print();
    return 0;
}
