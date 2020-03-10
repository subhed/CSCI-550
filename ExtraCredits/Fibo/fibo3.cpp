#include <iostream>
#include <vector>
using namespace std;

long int fib(int n){

    if(n == 0 || n == 1){
        return 1;
    }

    vector<long int> v(2);
    long int result;

    v[0] = v[1] = 1;
    
    for (size_t i = 2; i <= n; i++)
    {
        result = v[0]+ v[1];
        v[0] = v[1];
        v[1] = result;
    }

    return result;

}

int main(){

    int number;
    cin>> number;


    long int res = fib(number);

    cout << res << endl;

    
 

return 0;

}