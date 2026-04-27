#include "stackll.h"

int main(){
    StackLL ll;
    ll.push(3);
    ll.print();
    ll.push(2);
    ll.print();
    ll.push(1);
    ll.print();
    ll.pop();
    ll.print();
    ll.pop();
    ll.print();

    ll.clear();
    ll.print();

    return 0;
}
