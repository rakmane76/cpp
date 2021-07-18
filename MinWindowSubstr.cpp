
/* Min Window Substring

Have the function MinWindowSubstring(strArr) take the array of strings stored in strArr, which will contain only two strings, 
the first parameter being the string N and the second parameter being a string K of some characters, and your goal is to determine the smallest substring of N 
that contains all the characters in K. 
For example: if strArr is ["aaabaaddae", "aed"] then the smallest substring of N that contains the characters a, e, and d is "dae" located at the end of the string. 
So for this example your program should return the string dae.

Another example: if strArr is ["aabdccdbcacd", "aad"] then the smallest substring of N that contains all of the characters in K is "aabd" which is 
located at the beginning of the string. Both parameters will be strings ranging in length from 1 to 50 characters and all of K's characters will exist 
somewhere in the string N. Both strings will only contains lowercase alphabetic characters.
Examples
Input: {"ahffaksfajeeubsne", "jefaa"}
Output: aksfaje
Input: {"aaffhkksemckelloe", "fhea"}
Output: affhkkse

*/

#include <iostream>
#include <string>
#include<cstring>
#include<vector>
#include<set>

using namespace std;

string MinSubStr(string Arr[]){
    string input = Arr[0], cmp = Arr[1], res={};
    cout << "in : " << input << endl;
    cout << "cmp : " << cmp << endl;

    size_t first = input.find_first_of(cmp);
    size_t last = input.find_last_of(cmp);
    cout << " first : " << first << ", last :" << last << endl;

    size_t cmpSize = cmp.size();
    for ( size_t i = first; i <= last-cmpSize-1; i++ ){
        string cmpBkp(cmp);
        size_t b =i; 
        for (; b <= last - cmpSize - 1 ; b++){
            if ( cmpBkp.find_first_of(input[b]) != string::npos ) cmpBkp.erase(cmpBkp.find_first_of(input[b]),1);
            if (cmpBkp.empty()) break;
        }
        if ( cmpBkp.empty()){
            if ( (res.empty()) || (res.size() > b-i+1) ) res = input.substr(i, b-i+1);
        }
    }

    return res;
}

int main(void) { 
   
  // keep this function call here
  string A[] = {"ahffaksfajeeubsne", "jefaa"};
  //int arrLength = sizeof(A) / sizeof(*A);
  //cout << MinWindowSubstring(A, arrLength);
  cout << MinSubStr(A) << endl;
  string B[] = {"aabdccdbcacd", "aad"};
  cout << MinSubStr(B) << endl;
  string C[] = {"aaffhkksemckelloe", "fhea"};
  cout << MinSubStr(C) << endl;
  return 0;
    
}