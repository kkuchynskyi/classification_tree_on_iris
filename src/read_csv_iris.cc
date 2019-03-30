#include <iostream>
#include <algorithm>
#include "read_csv_iris.hpp"



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