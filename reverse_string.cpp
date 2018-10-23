#include<string>
#include<iostream>
#include<stack>
#include<cctype>
#include<algorithm>

using namespace std;

string reverse_string(string &s){
    string res;
    stack<string> st;
    cout << s <<": ended here" << endl;
    cout <<"Length :" << s.length() << endl;
    auto n = s.begin();
    for(auto it = s.begin(); it != s.end() ; it = n){
        if (::isspace(*it))
            n = find_if_not(it, s.end(), ::isspace);
        else
            n = find_if(it, s.end(), ::isspace);
        
        st.push(string(it,n));
    }
    while(!st.empty()){
        res += st.top();
        st.pop();
    }
    cout <<"Reverse Length :" << res.length() << endl;
    return res;
}

int main(){
    cout << "Enter String:";
    //string s="       !!! 1234	Rakesh     working    on sample          test";
    string s;
    getline(cin, s);
    string p = reverse_string(s);
    cout <<p << ": ended here "<< endl;
    cout <<"=== another reverse ==" << endl;
    cout <<reverse_string(p) << ": ended here "<< endl;
    return 0;
}
