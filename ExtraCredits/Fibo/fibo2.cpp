#include <iostream>
#include <vector>
using namespace std;

long int fib(int n){

    if(n == 0 || n == 1){
        return 1;
    }

    vector<long int> v(n+1);
    v[0] = v[1] = 1;
    
    for (size_t i = 2; i <= n; i++)
    {
        v[i]= v[i-1]+ v[i-2];
    }

    return v[n];
    
    


}

int main(){

    int number;
    cin>> number;


    long int res = fib(number);

    cout << res << endl;

    
 

return 0;

}