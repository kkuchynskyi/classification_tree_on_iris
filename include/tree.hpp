#ifndef TREE_H
#define TREE_H
#include <vector>
#include <string>
#include <map>
#include <tuple>
#include <memory>
template<class T>
using vec2d = std::vector<std::vector<T>>;


struct Node{
  bool isLeaf = {0};
  float splitValue;
  int splitColumn;
  std::unique_ptr<Node> left;   // Pointer to the left subtree.
  std::unique_ptr<Node> right; // Pointer to the right subtree.
};

struct NodeClassification : Node{
  std::string category;         // The data in this node.
  std::unique_ptr<NodeClassification> left;   // Pointer to the left subtree.
  std::unique_ptr<NodeClassification> right;
};

struct NodeRegression : Node{
  float value;       // The data in this node.
  std::shared_ptr<NodeRegression> left;   // Pointer to the left subtree.
  std::shared_ptr<NodeRegression> right;
};

class BaseDecisionTree{
 public:
  virtual void fit(vec2d<float>,std::vector<float>) = 0;
  //virtual vector<float> predict(vec2d<float>);
  //virtual void print_tree() = 0;

};



class DecisionTreeClassifier{
  public:
   //void decision_tree_algorithm(vec2d<float>, std::vector<std::string>, int);
   void fit(vec2d<float>, std::vector<std::string>);
   void print_tree();
  private:
   bool check_purity(std::vector<std::string>);
   
   std::string classify_data(std::vector<std::string>);
   
   std::map<int,std::vector<float>> get_potential_splits(vec2d<float>);
   
   std::tuple<vec2d<float>,vec2d<float>,std::vector<std::string>,std::vector<std::string>> \
    split_data(vec2d<float>, std::vector<std::string>, float,int);

   float calculate_entropy(std::vector<float>,std::vector<std::string>);

   float calculate_overall_entropy(std::vector<float>,std::vector<float>,std::vector<std::string>,std::vector<std::string>);

   std::tuple<int,float> determine_best_split(vec2d<float>,const std::vector<std::string>,std::map<int,std::vector<float>>);

   void _fit_one_stage(vec2d<float>, std::vector<std::string>, std::unique_ptr<Node>&);
   
   void _print_one_node(std::unique_ptr<Node>&);
   std::unique_ptr<Node> root;

};


class DecisionTreeRegressor : public BaseDecisionTree{
  public:
   DecisionTreeRegressor(int i,int j): max_depth(i),min_sample_split(j){};
   void fit(vec2d<float> ,std::vector<float>) override;
   std::vector<float> predict(vec2d<float>);
   void print_tree();
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
  GradientDecisionTreeRegressor(int i ):_n_estimators(i){};
  void fit(vec2d<float>,std::vector<float>,int,int);
 private:
  std::vector<DecisionTreeRegressor> estimators;
  int _n_estimators;
  int _n_training_examples;
  int _n_features;
};

#endif