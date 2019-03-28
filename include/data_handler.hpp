#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
// #include <data.hpp>



class data_handler{
    std::vector<float> sepal_length_vec;
    std::vector<float> sepal_width_vec;
    std::vector<float> petal_length_vec;
    std::vector<float> petal_width_vec;
    std::vector<std::string> species_vec;
    int number_rows;

    public:
    data_handler(int,const std::string);

    std::vector<float> get_sepal_length(){
        return sepal_length_vec; }
    std::vector<float> get_sepal_width(){
        return sepal_width_vec; }
    std::vector<float> get_petal_length(){
        return petal_length_vec; }
    std::vector<float> get_petal_width(){
        return petal_width_vec; }
    std::vector<std::string> get_species(){
        return species_vec;
    }
    std::vector<std::vector<float>> get_data();




    ~data_handler();



};

std::vector<std::vector<float>> data_handler::get_data(){
    std::vector<std::vector<float>> data;
    data.push_back(this->sepal_length_vec);
    data.push_back(this->sepal_width_vec);
    data.push_back(this->petal_length_vec);
    data.push_back(this->petal_width_vec);
    return data;
}