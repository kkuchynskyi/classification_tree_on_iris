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


float mean_last_column(const std::vector<std::vector<float>>& data){
    if(data.size()==0){
        std::cout<<"Error in 'vector_mean_last_columns'.Data provided to this function is empty()."<<std::endl;
    }
    else{
        int index_of_last_column = data[0].size()-1;
        float sum = 0;
        for(int i=0;i<data.size();i++){
            sum+=data[i][index_of_last_column];
        }
        return sum/data.size();
    }
    
}

float mse(const std::vector<std::vector<float>>& data){
    if(data.size()==0){
        std::cout<<"Error in 'squared_error'.Data provided to this function is empty()."<<std::endl;
        //return;
    }
    else{
        int index_of_last_column = data[0].size() -1;
        float sum = 0;
        float mean_value = mean_last_column(data);
        for(int i =0;i<data.size();i++){
            sum+=std::pow(data[i][index_of_last_column] - mean_value,2);
        }
        return sum/data.size();

    }
}




void stack_X_and_Y(vec2d<float>& a,std::vector<float> b){
    if(a.size()==b.size()){
        for(int i=0;i<a.size();i++){
            a[i].push_back(b[i]);
        }

    }
}

float mean_by_column(std::vector<std::vector<float>> const  &column,int index_column){
    float sum = 0;
    int count = 0;
    
    for(auto &i : column){
        sum+=i[index_column];
        count++;
    }
    return sum/count;
}


bool compare_for_sort(std::vector<float> i,std::vector<float> j){
    return (i.at(column_to_be_sort_glob) > j.at(column_to_be_sort_glob));
}

std::vector<std::vector<float>> sort_by_feature(std::vector<std::vector<float>>& X_to_sort, int feature_index){
    column_to_be_sort_glob = feature_index;
    sort(X_to_sort.begin(),X_to_sort.end(),compare_for_sort);
    return X_to_sort;
}

float error(std::vector<float> a,std::vector<float> b){
    if(a.size()==b.size()){
        float s = 0;
        for(int i=0;i<a.size();i++){
            s+=std::pow(a[i] -b[i],2);
        }
        return s;
    }
    else{
        std::cout<<"ERROR IN error"<<std::endl;
    }
}

#endif
