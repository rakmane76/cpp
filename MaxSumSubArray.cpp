/*
* Using DP and Kadane's algo to find max sum of subarray from given array of int. 
*  Refer to Kadane : https://www.youtube.com/watch?v=VMtyGnNcdPw
*  Also refer :  https://www.youtube.com/watch?v=w_KEocd__20
*
*  For DP alternative to solve, tried same usual 2D array approach.. 
*  Down and Right axis are sum values of array for that index range. eg. matrix(1,4) represent sum of arr[1] ... arr[4] 
*  Set diagonal values as same value of arr at that index.  eg. matrx[0][0] = arr[i] etc..
*  Then value at each matrix element from 1.. size of array can be computed as 
*  sum of subarray greater than size 1, is sum of its previous matrix column  and next matrix row, then subtract sum from previous diagonal matrix. 
*  Eg. matrix[1][3] = matrix[1][2] + matrix[2][3] - matrix[2][2]
*/

#include<iostream>
#include<vector>

using namespace std;

vector<int> GetMaxSumSubArrDP(vector<int> &arr){
    vector<int> result(3,0); 
    int sum=0, left =0, right=0, size = arr.size();
    
    vector<vector<int>> matrix(size, vector<int>(size,0));  // create 2d matrix of size n x n  .. Initialize to 0.. 
    for (int i =0; i < size; i++) { // fill diagonal with array index value.. 
        matrix[i][i] = arr[i];
        if ( arr[i] > sum ) { sum = arr[i], left = right = i; } // if sum at matrix is greater than previous max sum, then update
    }

    for ( int i = 0 ; i < size; i++ ) { // fill rest of matrix...
        for ( int l = 0, r = i+1; r < size; l++, r++){
            matrix[l][r] = matrix[l][r-1] + matrix[l+1][r] - matrix[l+1][r-1];
            if ( matrix[l][r] > sum ) { sum = matrix[l][r]; left = l; right = r; }  // if sum at matrix is greater than previous max sum, then update
        }
    }
    result[0] = sum; result[1] = left; result[2] = right;
    return result;
}

vector<int> GetMaxSumSubArrKadane(vector<int> &arr){
    vector<int> result(3,0); 
    int currentSum=arr[0], overAllSum = arr[0], left = 0, right=0, size = arr.size();
    int overallLeft = 0, overallRight = 0;
    
    for (int i = 1; i < size; i++) { 
        if (currentSum < 0) { currentSum = arr[i]; left = i; right = i;}
        else { currentSum += arr[i]; right = i;}

        if ( currentSum > overAllSum ) { overAllSum = currentSum; overallLeft = left; overallRight = right;}      
    }
    
    result[0] = overAllSum; result[1] = overallLeft; result[2] = overallRight;
    return result;
}

int main(){
    vector<int> arr {4, 3, -2, 6, 7, -10, -10, 4, 5, 9, -3, 4, 7, -28, 2, 9, 3, 2, 11};

    vector<int> result = GetMaxSumSubArrDP(arr);
    cout << "Res :" << result[0] << ", left:" << result[1] << ", right:" << result[2] << endl;
    
    result = GetMaxSumSubArrKadane(arr);
    cout << "Res :" << result[0] << ", left:" << result[1] << ", right:" << result[2] << endl;
    
    return 0;
}