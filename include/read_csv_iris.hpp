#ifndef READCSVIRIS_H
#define READCSVIRIS_H
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
// #include <data.hpp>



class ReadCsvIris{
 public:
  ReadCsvIris(int,const std::string);
  ~ReadCsvIris();
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
private:
  std::vector<float> sepal_length_vec;
  std::vector<float> sepal_width_vec;
  std::vector<float> petal_length_vec;
  std::vector<float> petal_width_vec;
  std::vector<std::string> species_vec;
  int number_rows;
};
#endif
