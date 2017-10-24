//
// Created by acid on 2017/10/23.
//
#define VC vector<pair<float, float>>
#define PR pair<float, float>
#include <iostream>
#include <vector>
#include <omp.h>
#include <fstream>
#include <tuple>
#include <sstream>


using namespace std;

int main(){

    VC one,two,three,four,five,six,seven,eight;

    VC allData;
    ifstream infile("data2.txt");

    for (int j = 0; j < 3000; ++j) {
        float x, y, ignore;
        infile >> x;
        infile >> y;
        infile >> ignore;
        PR toAdd(x,y);
        allData.push_back(toAdd);
    }

    omp_set_num_threads(8);
    #pragma omp parallel
    {
        #pragma omp for schedule(static) nowait
        for (unsigned int i=0; i < allData.size(); i++) {

            if(omp_get_thread_num() == 0)
                one.push_back(allData[i]);
            if(omp_get_thread_num() == 1)
                two.push_back(allData[i]);
            if(omp_get_thread_num() == 2)
                three.push_back(allData[i]);
            if(omp_get_thread_num() == 3)
                four.push_back(allData[i]);

            if(omp_get_thread_num() == 4)
                five.push_back(allData[i]);
            if(omp_get_thread_num() == 5)
                six.push_back(allData[i]);
            if(omp_get_thread_num() == 6)
                seven.push_back(allData[i]);
            if(omp_get_thread_num() == 7)
                eight.push_back(allData[i]);
        }
    }

    printf("%lu,\t%lu,\t%lu,\t%lu,\t%lu,\t%lu,\t%lu,\t%lu\n", one.size(),two.size(),three.size(),four.size(),five.size(),six.size(),seven.size(),eight.size());
}