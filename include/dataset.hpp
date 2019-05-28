#ifndef DATASET_H
#define DATASET_H
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
// #include <data.hpp>

class Dataset{
 public:
  virtual std::vector<std::vector<float>>& get_X() = 0;
  virtual std::vector<std::vector<float>>& get_X_Y() = 0;
  virtual std::vector<float>& get_Y() = 0;
  virtual int get_number_rows() = 0;
  virtual int get_number_columns() = 0;
  virtual std::vector<float> get_row_by_index(int) = 0;
};



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



class ReadCsvBikes : public Dataset {
 public:
  ReadCsvBikes(int,int,const std::string);
  std::vector<std::vector<float>>& get_X() override {
        return X; }
  std::vector<std::vector<float>>& get_X_Y () override  {
        return X_Y; }
  std::vector<float>& get_Y() override{
        return Y; }
  int get_number_rows() override{ return number_rows;};
  int get_number_columns() override{ return number_columns;};
  std::vector<float> get_row_by_index(int) override;
  std::vector<std::vector<float>> sort_by_column(int);

private:
  std::vector<std::vector<float>> X_Y;
  std::vector<std::vector<float>> X;
  std::vector<float> Y;

  int number_rows;
  int number_columns;
};
#endif
