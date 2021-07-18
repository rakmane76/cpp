/*

Bracket Combinations
Have the function BracketCombinations(num) read num which will be an integer greater than or equal to zero, 
and return the number of valid combinations that can be formed with num pairs of parentheses. 
For example, if the input is 3, then the possible combinations of 3 pairs of parenthesis, namely: ()()(), are ()()(), ()(()), (())(), ((())), and (()()). 
There are 5 total combinations when the input is 3, so your program should return 5.

Came up with formula to calculate the combination. 
It goes something like .. 
for N = 1 return 1
for N =2 return 3 
else for N > 2  = 1*S(N) + A*S(N-1) + B*S(N-2) + ... + X*S(3)
Here S(N) is summation N , N-1 ,... 2 . -> N + N-1 + N-2 + .. + 3 + 2 = (N(N+1)/2) - 1
A, B, C ,X are factors that need to be multiplied to summation N. 
Note Factors A will always be 1, and last factor X will always be equal to its previous factor W. X = W = X-1. 
To calculate factors start with N = 3  and it will have only 1 factor A = 1. 
Increment to next term 4, which will have 2 factors A, B . Here A = 1 , and last factor B = A , so B = 1 . 
Increment next term 5 , it will have 3 factors A =1, B, C=B . To calculate B, B = 4(A)+4(B) .. (Sum of factors of previous term = 4 until N-1)
Increment next term 6, it will have 4 factors A=1, B, C, D = C. B = (5(A)+5(B)) , C = (5(A) + 5(B) + 5(C))
Keep doing till you get all terms for factors. 
Then multiply by Summation S and sum to get results. Tested with actual for loop code .. it is matching. 

Also found another interesting observation.
above factors A,B,C,D from combination of coefficients starting with N=3
(1), (1,1), (1,2,2), (1,3,5,5), (1,4,9,14,14), (1,5,14,28,42,42) ...... please explanation above how it is calculated. 
This takes more time to compute than Catalan function written below. But again something different and interesting observation.
*/ 
#include <iostream>
#include <string>
#include<deque>
#include <chrono>
#include<vector>
#include<cstring>

using namespace std;

int countCombinations(int open, int close, string s){
  int count = 0;
  if ((open == 0) && (close == 0)) {
    //cout << s << endl;
    return 1;
  }
  
  if ( open > 0) { 
    count += countCombinations(open-1, close, s + "(");
    if (close > open){
      count += countCombinations(open, close-1, s + ")");
    }
  }
  else if(close > open){
    count += countCombinations(open, close-1, s + ")");
  }
  return count;
}

int BracketCombinations(int num) {
  string s;
  int result = countCombinations(num, num, s);
  return result;
}

void fillVector(deque<int> &v){
  if (v.empty()) {
     v.push_back(1);
     return;
  }
  
  int size = v.size();
  for ( int i=1; i <= size-1; i++) v[i] += v[i-1];
  v.push_back(v[size-1]);
}

int Summation (int i){
  int sum = (i*(i+1))/2 ;
  sum--;
  return sum;
}

int Calc(deque<int> &v, int &n){
  int size = v.size();
  int sum = 0;
  for (int i=0; i < size; i++){
    sum += Summation(n-i) * v[i];
  }
  return sum;
}

int BracketCalc(int i){
  if ( i == 1 ) return 1;
  if ( i == 2 ) return 2;
  deque<int> v; 
  for ( int n = 3; n <= i ; n++){
    fillVector(v);
  }
  int s = Calc(v, i);
  return s;  
}

int Catalan(int n){
  if ( n == 1 ) return 1;
  if ( n == 2 ) return 2;
  
  vector<int> v(n+1, 0);
  v[0] = 1; 
  v[1] = 1;
  for ( int i = 2; i <= n; i++){
    int inside = i - 1;
    int outside = 0;
    while ( inside >= 0){
      v[i] += v[inside] * v[outside];
      inside--; outside++;
    }
  }
  return v[n];
}

int main(void) { 
  // keep this function call here
  int i;
  cin >> i;
  auto start = chrono::steady_clock::now();
//  cout << BracketCombinations(i);
  auto end = chrono::steady_clock::now();
/*  cout << "   : Time in microseconds: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
  
  cout << endl << "=====================" << endl;
*/
  start = chrono::steady_clock::now();
  cout << BracketCalc(i);
  end = chrono::steady_clock::now();
  cout << "   : Time in microseconds: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
  
  start = chrono::steady_clock::now();
  cout << Catalan(i);
  end = chrono::steady_clock::now();
  cout << "   : Time in microseconds: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
  
  return 0;
    
}
