#include <iostream>
#include <array>
#include <map>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include "read_csv_iris.hpp"



bool check_purity(std::vector<std::string> labels){
    // get unique label values
    std::vector<std::string> unique_labels_vec;
    unique_labels_vec = labels;
    std::vector<std::string>::iterator it;
    it = std::unique(unique_labels_vec.begin(), unique_labels_vec.end());
    unique_labels_vec.resize(std::distance(unique_labels_vec.begin(),it));
    if(unique_labels_vec.size()==1){
        return true;
    }
    else{
        return false;
    }
}

std::string classify_data(std::vector<std::string> labels){
    std::vector<std::string> unique_labels_vec;
    unique_labels_vec = labels;
    std::vector<std::string>::iterator it;
    it = std::unique(unique_labels_vec.begin(), unique_labels_vec.end());
    unique_labels_vec.resize(std::distance(unique_labels_vec.begin(),it));
    std::string classification;
    int count;
    int max_count = 0;
    for(auto unique_value_index=0;unique_value_index<unique_labels_vec.size();unique_value_index++){
        count=0;
        for(auto i=0;i<labels.size();i++){
            if(labels.at(i)==unique_labels_vec.at(unique_value_index)){
                count+=1;
            }
        }
        if(count>max_count){
            max_count = count;
            classification = unique_labels_vec.at(unique_value_index);
        }
    }
    return classification;
}

std::map<int,std::vector<float>> get_potential_splits(std::vector<std::vector<float>> data,const std::vector<std::string> labels){
    std::map<int,std::vector<float>> potential_splits;
    for(auto column_index=0;column_index<data.size();column_index++){
        
        std::vector<float> potential_splits_per_column;
        std::vector<float> unique_features_vec;
        unique_features_vec = data.at(column_index);
        std::vector<float>::iterator it;
        it = std::unique(unique_features_vec.begin(), unique_features_vec.end());
        unique_features_vec.resize(std::distance(unique_features_vec.begin(),it));
        std::sort(unique_features_vec.begin(),unique_features_vec.end());
        for(auto i=1;i<data.at(column_index).size();i++){
            potential_splits_per_column.push_back((data.at(column_index).at(i)+data.at(column_index).at(i-1))/2);
        }
        potential_splits[column_index] = potential_splits_per_column;


    }
    return potential_splits;
}

std::tuple<std::vector<std::vector<float>>,std::vector<std::vector<float>>,std::vector<std::string>,std::vector<std::string>> \
 split_data(std::vector<std::vector<float>> data,std::vector<std::string> labels,float split_value,int column_index){
    std::vector<std::vector<float>> data_below;
    std::vector<std::vector<float>> data_above;
    std::vector<std::string> labels_below;
    std::vector<std::string> labels_above;

    int first_visit_checker1 = 0;
    int first_visit_checker2 = 0;

    for(auto i=0;i<data.at(column_index).size();i++){
        if(data.at(column_index).at(i)>split_value){
            if(first_visit_checker1==0){
                for(auto j=0;j<data.size();j++){
                    std::vector<float> column1;
                    column1.push_back(data.at(j).at(i));
                    data_above.push_back(column1);
                }
                labels_above.push_back(labels.at(i));
                first_visit_checker1++;
            }
            else{
                for(auto j=0;j<data.size();j++){
                    data_above.at(j).push_back(data.at(j).at(i));
                }
                labels_above.push_back(labels.at(i));
            }
                
        }
        else{
            if(first_visit_checker2==0){
                for(auto j=0;j<data.size();j++){
                    std::vector<float> column2;
                    column2.push_back(data.at(j).at(i));
                    data_below.push_back(column2);
                }
                labels_below.push_back(labels.at(i));
                first_visit_checker2+=1;
            }
            else{
                for(auto j=0;j<data.size();j++){
                    data_below.at(j).push_back(data.at(j).at(i));
                }
                labels_below.push_back(labels.at(i));
            }     
        }
    }

    return std::make_tuple(data_below,data_above,labels_below,labels_above);

}

float calculate_entropy(std::vector<float> feature_column,std::vector<std::string> labels){
    // get unique label values
    std::vector<std::string> unique_labels_vec;
    unique_labels_vec = labels;
    std::vector<std::string>::iterator it;
    it = std::unique(unique_labels_vec.begin(), unique_labels_vec.end());
    unique_labels_vec.resize(std::distance(unique_labels_vec.begin(),it));
    std::vector<float> unique_counts;
    for(auto unique_value_index=0;unique_value_index<unique_labels_vec.size();unique_value_index++){
        unique_counts.push_back(0);
        for(auto i=0;i<labels.size();i++){
            if(labels.at(i)==unique_labels_vec.at(unique_value_index)){
                unique_counts.at(unique_value_index)+=1;
            }
        }
    }
    float sum_of_elements = 0;
    std::for_each( unique_counts.begin(), unique_counts.end(), [&](float & x)
    { sum_of_elements-=(x/labels.size())*log2(x/labels.size()); });

    return sum_of_elements;
}

float calculate_overall_entropy(std::vector<float> data_below,std::vector<float> data_above,std::vector<std::string> labels_below,std::vector<std::string> labels_above){
    float probability_below = (float)data_below.size()/(float)(data_below.size() + data_above.size());
    float probability_above = 1 - probability_below;
 
    float overall_entropy = (probability_above*calculate_entropy(data_above,labels_above) \
    +probability_below*calculate_entropy(data_below,labels_below));
    return overall_entropy;
}
std::tuple<int,float> determine_best_split(std::vector<std::vector<float>> data,const std::vector<std::string> labels,std::map<int,std::vector<float>> potential_splits){
    float overall_entropy = 999;
    float current_overall_entropy;
    int best_split_column;
    float best_split_value;

    std::tuple<std::vector<std::vector<float>>,std::vector<std::vector<float>>,std::vector<std::string>,std::vector<std::string>> tuple_;
    std::vector<std::vector<float>> data_below;
    std::vector<std::vector<float>> data_above = std::get<1>(tuple_);
    std::vector<std::string> labels_below = std::get<2>(tuple_);
    std::vector<std::string> labels_above = std::get<3>(tuple_);
    for (auto const& x : potential_splits){
        for(auto j=0;j<x.second.size();j++){
            tuple_  = split_data(data,labels,x.second.at(j),x.first);
            data_below = std::get<0>(tuple_);
            data_above = std::get<1>(tuple_);
            labels_below = std::get<2>(tuple_);
            labels_above = std::get<3>(tuple_);
            if (data_above.size()!=0 && data_below.size()!=0){
                current_overall_entropy = calculate_overall_entropy(data_below.at(x.first),data_above.at(x.first),labels_below,labels_above);
                if (current_overall_entropy<overall_entropy){
                    overall_entropy=current_overall_entropy;
                    best_split_column = x.first;
                    best_split_value = x.second.at(j);
                }

            }
        }
    }


    return std::make_tuple(best_split_column,best_split_value);
}

void decision_tree_algorithm(std::vector<std::vector<float>> data,std::vector<std::string> labels,int counter){
    
    if (check_purity(labels)){
        std::string classification = classify_data(labels);
        std::cout<<"FINISH!"<<std::endl;;
    }
    //recursive part
    else{
        counter+=1;
        std::map<int,std::vector<float>> potential_splits = get_potential_splits(data,labels);
        std::tuple<int,float> tuple_ = determine_best_split(data,labels,potential_splits);
        int column_to_split = std::get<0>(tuple_);
        float split_value = std::get<1>(tuple_);
        std::cout<<std::endl;
        std::cout<<"COUNT:"<<counter<<". Column to split: "<<column_to_split<<". Split value: "<<split_value<<std::endl;
        std::tuple<std::vector<std::vector<float>>,std::vector<std::vector<float>>,std::vector<std::string>,std::vector<std::string>> splitted_data =  split_data(data,labels,split_value,column_to_split);
        std::vector<std::vector<float>> data_below = std::get<0>(splitted_data);
        std::vector<std::vector<float>> data_above = std::get<1>(splitted_data);
        std::vector<std::string> labels_below = std::get<2>(splitted_data);
        std::vector<std::string> labels_above = std::get<3>(splitted_data);
        std::cout<<"Above"<<std::endl;
        decision_tree_algorithm(data_above,labels_above,counter);
        std::cout<<"Below"<<std::endl;
        decision_tree_algorithm(data_below,labels_below,counter);


    }
}



int main()
{   
    //read csv
    ReadCsvIris *iris = new ReadCsvIris(151,"iris/iris.csv");
    decision_tree_algorithm(iris->get_data(),iris->get_species(),0);

}



