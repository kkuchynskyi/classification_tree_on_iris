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
//++++
float vector_mean_last_columns(const std::vector<std::vector<float>>& data){
    if(data.size()==0){
        std::cout<<"Error in 'vector_mean_last_columns'.Data provided to this function is empty()."<<std::endl;
        //return;
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
        float mean_value = vector_mean_last_columns(data);
        for(int i =0;i<data.size();i++){
            sum+=std::pow(data[i][index_of_last_column] - mean_value,2);
        }
        return sum/data.size();

    }
}



// float mse(const std::vector<float>& column){
//     float sum = 0;
//     float column_mean = vector_mean(column);
//     std::cout<<"mean : "<<column_mean<<std::endl;
//     for(auto i:column){
//         sum += std::pow(i-column_mean,2);
//     }
//     return sum/column.size();
// }

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
