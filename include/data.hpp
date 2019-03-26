#include <string>
#include <fstream>
#include <vector>

class data{
    float sepal_length;
    float sepal_width;
    float petal_length;
    float petal_width;
    std::string species;

    public:
    void set_features(float,float,float,float,std::string);
    float get_sepal_length(){
        return sepal_length;
    };


};

void data::set_features(float sepal_length,float sepal_width,float petal_length,float petal_width,std::string species)
{
    this->sepal_length = sepal_length;
    this->sepal_width = sepal_width;
    this->petal_length = petal_length;
    this->petal_width = petal_width;
    this->species = species;
}