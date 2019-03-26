#include "data_handler.hpp"
 
data_handler::data_handler(int number_of_rows,const std::string path_to_file){

    this->training_data = new std::vector<data *>;
    this->number_rows = number_of_rows;

    data *feature_row;
    std::ifstream file(path_to_file);

    if(!file.is_open()) std::cout<< "ERROR: File Open"<<"\n";

    std::string sepal_length;
    std::string sepal_width;
    std::string petal_length;
    std::string petal_width;
    std::string species;
    // int i = 0;
    for(auto i=0;i<number_rows;i++){
        getline(file,sepal_length,',');
        getline(file,sepal_width,',');
        getline(file,petal_length,',');
        getline(file,petal_width,',');
        getline(file,species,'\n');
        if(i!=0){
            feature_row = new data;
            feature_row->set_features(std::stof(sepal_length),std::stof(sepal_width),std::stof(petal_length),std::stof(petal_width),species);
            this->training_data->push_back(feature_row);
        }
    }


    file.close();
}

int data_handler::get_sepal_length(){

    std::vector<data*>::iterator iter;
    for (iter = (*this->training_data).begin(); iter != (*this->training_data).end(); ++iter){
        std::cout<<(*iter)->get_sepal_length();
    }
    
    return 5;
}

int main()
{   
    data_handler *iris = new data_handler(151,"iris/iris.csv");
    std::cout<<iris->get_sepal_length();

    printf("HELLO.\n");
}