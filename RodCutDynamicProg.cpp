/*
* Given int N, length if rod, and array of int where value represent value of rod for that index length. 
* eg . [1,2,3,4] is Rod of length 4, having price, lenght combination as (1,1) , (2,2), (3,3), (4,4)
* We need to find the best value for the rod, such that we can break the rod into given size of index and get value as define in that index of array. 
* eg for above case , total length of rod = 4 . 
* if we sell the whole rod as single piece of length 4, its value will be arr[3] = 4 
* if we seel it at 4 pieces of length 1, its value will be a[0] + a[0] + a[0] + a[0] = 4. 
* similarly it can be broken to 2 pieces of lenght 2 , and total value will be a[1] + a[1] = 4 
* lastly it can be broken into 2 pieces of length 1 and 3 resp, to get total value a[0] + a[2] = 4 .
* so here the best value of rod is 4 , no matter how we disassemble the rod into.. 
* this problem can be solved with Dynamic programming.. 
*
* Refer : https://www.youtube.com/watch?v=eQuJb5gBkkc&t=130s 
*
* First add one more element 0, at beginning of input matrix for simplicity. so we move from index 1 to n. 
* Create Result array of same size as above n+1 and assign all 0 values. This array will represent best price 
* on the index for that index length. 
* You need to traverse input matrix from first element and calculate best prices for that index and store Best Price value in Result array. 
* Best price at index N is calculated by getting max of input[N-c] + BestPrice[c] where c goes from 1 to N
* After calculating Best Price for final n, return that as result   
*/

#include<iostream>
#include<vector> 

using namespace std;

int CalcMax_DP(int arr[], int &size){ // DP used, traverse only half loop of BestPrice Array to compute Best Price at any index.
    vector<int> v(size+1, 0);
    vector<int> res(size+1, 0);
    int bestVal;
    for (int i=1; i<=size; i++) v[i] = arr[i-1];
    
    for (int i=1; i <= size; i++){
        bestVal = 0; // reset bestVal for each iteration.
        for (int a=0, b=i; a <= b; a++, b--){ // here a is first index = 0 and b = last index in same array and comparison done till midway. 
            if ( (res[b] + res[a]) > bestVal ) bestVal = (res[b] + res[a]);
        }
        if (v[i] > bestVal) bestVal = v[i]; // make sure dont miss the Bestprice at input Array index N. 
        res[i] = bestVal;
    }
    
    return res[size];
}

int CalcMaxPriceSet(int arr[], int &size){ // Simple O(n*n) pattern... 
    vector<int> v(size+1, 0);
    vector<int> res(size+1, 0);
    int bestVal;
    for (int i=1; i<=size; i++) v[i] = arr[i-1];
    
    for (int i=1; i <= size; i++){
        bestVal = 0;
        for (int cnt=0; cnt < i; cnt++){
            if ( (v[i-cnt]+ res[cnt]) > bestVal ) bestVal = (v[i-cnt]+ res[cnt]);
        }
        res[i] = bestVal;
    }
    
    return res[size];
}

int main(){
    int arr[] = {1,5,8,9,10,17,17,20} ; // Prices of rod , where index is length of rod. 
    int size = 8;
    cout << CalcMaxPriceSet(arr, size) << endl;
    cout << CalcMax_DP(arr, size) << endl;
}