#ifndef TREE_H
#define TREE_H
#include <vector>
#include <string>
#include <map>
#include <tuple>
#include <memory>
template<class T>
using vec2d = std::vector<std::vector<T>>;



struct NodeRegression{
  bool isLeaf = {0};
  float splitValue;
  float value;       // The data in this node.
  int splitColumn;
  std::shared_ptr<NodeRegression> left;   // Pointer to the left subtree.
  std::shared_ptr<NodeRegression> right;
};





class DecisionTreeRegressor {
  public:
   DecisionTreeRegressor(int i,int j): max_depth(i),min_sample_split(j){};
   void fit(vec2d<float> ,std::vector<float>) ;
   std::vector<float> predict(vec2d<float>);
  private:
   bool check_cv(vec2d<float>,int);
   std::map<int,std::vector<float>> get_potential_splits(vec2d<float>);

   float classify_data(std::vector<std::vector<float>>);
   
   auto split_finding(vec2d<float>&,int&,float&);

   void _fit_one_stage(vec2d<float>&,std::shared_ptr<NodeRegression>&,int);
   float predict_one_step(std::vector<float>);
   
   std::shared_ptr<NodeRegression> root;
   int _n_training_examples;
   int _n_features;
   int max_depth;
   int min_sample_split;
};

class GradientDecisionTreeRegressor{
 public:
  GradientDecisionTreeRegressor(int i):_n_estimators(i){};
  void fit(vec2d<float>,std::vector<float>);
  std::vector<float> predict(vec2d<float>);
 private:
  float _predict_on_vector(std::vector<float>);
  std::vector<DecisionTreeRegressor> estimators;
  int _n_estimators;
  int _n_training_examples;
  int _n_features;

};

#endif