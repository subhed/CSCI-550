// Memorization

#include <iostream>
#include <vector>

using namespace std;

long int fib(int n, vector<long int> &v){

    if(n == 0){
        
        if(v[0] == 0){
        v[0] = 1;
        return v[0];
        }
        else if(n == 1)
        {
            if(v[1]==0)
                v[1] = 1;

            return v[1];
        }
        if(v[n]>0)
            return v[n];
        
        v[n] = fib(n-1, v) + fib(n-2, v);
        return v[n];
    
    }
   
}

int main(){

    int number;
    cin>> number;

    vector<long int> v(number+1, 0);

    long int res = fib(number, v);

    cout << res << endl;

return 0;

}