#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include <algorithm>

int column_to_be_sort_glob;

float vector_mean(const std::vector<float>& column){

    return std::accumulate(column.begin(),column.end(),0.0)/column.size();
}
float mse(const std::vector<float>& column){
    float sum = 0;
    float column_mean = vector_mean(column);
    std::cout<<"mean : "<<column_mean<<std::endl;
    for(auto i:column){
        sum += std::pow(i-column_mean,2);
    }
    return sum/column.size();
}


float mean_by_column(std::vector<std::vector<float>> const  &column,int index_column){
    float sum = 0;
    int count = 0;
    //std::cout<<"i= ";
    for(auto &i : column){
        //std::cout<<i[index_column]<<" ";
        sum+=i[index_column];
        count++;
    }
    return sum/count;
}

float mse_for_pairs(std::vector<std::vector<float>> const &column,int index_column){
    float sum = 0;
    int count = 0;
    float column_mean = mean_by_column(column,index_column);
    //std::cout<<"ProblemHERE :"<<count<<" "<<column.size()<<std::endl;

    for(auto i:column){
        sum += std::pow(i[index_column]-column_mean,2);
        count++;
    }
    return count*(sum/count);
}

float mse_for_partition(std::vector<std::vector<float>> const& feature_target_pairs_left,
    std::vector<std::vector<float>> const& feature_target_pairs_right,int index_column){
    //std::cout<<"left.size() : "<<feature_target_pairs_left.size()<<std::endl;
    //std::cout<<"right.size() : "<<feature_target_pairs_right.size()<<std::endl;
    float a = mse_for_pairs(feature_target_pairs_left,index_column);
    //std::cout<<"fin"<<std::endl;
    float b = mse_for_pairs(feature_target_pairs_right,index_column);
    return a + b;
}


bool compare_for_sort(std::vector<float> i,std::vector<float> j){
    return (i.at(column_to_be_sort_glob) > j.at(column_to_be_sort_glob));
}

std::vector<std::vector<float>> sort_by_feature(std::vector<std::vector<float>>& X_to_sort, int feature_index){
    column_to_be_sort_glob = feature_index;
    sort(X_to_sort.begin(),X_to_sort.end(),compare_for_sort);
    return X_to_sort;
}


#endif
