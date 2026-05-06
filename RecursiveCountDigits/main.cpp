#include <iostream>
using std::cout;
using std::endl;

int countDigits(int x, int cont){
    // caso base
    if(x<10) {
        return cont;
    } else {
        return cont + countDigits(x/10, cont);
    }
}

int countDigits2(int x){
    if(x<10) return 1;
    else return 1 + countDigits2(x/10);
}

int main(){
    cout << "Digit count 4: " << countDigits(4, 1) << endl;
    cout << "Digit count 45: " << countDigits(45, 1) << endl;
    cout << "Digit count 456: " << countDigits(456, 1) << endl;
    cout << "Digit count 4567: " << countDigits(4567, 1) << endl;

    cout << "Digit count 4: " << countDigits2(4) << endl;
    cout << "Digit count 45: " << countDigits2(45) << endl;
    cout << "Digit count 456: " << countDigits2(456) << endl;
    cout << "Digit count 4567: " << countDigits2(4567) << endl;
    return 0;
}
