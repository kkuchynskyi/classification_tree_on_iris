#include <iostream>
#include <array>
#include <map>
#include <tuple>
#include <algorithm>
#include <cmath>
#include "data_handler.hpp"
// #include "decision_tree_functions.cc"


data_handler::data_handler(int number_of_rows,const std::string path_to_file){

    this->number_rows = number_of_rows;

    std::ifstream file(path_to_file);

    if(!file.is_open()) std::cout<< "ERROR: File Open"<<"\n";

    std::string sepal_length;
    std::string sepal_width;
    std::string petal_length;
    std::string petal_width;
    std::string species;

    for(auto i=0;i<number_rows;i++){
        getline(file,sepal_length,',');
        getline(file,sepal_width,',');
        getline(file,petal_length,',');
        getline(file,petal_width,',');
        getline(file,species,'\n');
        if(i!=0){
            sepal_length_vec.push_back(std::stof(sepal_length));
            sepal_width_vec.push_back(std::stof(sepal_width));
            petal_length_vec.push_back(std::stof(petal_length));
            petal_width_vec.push_back(std::stof(petal_width));
            species_vec.push_back(species);
        }
    }


    file.close();
}

std::map<int,std::vector<float>> get_potential_splits(std::vector<std::vector<float>> data,const std::vector<std::string> labels){
    std::map<int,std::vector<float>> potential_splits;
    for(auto column_index=0;column_index<data.size();column_index++){
        
        std::vector<float> potential_splits_per_column;

        for(auto i=1;i<data.at(column_index).size();i++){
            potential_splits_per_column.push_back((data.at(column_index).at(i)+data.at(column_index).at(i-1))/2);
        }
        potential_splits[column_index] = potential_splits_per_column;
    }

    return potential_splits;
}

std::tuple<std::vector<float>,std::vector<float>,std::vector<std::string>,std::vector<std::string>> \
 split_data(std::vector<float> column_to_split,std::vector<std::string> labels,float split_value){
    
    
    std::vector<float> data_below;
    std::vector<float> data_above;
    std::vector<std::string> labels_below;
    std::vector<std::string> labels_above;
    for(auto i=0;i<column_to_split.size();i++){
        if(column_to_split.at(i)>split_value){
            data_above.push_back(column_to_split.at(i));
            labels_above.push_back(labels.at(i));
        }
        else{
            data_below.push_back(column_to_split.at(i));
            labels_below.push_back(labels.at(i));        
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
    float probability_below = data_below.size()/(data_below.size() + data_above.size());
    float probability_above = 1 - probability_below;

    float overall_entropy = (probability_above*calculate_entropy(data_above,labels_above) \
    +probability_below*calculate_entropy(data_below,labels_below));
    return overall_entropy;
}

std::tuple<int,float> determine_best_split(std::vector<std::vector<float>> data,const std::vector<std::string> labels,std::map<int,std::vector<float>>){
    
}


int main()
{   
    //read csv
    data_handler *iris = new data_handler(151,"iris/iris.csv");
    //potential splits
    std::map<int,std::vector<float>> splits= get_potential_splits(iris->get_data(),iris->get_species());

    //split feature column by value
    float split_value = 1.05;
    std::tuple<std::vector<float>,std::vector<float>,std::vector<std::string>,std::vector<std::string>> tuple_ = split_data(iris->get_petal_width(),iris->get_species(),split_value);
    std::vector<float> data_below = std::get<0>(tuple_);
    std::vector<float> data_above = std::get<1>(tuple_);
    std::vector<std::string> labels_below = std::get<2>(tuple_);
    std::vector<std::string> labels_above = std::get<3>(tuple_);

    std::cout<<'\n';
    float b = calculate_entropy(data_below,labels_below);
    std::cout<<b<<'\n';
    printf("HELLO.\n");
}
