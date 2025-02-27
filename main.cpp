#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <random>
using namespace std;
const long long n = 100000, num=1000;
int l=0,r=n-1;
pair<int,int> ans;
long long arr[n];
long long ran[num];
bool flag=false;

int main() {
    unsigned seed = 1000;
    std :: default_random_engine rng(seed );
    std :: uniform_int_distribution<unsigned> dstr (0 ,2*n);

    for (uint64_t i = 0;i<n;++i){
        arr[i]=i;
    }
    for (uint64_t i = 0;i<num;++i){
        ran[i]=dstr(rng); //random numbers
        //ran[i]=-1; //non-existing numbers
    }

    auto begin = chrono :: steady_clock ::now();

    for (uint64_t cnt=0; cnt<num-1;++cnt){
        /*flag = false; //quadratic search
        for (int i =0;i<n && !flag;++i){
            for (int j = i+1;j<n && !flag;++j){
                if (arr[i]+arr[j]==ran[cnt]){
                    ans.first = i;
                    ans.second = j;
                    flag = true;
                }
            }
        }*/

        l=0;r=n-1; //linear search
        while ((l!=r) && (arr[l]+arr[r]!=ran[cnt])){
            if (arr[l]+arr[r]>ran[cnt]) r--;
            else if (arr[l]+arr[r]<ran[cnt]) l++;
        }

    }
    auto end = std :: chrono :: steady_clock ::now();
    auto time_span = std :: chrono :: duration_cast<std :: chrono :: milliseconds >(end- begin );
    std :: cout << "\n\n";
    std :: cout << time_span.count() << std :: endl ;
    cout<<l<<" "<<r;

    return 0;
}
