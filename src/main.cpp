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
    DecisionTreeRegressor b(3);
    //std::cout<<"tree :"<<sizeof(b)<<std::endl;
    b.fit(*bikes);

    clock_t end = clock();
    float elapsed_time = float(end -begin)/CLOCKS_PER_SEC;
    std::cout<<endl<<"ELAPSED TIME: "<<elapsed_time<<std::endl;

    
    
}