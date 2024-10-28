
#include <chrono>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
 
int main()
{
   std::cout.imbue(std::locale("en_US.UTF-8"));
        const std::vector<double> v(10000000, rand()%10);
        int count=0;
        std::cout<<"Reduce Parrelle with lamda function"<<std::endl;
        const auto t1 = std::chrono::high_resolution_clock::now();
       for(int i=0;i<v.size();i++){
           count+=v.at(i);
       }
       std::cout<<count<<std::endl;
         const auto t2 = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double, std::milli> ms = t2 - t1;
        std::cout<<ms.count()<<"ms"<<std::endl;
        
}
