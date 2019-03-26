#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <data.hpp>



class data_handler{
    std::vector<data *> *training_data;
    int number_rows;
    
    public:
    data_handler(int,const std::string);
    int get_sepal_length();
    ~data_handler();



};