#include <iostream>
using namespace std;

long int fib(int n){

    if(n == 0 || n == 1){
        return 1;
    }
    else{
        return fib(n-1) + fib(n-2);
    }
}

int main(){

    int number;
    cin>> number;

    long int res = fib(number);

    cout << res << endl;

return 0;

}