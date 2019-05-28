#include <iostream>
#include <array>
#include <map>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <memory>
//#include <string>
#include "dataset.hpp"
#include "tree.hpp"
#include "utils.hpp"


using namespace std;


bool DecisionTreeRegressor::check_cv(vec2d<float> X, int current_depth){
    if(X.size() > this->min_sample_split  && current_depth<this->max_depth){
        return false;
    }
    return true;
}

float DecisionTreeRegressor::classify_data(std::vector<std::vector<float>> X){

    return mean_by_column(X, this->_n_features);
}




void DecisionTreeRegressor::fit(vec2d<float> X,vector<float> Y){
    this->_n_features = X[0].size();
    this->_n_training_examples = X.size();
    this->root = std::make_shared<NodeRegression>();
    auto X_copy = X;
    
    stack_X_and_Y(X_copy,Y);

    int current_depth_tree = 0;
    if (check_cv(X_copy,current_depth_tree)){
        float value = this->classify_data(X);
        this->root->isLeaf = true;
        this->root->value = value;
        this->root->left = nullptr;
        this->root->right = nullptr;
    }
    else{
    _fit_one_stage(X_copy,this->root,current_depth_tree);
    }

}

auto DecisionTreeRegressor::split_finding(vec2d<float>& data,int& index_split_column,float& split_point){

    float min_impurity = 1000;
    vec2d<float> best_left;
    vec2d<float> best_right;
    for(int i = 0;i<this->_n_features;i++){
        sort_by_feature(data,i);
        auto first_element = data.begin();
        auto last_element = data.end();
        int percentile = 1;
        for(int j=percentile;j<data.size()-1;j+=percentile){
            vec2d<float> left_split(first_element,first_element +j);
            vec2d<float> right_split(first_element + j+1,last_element);
            float current_impurity = (j*mse(left_split) +(data.size()- j)*mse(right_split))/data.size();
            if(min_impurity>current_impurity){
                min_impurity = current_impurity;
                index_split_column = i;
                split_point = data[j+1][i];
                best_left = left_split;
                best_right = right_split;
            }
        }
    }

    return make_tuple(best_left,best_right);
}

void DecisionTreeRegressor::_fit_one_stage(vec2d<float>& data,shared_ptr<NodeRegression> &node,int current_depth){
    current_depth++;
    node->isLeaf = false;
    int column_to_split;
    float split_value;
    auto splitted_data =  this->split_finding(data,column_to_split,split_value);
    node->splitColumn = column_to_split;
    node->splitValue = split_value;
    
    vector<vector<float>> data_above = get<0>(splitted_data);
    vector<vector<float>> data_below = get<1>(splitted_data);
    

    node->left = std::make_shared<NodeRegression>();
    if (check_cv(data_below,current_depth)){
        float value = this->classify_data(data_below);
        node->left->isLeaf = true;
        node->left->value = value;
        node->left->left = nullptr;
        node->left->right = nullptr;
    }
    else{
        _fit_one_stage(data_below,node->left,current_depth);
    }

    node->right = std::make_shared<NodeRegression>();
    if (check_cv(data_above,current_depth)){
        float value = this->classify_data(data_above);
        node->right->isLeaf = true;
        node->right->value = value;
        node->right->left = nullptr;
        node->right->right = nullptr;
    }
    else{
        _fit_one_stage(data_above,node->right,current_depth);
    }
    
}

vector<float> DecisionTreeRegressor::predict(vec2d<float> X){
    int n_training_examples = X.size();
    vector<float> prediction;
    prediction.reserve(n_training_examples);
    for(int i=0;i<n_training_examples;i++){
        
        prediction.push_back(predict_one_step(X[i]));
    }
    return prediction;

}

float DecisionTreeRegressor::predict_one_step(vector<float> row_to_predict){
    auto tmp = this->root;
    while(!tmp->isLeaf){
        //cout<<"+ ";
        if(row_to_predict[tmp->splitColumn]>=tmp->splitValue){
            //cout<<"+partition = "<<tmp->splitValue<<endl;
            tmp = tmp->right;
        }
        else{
            //cout<<"-partition = "<<tmp->splitValue<<endl;
            tmp = tmp->left;
        }
    }
    //cout<<"isLeaf - "<<tmp->isLeaf<<endl;
    return tmp->value;
}






vector<float> vectors_substraction(vector<float> a, vector<float> b){
    if(a.size()==b.size()){
        vector<float> output;
        output.reserve(a.size());
        for(int i=0;i<a.size();i++){
            output.push_back(a[i] - b[i]);                                                              
        }
        //cout<<"output.size() = "<<output.size()<<endl;
        return output;
    }
    else{
        cout<<"ERROR in vector substraction operation!!!"<<endl;
        //return NULL;
    }
}
void vectors_addition(vector<float>& a, vector<float> b){
     if(a.size()==b.size()){
        vector<float> output;
        output.reserve(a.size());
        for(int i=0;i<a.size();i++){
            a[i] += b[i];                                                              
        }
    }
    else{
        cout<<"ERROR in vector addition operation!!!"<<endl;
        //return NULL;
    }
}


void GradientDecisionTreeRegressor::fit(vec2d<float> X,vector<float> Y){
    this->_n_features = X[0].size();
    this->_n_training_examples = X.size();
    vector<float> prediction(X.size(),0);
    vector<float> residuals = Y;
    prediction.reserve(_n_training_examples);
    for(int i =0;i<this->_n_estimators;i++){
        auto tmp = DecisionTreeRegressor(3,2);
        tmp.fit(X,residuals);
        this->estimators.push_back(tmp);
        auto predf = tmp.predict(X);
        vectors_addition (prediction, predf);
        residuals = vectors_substraction(Y,prediction);
        cout<<"Error = "<<error(prediction,Y)<<" step = "<<i<<endl;

    }
}

vector<float> GradientDecisionTreeRegressor::predict(vec2d<float> X){
    vector<float> prediction(X.size(),0);
    for(int i=0;i<this->_n_estimators;i++){
        vectors_addition(prediction,estimators[i].predict(X));
    }
    return prediction;
}


