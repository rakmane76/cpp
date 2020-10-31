/*
* Puzzle, write function that takes 2 parameters. int and int(char)
* First parameter call Number, can be any digit number 
* Second parameter is single digit (0-9) 
* write function that will count times of digit is written 
* when you traverse from 1..Number in incremental order. 
* e.g Number = 51 , Digit 'd' = 4
* Function should print 6 , since traversing 1 to 51 , 4 comes in 4, 14, 24, 34, 44.
* Another eg. N = 103 , d = '7' , result = 20 . Values are 7, 17, 27, 37, 47, 57, 67, 70..77...79, 87, ,97 
*/

#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
#include <bits/stdc++.h> 
#include <chrono> 

using namespace std;

int countNo(int &, char &); // Simple traversing 1 to N and count d . Order(N)
int calcNo(int &, char &);
int countDig(int cnt, char &ch) ; // Formula use, order O(log(10))

int main(){
    int cnt = 0;
    cin >> cnt;

    char ch = '0';
    cin >> ch;

    int res = 0;
    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    res  = countNo(cnt, ch);
    auto end = chrono::high_resolution_clock::now();
    double time_taken =  
      chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    cout << " Res : " << res << ", time taken : " << fixed  << time_taken << setprecision(9) << endl; 


    start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    res = countDig(cnt, ch);
    end = chrono::high_resolution_clock::now();
    time_taken =  
      chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    cout << " Res : " << res << ", time taken : " << fixed  << time_taken << setprecision(9) << endl; 

    return 0;
}

int countNo(int & cnt, char &ch){
    int res = 0;
    string str;

    for ( int i = 1; i <= cnt; i++){
        str = to_string(i);
        if (count(str.begin(), str.end(), ch)){
            //cout << str << ", ";
            res += count(str.begin(), str.end(), ch);
        }
    }
    cout << endl;
    return res;
}

// Experimental function, but doesnt do correction if d = 0
int calcNo(int &cnt, char &ch){
    int res=0;

    int exp = (int)log10(cnt);
    string str = to_string(cnt);
    int numberToCount = atoi(string(1,ch).c_str());
    int n = 0, prevn=0;
    
    for (int i=0; i<=exp; i++){
        n = atoi(string(1,str[exp-i]).c_str());
        if ( i == 0) {
            if ( n >= numberToCount) res++;
            prevn = n;
            continue;
        }
        res += (n*i*((int)pow(10,i-1)));
        if ( n == numberToCount) 
            res += atoi(string(str, exp-i+1).c_str()) + 1;
        else if (n > numberToCount)
            res += (int)pow(10,i);
    }

    return res;
}


/*
* Here formula is used, p = log(N) to base 10.. 
* Result = Sum{ (n_i * 10^(i-1) *i) 
*              +
*            Mod(N,10^i) + 1 ... if n == d
*              +
*            10^i     .......... if n > d
*          } ....  for i from 1 .. p
*            -
*          Sum(10^i)  for i from 1..p  only if d == 0  // this is for correction.. 
*
*/
int countDig(int cnt, char &ch) {
    int numberToCount = atoi(string(1,ch).c_str());
    int exp = (int)log10(cnt);
    string str = to_string(cnt);
 
    int n=0;
    int res=0; /// final result. 
    
    for (int i=0; i<=exp; i++){
        n = atoi(string(1,str[exp-i]).c_str());
        res += (n *i *((int)pow(10,i-1)));
            if (n > numberToCount) res += (int)(pow(10,i));
            else if ( n == numberToCount)  res += (1 + (cnt%((int)pow(10,i))));
    }

    if (numberToCount == 0){
        int s = 0; 
        for ( int i = 0 ; i <=exp; i++) s += (int)pow(10,i);
        res -= s;
    }
    return res;
}
