/* 
* Problems related to Palindrome using Dynamic Programming.. 
* For explanation check : https://www.youtube.com/watch?v=XmSOWnL6T_I&t=69s
* https://www.youtube.com/watch?v=WpYHNHofwjc&t=43s
*/

#include<iostream>
#include<string>
#include<vector>
using namespace std;

int CountPalindromes(string &s) {
    int size = s.size();
    vector<vector<unsigned int>> di(size, vector<unsigned int>(size,0)); // 2-dimensional vector to set according string palingdrome or not. 
    for (int i =0 ; i < size; i++) di[i][i] = 1 ; // all diagnols are single character and palindromes. set to true. 
    for (int i = 1; i < size; i++) if (s[i-1] == s[i] ) di[i-1][i] = 1; // length 2 characters set manually in 2D vec. 

    for (int cnt = 2; cnt < size; cnt++)  // traverse rest of 2D legit matrix  and set at correct index if string palindrome. 
        for (int L = 0, R = cnt; R < size; L++, R++)  // Start from matrix[0][2] until [0][size-1] this will cover whole input string
            if ( (s[L] == s[R]) && (di[L+1][R-1] == 1) ) di[L][R] = 1;  // first and last character are same and inside string is palindrome set current string. 
    
    int result = 0;
    for ( int i = 0; i < size; i++)
    for ( int j = 0; j < size; j++)
        if (di[i][j] == 1 )  result++;
    
    return result;
}


string LargestSubsetPalindromes(string &s) {
    int size = s.size();
    vector<vector<unsigned int>> di(size, vector<unsigned int>(size,0)); // 2-dimensional vector to set according string palingdrome or not. 
    for (int i =0 ; i < size; i++) di[i][i] = 1 ; // all diagnols are single character and palindromes. set to true. 
    for (int i = 1; i < size; i++) if (s[i-1] == s[i] ) di[i-1][i] = 1; // length 2 characters set manually in 2D vec. 

    for (int cnt = 2; cnt < size; cnt++)  // traverse rest of 2D legit matrix  and set at correct index if string palindrome. 
        for (int L = 0, R = cnt; R < size; L++, R++)  // Start from matrix[0][2] until [0][size-1] this will cover whole input string
            if ( (s[L] == s[R]) && (di[L+1][R-1] == 1) ) di[L][R] = 1;  // first and last character are same and inside string is palindrome set current string. 
    
    string result = {};
    for ( int i = 0; i < size; i++)
    for ( int j = 0; j < size; j++)
        if ((di[i][j] == 1) && result.size() < j-i+1) result = s.substr(i, j-i+1) ;
    
    return result;
}


int main(){
    string s = "abcabac";

    cout << CountPalindromes(s) << endl; 

    cout << LargestSubsetPalindromes(s) << endl; 
    
    return 0;
}
