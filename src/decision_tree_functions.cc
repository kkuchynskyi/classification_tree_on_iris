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



// bool DecisionTreeClassifier::check_purity(vector<string> labels){
//     // get unique label values
//     vector<string> unique_labels_vec;
//     unique_labels_vec = labels;
//     vector<string>::iterator it;
//     it = unique(unique_labels_vec.begin(), unique_labels_vec.end());
//     unique_labels_vec.resize(distance(unique_labels_vec.begin(),it));
//     if(unique_labels_vec.size()==1){
//         return true;
//     }
//     else{
//         return false;
//     }
// }

// string DecisionTreeClassifier::classify_data(vector<string> labels){
//     vector<string> unique_labels_vec;
//     unique_labels_vec = labels;
//     vector<string>::iterator it;
//     it = unique(unique_labels_vec.begin(), unique_labels_vec.end());
//     unique_labels_vec.resize(distance(unique_labels_vec.begin(),it));
//     string classification;
//     int count;
//     int max_count = 0;
//     for(auto unique_value_index=0;unique_value_index<unique_labels_vec.size();unique_value_index++){
//         count=0;
//         for(auto i=0;i<labels.size();i++){
//             if(labels.at(i)==unique_labels_vec.at(unique_value_index)){
//                 count+=1;
//             }
//         }
//         if(count>max_count){
//             max_count = count;
//             classification = unique_labels_vec.at(unique_value_index);
//         }
//     }
//     return classification;
// }

// map<int,vector<float>> DecisionTreeClassifier::get_potential_splits(vector<vector<float>> data){
//     map<int,vector<float>> potential_splits;
//     for(auto column_index=0;column_index<data.size();column_index++){
        
//         vector<float> potential_splits_per_column;
//         vector<float> unique_features_vec;
//         unique_features_vec = data.at(column_index);
//         vector<float>::iterator it;
//         it = unique(unique_features_vec.begin(), unique_features_vec.end());
//         unique_features_vec.resize(distance(unique_features_vec.begin(),it));
//         sort(unique_features_vec.begin(),unique_features_vec.end());
        

        
//         for(auto i=1;i<data.at(column_index).size();i++){
//             potential_splits_per_column.push_back((data.at(column_index).at(i)+data.at(column_index).at(i-1))/2);
//         }
//         potential_splits[column_index] = potential_splits_per_column;


//     }
//     return potential_splits;
// }

// tuple<vector<vector<float>>,vector<vector<float>>,vector<string>,vector<string>> \
//  DecisionTreeClassifier::split_data(vector<vector<float>> data,vector<string> labels,float split_value,int column_index){
//     vector<vector<float>> data_below;
//     vector<vector<float>> data_above;
//     vector<string> labels_below;
//     vector<string> labels_above;

//     int first_visit_checker1 = 0;
//     int first_visit_checker2 = 0;

//     for(auto i=0;i<data.at(column_index).size();i++){
//         if(data.at(column_index).at(i)>split_value){
//             if(first_visit_checker1==0){
//                 for(auto j=0;j<data.size();j++){
//                     vector<float> column1;
//                     column1.push_back(data.at(j).at(i));
//                     data_above.push_back(column1);
//                 }
//                 labels_above.push_back(labels.at(i));
//                 first_visit_checker1++;
//             }
//             else{
//                 for(auto j=0;j<data.size();j++){
//                     data_above.at(j).push_back(data.at(j).at(i));
//                 }
//                 labels_above.push_back(labels.at(i));
//             }
                
//         }
//         else{
//             if(first_visit_checker2==0){
//                 for(auto j=0;j<data.size();j++){
//                     vector<float> column2;
//                     column2.push_back(data.at(j).at(i));
//                     data_below.push_back(column2);
//                 }
//                 labels_below.push_back(labels.at(i));
//                 first_visit_checker2+=1;
//             }
//             else{
//                 for(auto j=0;j<data.size();j++){
//                     data_below.at(j).push_back(data.at(j).at(i));
//                 }
//                 labels_below.push_back(labels.at(i));
//             }     
//         }
//     }

//     return make_tuple(data_below,data_above,labels_below,labels_above);

// }

// float DecisionTreeClassifier::calculate_entropy(vector<float> feature_column,vector<string> labels){
//     // get unique label values
//     vector<string> unique_labels_vec;
//     unique_labels_vec = labels;
//     vector<string>::iterator it;
//     it = unique(unique_labels_vec.begin(), unique_labels_vec.end());
//     unique_labels_vec.resize(distance(unique_labels_vec.begin(),it));
//     vector<float> unique_counts;
//     for(auto unique_value_index=0;unique_value_index<unique_labels_vec.size();unique_value_index++){
//         unique_counts.push_back(0);
//         for(auto i=0;i<labels.size();i++){
//             if(labels.at(i)==unique_labels_vec.at(unique_value_index)){
//                 unique_counts.at(unique_value_index)+=1;
//             }
//         }
//     }
//     float sum_of_elements = 0;
//     for_each( unique_counts.begin(), unique_counts.end(), [&](float & x)
//     { sum_of_elements-=(x/labels.size())*log2(x/labels.size()); });

//     return sum_of_elements;
// }

// float DecisionTreeClassifier::calculate_overall_entropy(vector<float> data_below,vector<float> data_above,vector<string> labels_below,vector<string> labels_above){
//     float probability_below = (float)data_below.size()/(float)(data_below.size() + data_above.size());
//     float probability_above = 1 - probability_below;
 
//     float overall_entropy = (probability_above*calculate_entropy(data_above,labels_above) \
//     +probability_below*calculate_entropy(data_below,labels_below));
//     return overall_entropy;
// }

// tuple<int,float> DecisionTreeClassifier::determine_best_split(vector<vector<float>> data,const vector<string> labels,map<int,vector<float>> potential_splits){
//     float overall_entropy = 999;
//     float current_overall_entropy;
//     int best_split_column;
//     float best_split_value;

//     tuple<vector<vector<float>>,vector<vector<float>>,vector<string>,vector<string>> tuple_;
//     vector<vector<float>> data_below;
//     vector<vector<float>> data_above = get<1>(tuple_);
//     vector<string> labels_below = get<2>(tuple_);
//     vector<string> labels_above = get<3>(tuple_);
//     for (auto const& x : potential_splits){
//         for(auto j=0;j<x.second.size();j++){
//             tuple_  = split_data(data,labels,x.second.at(j),x.first);
//             data_below = get<0>(tuple_);
//             data_above = get<1>(tuple_);
//             labels_below = get<2>(tuple_);
//             labels_above = get<3>(tuple_);
//             if (data_above.size()!=0 && data_below.size()!=0){
//                 current_overall_entropy = calculate_overall_entropy(data_below.at(x.first),data_above.at(x.first),labels_below,labels_above);
//                 if (current_overall_entropy<overall_entropy){
//                     overall_entropy=current_overall_entropy;
//                     best_split_column = x.first;
//                     best_split_value = x.second.at(j);
//                 }

//             }
//         }
//     }


//     return make_tuple(best_split_column,best_split_value);
// }



// void DecisionTreeClassifier::fit(vector<vector<float>> data,vector<string> labels){
//     this->root = std::make_unique<Node>();
//     if (check_purity(labels)){
//         string classification = this->classify_data(labels);
//         this->root->isLeaf = true;
//         this->root->category = classification;
//         this->root->left = nullptr;
//         this->root->right = nullptr;
//         //cout<<"FINISH!"<<endl;;
//     }
//     else{
//         _fit_one_stage(data,labels,root);
//     }
// }

// void DecisionTreeClassifier::_fit_one_stage(vector<vector<float>> data,vector<string> labels,std::unique_ptr<Node> &node){
//     map<int,vector<float>> potential_splits = get_potential_splits(data);
//     tuple<int,float> tuple_ = determine_best_split(data,labels,potential_splits);
//     int column_to_split = get<0>(tuple_);
//     float split_value = get<1>(tuple_);
//     //cout<<endl;
//     //cout<<"COUNT:"<<counter<<". Column to split: "<<column_to_split<<". Split value: "<<split_value<<endl;
//     node->isLeaf = false;
//     node->splitColumn = column_to_split;
//     node->splitValue = split_value;
//     tuple<vector<vector<float>>,vector<vector<float>>,vector<string>,vector<string>> splitted_data =  split_data(data,labels,split_value,column_to_split);
//     vector<vector<float>> data_below = get<0>(splitted_data);
//     vector<vector<float>> data_above = get<1>(splitted_data);
//     vector<string> labels_below = get<2>(splitted_data);
//     //cout<<"Below"<<endl;
//     node->left = std::make_unique<Node>();
//     if (check_purity(labels_below)){
//         string classification = this->classify_data(labels);
        
//         node->left->isLeaf = true;
//         node->left->category = classification;
//         node->left->left = nullptr;
//         node->left->right = nullptr;
//         //cout<<"FINISH!"<<endl;;
//     }
//     else{
//         _fit_one_stage(data_below,labels_below,node->left);
//     }
//     //cout<<"Above"<<endl;
//     vector<string> labels_above = get<3>(splitted_data);
//     node->right = std::make_unique<Node>();
//     if (check_purity(labels_above)){
//         string classification = this->classify_data(labels_above);
//         //cout<<"FINISH!"<<endl;;
//         node->right->isLeaf = true;
//         node->right->category = classification;
//         node->right->left = nullptr;
//         node->right->right = nullptr;
//     }
//     else{
//         _fit_one_stage(data_above,labels_above,node->right);
//     }
    
// }

// void DecisionTreeClassifier::print_tree(){
//     cout<<"TREE : "<<endl;
//     _print_one_node(this->root);
// }

// void DecisionTreeClassifier::_print_one_node(std::unique_ptr<Node> &node){
//     if(node->isLeaf==true){
//         cout<<"CLASSIFICATION : "<<node->category<<endl;
//     }
//     else{
//         cout<<"split.column : "<<node->splitColumn<<" split.value : "<<node->splitValue<<endl;
//         if(node->right != nullptr){
//             _print_one_node(node->right);
//         }
//         else{
//             cout<<"right : "<<node->right->category<<endl;
//         }
//         if(node->left != nullptr){
//             _print_one_node(node->left);
//         }
//         else{
//             cout<<"right : "<<node->left->category<<endl;
//         }
//     }
// }

/////////////////////////////////////////////////////////////////////////////



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
    //cout<<"number_columns : "<<number_columns<<endl;

    int current_depth_tree = 0;
    if (check_cv(X_copy,current_depth_tree)){
        float value = this->classify_data(X);
        this->root->isLeaf = true;
        this->root->value = value;
        this->root->left = nullptr;
        this->root->right = nullptr;
        //cout<<"FINISH!"<<endl;;
    }
    else{
    _fit_one_stage(X_copy,this->root,current_depth_tree);
    }

}

auto DecisionTreeRegressor::split_finding(vec2d<float>& data,int& index_split_column,float& split_point){

    float min_impurity = 1000;
    vec2d<float> best_left;
    vec2d<float> best_right;
    // float mean_value = vector_mean_last_columns(data);
    // int loss = squared_error(data,mean_value);
    // int loss_right = 0;
    // int loss_left = 0;
    for(int i = 0;i<this->_n_features;i++){


        sort_by_feature(data,i);

        auto first_element = data.begin();
        auto last_element = data.end();
        int percentile = 1;
        for(int j=percentile;j<data.size()-1;j+=percentile){
           
            vec2d<float> left_split(first_element,first_element +j);
            vec2d<float> right_split(first_element + j+1,last_element);

            float current_impurity = (j*mse(left_split) +(data.size()- j)*mse(right_split))/data.size();
            //cout<<"--"<<endl;
            if(min_impurity>current_impurity){
                min_impurity = current_impurity;
                index_split_column = i;
                split_point = data[j+1][i];
                best_left = left_split;
                best_right = right_split;
            }
            
        }
    }

    //cout<<"index_split_column : "<<index_split_column<<endl;
    //cout<<"split_point : "<<split_point<<endl;
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
    //cout<<"Column to split: "<<column_to_split<<". Split value: "<<split_value<<endl;
    vector<vector<float>> data_above = get<0>(splitted_data);
    vector<vector<float>> data_below = get<1>(splitted_data);
    //cout<<"Below : "<<data_below.size()<<endl;

    node->left = std::make_shared<NodeRegression>();
    if (check_cv(data_below,current_depth)){
        float value = this->classify_data(data_below);
        node->left->isLeaf = true;
        node->left->value = value;
        node->left->left = nullptr;
        node->left->right = nullptr;
        //cout<<"FINISH!"<<endl;;
    }
    else{
        _fit_one_stage(data_below,node->left,current_depth);
    }
    //cout<<"Above : "<<data_above.size()<<endl;
    // vector<string> labels_above = get<3>(splitted_data);
    node->right = std::make_shared<NodeRegression>();
    if (check_cv(data_above,current_depth)){
        float value = this->classify_data(data_above);
        node->right->isLeaf = true;
        node->right->value = value;
        node->right->left = nullptr;
        node->right->right = nullptr;
        //cout<<"FINISH!"<<endl;;
    }
    else{
        _fit_one_stage(data_above,node->right,current_depth);
    }
    
}

vector<float> DecisionTreeRegressor::predict(vec2d<float> X){
    //int n_features = data_to_predict.get_number_columns()-1;
    int n_training_examples = X.size();
    vector<float> prediction;
    prediction.reserve(n_training_examples);
    for(int i=0;i<n_training_examples;i++){
        //cout<<"Prediction "<<i<<endl;
        prediction.push_back(predict_one_step(X[i]));
    }
    //cout<<"Prediction end"<<endl;
    // for(int i=0;i<n_training_examples-1;i++){
    //     cout<<"PREDICTED VALUES = "<<(prediction[i])<<endl;
    // }
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

void DecisionTreeRegressor::print_tree(){
    auto tmp = this->root->left->right->left;
    cout<<"L->R->L"<<tmp->value<<endl;
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


void GradientDecisionTreeRegressor::fit(vec2d<float> X,vector<float> Y,int n_rows,int n_columns){
    this->_n_features = n_columns;
    this->_n_training_examples = X.size();
    //this->root = std::make_shared<NodeRegression>();
    vector<float> prediction(X.size(),0);
    vector<float> residuals = Y;
    cout<<"Y.size() = "<<Y.size()<<" Residuals.size() = "<<residuals.size()<<endl;
    //copy(Y.begin(), Y.end(), residuals.begin());;
    cout<<"prediction.size()!! = "<<prediction.size()<<endl;
    prediction.reserve(_n_training_examples);
    for(int i =0;i<10;i++){
        //cout<<"Residuals[0]  : "<<residuals[0]<<endl;
        //cout<<"Residuals[34]  : "<<residuals[34]<<endl;
        auto tmp = DecisionTreeRegressor(3,2);
        cout<<"start train"<<endl;
        cout<<"X[0].shape  = "<<X[0].size()<<" X.size() :"<<X.size()<<"residuals.shape  = "<<residuals.size()<<endl;
        tmp.fit(X,residuals);
        //tmp.print_tree();
        //cout<<"end train"<<endl;
        this->estimators.push_back(tmp);
        auto predf = tmp.predict(X);
        //cout<<"predf[0] = "<<predf[0]<<endl;
        //cout<<"predf.size() = "<<predf.size()<<endl;
        vectors_addition (prediction, predf);
        //cout<<"prediction.size() = "<<prediction.size()<<endl;
        // cout<<"prediction[0] = "<<prediction[0]<<endl;
        // cout<<"prediction[1] = "<<prediction[1]<<endl;
        // cout<<"prediction[34] = "<<prediction[34]<<endl;
        //cout<<"--Residuals[34]  : "<<residuals[34]<<endl;

        residuals = vectors_substraction(Y,prediction);
        //cout<<"++Residuals[34]  : "<<residuals[34]<<endl;
        cout<<"Error = "<<error(prediction,Y)<<" step = "<<i<<endl;

    }
}

