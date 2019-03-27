#include <iostream>
#include <map>
#include <tuple>
#include <algorithm>
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

void get_potential_splits(std::vector<float> feature_column,const std::vector<std::string> labels){
    //get unique label values
    // std::vector<std::string> unique_labels_vec;
    // unique_labels_vec = labels;
    // std::vector<std::string>::iterator it;
    // it = std::unique(unique_labels_vec.begin(), unique_labels_vec.end());
    // unique_labels_vec.resize(std::distance(unique_labels_vec.begin(),it));
    // std::cout<<'\n';
    // std::cout<<"distance : "<<std::distance(labels.begin(), find(labels.begin(), labels.end(),"versicolor"))<<'\n';
    std::vector<float> potential_splits;
    for(auto i=1;i<feature_column.size();i++){
        potential_splits.push_back((feature_column.at(i)+feature_column.at(i-1))/2);
    }
    // for(auto split:potential_splits){
    //     std::cout<<split<<" ";
    // }
    // std::cout<<'\n';
    // return potential_splits
}

std::tuple<std::vector<float>,std::vector<float>> split_data(std::vector<float> column_to_split,float split_value){
    std::vector<float> data_below;
    std::vector<float> data_above;
    for(auto element:column_to_split){
        if(element>=split_value){
            data_above.push_back(element);
        }
        else{
            data_below.push_back(element);
        }
    }

    return std::make_tuple(data_below,data_above);

}

int main()
{
    data_handler *iris = new data_handler(151,"iris/iris.csv");
    std::cout<<iris->get_sepal_length().at(4)<<'\n';
    get_potential_splits(iris->get_sepal_length(),iris->get_species());
    std::tuple<std::vector<float>,std::vector<float>> tuple_= split_data(iris->get_sepal_length(),5.);
    printf("HELLO.\n");
}
