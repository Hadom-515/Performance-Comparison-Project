#if PARALLEL
#include <execution>
#define SEQ std::execution::seq,
#define PAR std::execution::par,
#else
#define SEQ
#define PAR
#endif
 
#include <chrono>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
 
int main()
{
    std::cout.imbue(std::locale("en_US.UTF-8"));
        const std::vector<double> v(10000000, rand());
        std::cout<<"Reduce Parrelle with lamda function"<<std::endl;
        const auto t1 = std::chrono::high_resolution_clock::now();
         std::cout << std::reduce(PAR v.begin()+1, v.end(),*v.begin(), 
        [](double a, double b){ return a+b;}) <<'\n';
         const auto t2 = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double, std::milli> ms = t2 - t1;
        std::cout<<ms.count()<<"ms"<<std::endl;
        
        std::cout<<"Reduce Parrelle with standard binary addation opperation"<<std::endl;
       const auto t3 = std::chrono::high_resolution_clock::now();
         std::cout << std::reduce(PAR v.begin()+1, v.end(),*v.begin(), 
        std::plus<>()) <<'\n';
        const auto t4 = std::chrono::high_resolution_clock::now();
         const std::chrono::duration<double, std::milli> ms2 = t4 - t3;
        std::cout<<ms2.count()<<"ms"<<std::endl;
        
       
        std::cout<<"Reduce sequental with lamda function"<<std::endl;
        const auto t5 = std::chrono::high_resolution_clock::now();
         std::cout << std::reduce(SEQ v.begin()+1, v.end(),*v.begin(), 
        [](double a, double b){ return a+b;}) <<'\n';
         const auto t6 = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double, std::milli> ms3 = t6 - t5;
        std::cout<<ms3.count()<<"ms"<<std::endl;
        
        std::cout<<"Reduce Sequental with standard binary addation opperation"<<std::endl;
       const auto t7 = std::chrono::high_resolution_clock::now();
         std::cout << std::reduce(SEQ v.begin()+1, v.end(),*v.begin(), 
        std::plus<>()) <<'\n';
        const auto t8 = std::chrono::high_resolution_clock::now();
         const std::chrono::duration<double, std::milli> ms4 = t8 - t7;
        std::cout<<ms4.count()<<"ms"<<std::endl;
}
