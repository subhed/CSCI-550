#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){

    string S = "abcd";

    string SC = S;
    
    for (size_t i = 0; i <= S.length(); i++)
    {
        
            cout<<SC<<"\n";
            SC = S.substr(0,i+1);
                        // SC = SC.substr(1);


    }


    return 0;
}