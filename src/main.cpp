#include "dataset.hpp"
#include "tree.hpp"
#include <ctime>
#include <algorithm>
using namespace std;
//#include "utils.hpp"



int main()
{   
 
    //TESTss
    clock_t begin = clock();
    ReadCsvBikes *bikes = new ReadCsvBikes(501,7,"data/for_tree.csv");
    std::cout<<"bikes :"<<sizeof(bikes)<<std::endl;
    DecisionTreeRegressor b(3,1);
    auto X = bikes->get_X();
    auto Y = bikes->get_Y();
    b.fit(X,Y);
    //auto tmp = b.predict(X);
    b.print_tree();
    GradientDecisionTreeRegressor t(2);
    t.fit(X,Y,bikes->get_number_rows(),bikes->get_number_columns());;
    clock_t end = clock();
    float elapsed_time = float(end -begin)/CLOCKS_PER_SEC;
    std::cout<<endl<<"ELAPSED TIME: "<<elapsed_time<<std::endl;

    
    
}