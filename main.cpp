#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
 
std::mutex mt;
int index = 0;
 
class Account
{
public:
    int Balance = 1000;
 
    void Adjust(Account& A, int i){
        mt.lock();
        A.Balance -= i;
        Balance += i;
        std::cout << index + 1 << " " << A.Balance << " " << Balance << std::endl;
        index++; 
        mt.unlock();
    }
};
 
void Update (Account& A, Account& B){
    A.Adjust(B, 10);
}
 
int main ()
{
    std::vector <std::thread> Threads;
    Account A;
    Account B;
    for (int i = 0; i < 50; i++){
        Threads.emplace_back(Update, std::ref(A), std::ref(B));
    }

    for (int i = 0 ; i < 50 ; i++){
        Threads.emplace_back(Update, std::ref(B), std::ref(A));
    }
 
    for (int i=0; i < 100; i++){
        Threads[i].join();
    }
    std::cout << A.Balance << std::endl;
    std::cout << B.Balance << std::endl;
    return 0;
}