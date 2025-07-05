#include <iostream>
#include <vector>


 using namespace std;


// vector<int>LIS(int i, int *array){
//     int lengt = 1;
//     for(int j = i+1; j< 20; j++){
//         if(array[j]> array[i]){
//             d = 
//         }
//     }
// }
int lis(vector<int> const& a) {
    int n = a.size();
    const int INF = 1e9;
    vector<int> d(n+1, INF);
    d[0] = -INF;

    for (int i = 0; i < n; i++) {
        for (int l = 1; l <= n; l++) {
            if (d[l-1] < a[i] && a[i] < d[l])
                d[l] = a[i];
        }
    }

    int ans = 0;
    for (int l = 0; l <= n; l++) {
        if (d[l] < INF)
            ans = l;
    }
    return ans;
}

int main (){
    int array[20] = {90,65,88,61,77,20,13,55,57,17,96,22,10,29,34,78,58,71,47,86};
    vector<int>arr(20);
    for(int i = 0; i< 20; i++){
        arr.push_back(arr[i]);
    }

    int ans = lis(arr);
    cout<< ans<<endl;



}

