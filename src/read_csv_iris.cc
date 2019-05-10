#include <iostream>
#include <algorithm>
#include "dataset.hpp"
//using namespace std;



ReadCsvIris::ReadCsvIris(int number_of_rows,const std::string path_to_file){

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



std::vector<std::vector<float>> ReadCsvIris::get_data(){
    std::vector<std::vector<float>> data;
    data.push_back(this->sepal_length_vec);
    data.push_back(this->sepal_width_vec);
    data.push_back(this->petal_length_vec);
    data.push_back(this->petal_width_vec);
    return data;
}




ReadCsvBikes::ReadCsvBikes(int number_of_rows,int number_of_columns,const std::string path_to_file){

    this->number_rows = number_of_rows;
    this->number_columns = number_of_columns;

    std::ifstream file(path_to_file);

    if(!file.is_open()) std::cout<< "ERROR: File Open"<<"\n";

    std::string el1;
    std::string el2;
    std::string el3;
    std::string el4;
    std::string el5;
    std::string el6;
    std::string el_target;


    for(auto i=0;i<number_of_rows;i++){
        getline(file,el1,',');
        //std::cout<<"el1 :"<<el1<<" ";
        getline(file,el2,',');
        getline(file,el3,',');
        getline(file,el4,',');
        getline(file,el5,',');
        getline(file,el6,',');
        getline(file,el_target,'\n');
        //std::cout<<"el_target :"<<el_target<<" ";
        if(i!=0){
            std::vector<float> tmp;
            tmp.push_back(std::stof(el1));
            tmp.push_back(std::stof(el2));
            tmp.push_back(std::stof(el3));
            tmp.push_back(std::stof(el4));
            tmp.push_back(std::stof(el5));
            tmp.push_back(std::stof(el6));
            tmp.push_back(std::stof(el_target));
            X.push_back(tmp);
        }
    }



    file.close();
}

// std::vector<std::vector<float>> ReadCsvBikes::sort_by_column(int index){
//     std::vector<std::vector<float>> X_copy = this->X;
//     column_to_be_sort_glob = index;
//     sort(X_copy.begin(),X_copy.end(),compare_for_sort);
//     return X_copy;
// }
