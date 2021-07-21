
/* Min Window Substring

Refer : https://www.youtube.com/watch?v=e1HlptlipB0

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
#include<map>
#include <chrono>

using namespace std;

string MinSubStr(string Arr[]){ // this is not optimized code.. will take O(n*n) time.. 
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

struct MapInputStr{
    map<char, int> in{};
    void insert(char c) { 
        if(in.find(c) != in.end()) in[c] = in[c] + 1; 
        else in[c] = 1;
    }
    void del(char c) { in[c] = in[c] - 1;}
    bool operator < (const map<char,int> check) {
        bool flag = false;
        for ( const auto &k : check){
            if ( ( in.find(k.first) == in.end() ) || (in[k.first] < k.second) ) { flag = true;  break; }
        }
        return flag;
    }
};

string MinSubStr_DP(string Arr[]) {
    string input = Arr[0], cmp = Arr[1], result{};
    //cout << input << ", " << cmp << endl;
    map<char, int> cmpM, inM;
    //MapInputStr in_data;
    int cmpFreq =0, inFreq=0;
    for ( auto c : cmp ) { 
        if (cmpM.find(c) == cmpM.end()) cmpM[c] = 1;
        else cmpM[c] = cmpM[c] + 1;
        cmpFreq++; // get frequency count of cmp string
    }

    int left = 0, right = 0, size = input.size();
    int cmpSize = cmp.size();
    //for( const auto &k : cmpM ) { cout << k.first << ": " << k.second << " ||| "; } cout << endl;
    while (left <= (size - cmpSize)) {
        if ( right < size) {
            //in_data.insert(input[right++]);
            //for( const auto &k : in_data.in ) { cout << k.first << ": " << k.second << endl;}
            char c = input[right++];
            if ( inM.find(c) == inM.end() ) inM[c] = 1; else inM[c] = inM[c] + 1;
            
            if ( (cmpM.find(c) != cmpM.end()) && (cmpM[c] >= inM[c]) ) { 
                inFreq++; //cout <<" inFreq++ : " << inFreq << endl; 
                //for( const auto &k : inM ) { cout <<"Infre++ :" << k.first << ": " << k.second << " ||| "; } cout << endl;
            } 
        }
        while( inFreq >= cmpFreq ) { // !(in_data < cmpM) ) { // keep going left till you find substr
            //for( const auto &k : in_data.in ) { cout << k.first << ": " << k.second << " || "; } cout << endl;
            if ( result.empty() || (result.size() > (right-left)) )  result = input.substr(left, right-left);
            //cout << "left:" << left << " , right:" << right << ", res:" << result << endl;
            //in_data.del(input[left++]);
            char c = input[left++];
            inM[c] = inM[c] - 1;
            
            if ( (cmpM.find(c) != cmpM.end()) && (cmpM[c] > inM[c]) ) { 
                inFreq--; // cout << "Infre1-- " << inFreq << endl; 
                //for( const auto &k : inM ) { cout <<"Infre-- :" << k.first << ": " << k.second << " ||| " ; } cout << endl;
            }
        }
        //if ( (in_data < cmpM) && (right == size) ) break; 
        if( (inFreq < cmpFreq) && (right == size) ) break;
    }
    //cout << "RES : " << result << endl;
    return result;
}

int main(void) { 

  std::chrono::steady_clock::time_point start = chrono::steady_clock::now();
  std::chrono::steady_clock::time_point end = chrono::steady_clock::now();
  string A[] = {"ahffaksfajeeubsne", "jefaa"};
  start = chrono::steady_clock::now();
  cout << MinSubStr(A) << endl;
  end = chrono::steady_clock::now();
  cout << "   : Time in microseconds: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
  cout << MinSubStr_DP(A) << endl;
  string B[] = {"aabdccdbcacd", "aad"};
  cout << MinSubStr(B) << endl;
  cout << MinSubStr_DP(B) << endl;
  string C[] = {"aaffhkksemckelloe", "fhea"};
  cout << MinSubStr(C) << endl;
  cout << MinSubStr_DP(C) << endl;

  string D[] = {"adswappeltwdhfafewfhljp", "plhjwf"};
  start = chrono::steady_clock::now();
  cout << MinSubStr(D) << endl;
  end = chrono::steady_clock::now();
  cout << "   : Time in microseconds: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
  
  start = chrono::steady_clock::now();
  cout << MinSubStr_DP(D) << endl;
  end = chrono::steady_clock::now();
  cout << "   : Time in microseconds: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;

  return 0;
    
}