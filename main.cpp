#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <random>
using namespace std;
const long long n = 1600000, num=10000;
int l=0,r=n-1;
pair<int,int> ans;
long long arr[n];
long long countt[n];
long long ran[num];
bool flag=false;
uint64_t a,b = 0;

int main() {
    unsigned seed = 1000;
    std :: default_random_engine rng(seed );
    std :: uniform_int_distribution<unsigned> dstr (-1 ,n);
    binomial_distribution<unsigned> dstrr(n+1,0.5);

    for (uint64_t i = 0;i<n;++i){
        arr[i]=i;
        countt[i]=0;
    }
    for (uint64_t i = 0;i<num;++i){
        ran[i]=dstr(rng); //random numbers
        //ran[i]=-1; //non-existing numbers
        //ran[i]=dstrr(rng); //binomial-distributed numbers
    }

    auto begin = chrono :: steady_clock ::now();

    for (uint64_t cnt=0; cnt<num-1;++cnt){
        for (uint64_t i = 0;i<n;++i){ //A-strat
            if (arr[i]==ran[cnt]) {
                swap(arr[i],arr[0]);
                break;
            }
        }

        /*for (uint64_t i = 0;i<n;++i){ //B-strat
            if (arr[i]==ran[cnt] && i>0){
                swap(arr[i],arr[i-1]);
                break;
            }
            else if (arr[i]==ran[cnt]) break;
        }*/

        /*for (uint64_t i = 0;i<n;++i){ //C-strat
            if (arr[i]==ran[cnt]) {
                countt[i]++;
                if (i>0 && countt[i]>countt[i-1]){
                    swap(countt[i], countt[i-1]);
                    swap(arr[i],arr[i-1]);
                }
                break;
            }
        }*/

    }
    auto end = std :: chrono :: steady_clock ::now();
    auto time_span = std :: chrono :: duration_cast<std :: chrono :: milliseconds >(end- begin );
    std :: cout << "\n\n";
    std :: cout << time_span.count() << std :: endl ;

    return 0;
}
