#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <random>
using namespace std;
const long long n = 100, num=100000000ull;
int l=0,r=n-1,lr;
long long arr[n];
long long ran[num];
uint64_t a,b = 0;

int main() {
    unsigned seed = 1000;
    std :: default_random_engine rng(seed );
    std :: uniform_int_distribution<unsigned> dstr (0 ,n-1);

    for (uint64_t i = 0;i<n;++i){
        arr[i]=i;
    }
    for (uint64_t i = 0;i<num;++i){
        ran[i]=dstr(rng); //random numbers
        //ran[i]=-1; //non-existing numbers
    }

    auto begin = chrono :: steady_clock ::now();

    for (uint64_t cnt = num-1; cnt > 0;--cnt){

        l=0; r=n-1; //binary search
        while (r-l>1){
            lr=(r+l)/2;
            if (arr[lr]>ran[cnt]) r=lr;
            else l=lr;
        }
        if (arr[l]==ran[cnt]) a=l;
        else if (arr[r]==ran[cnt]) a=r;
        else a=-1;

        /*for (uint64_t i = 0;i<n;++i){ //linear search
            //b=dstr(rng );
            if (arr[i]==ran[cnt]) a = i;
        }*/
    }
    auto end = std :: chrono :: steady_clock ::now();
    auto time_span = std :: chrono :: duration_cast<std :: chrono :: milliseconds >(end- begin );
    std :: cout << "\n\n";
    std :: cout << time_span.count() << std :: endl ;

    return 0;
}
