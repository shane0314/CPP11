/*
g++ test39-boost-thread.cpp -o t39 -lboost_thread -pthread
*/
#include <iostream>
#include <boost/thread.hpp>

void task_1()
{
    for (int i = 0; i < 5; i ++)
        std::cout << "task_1 " << i << std::endl;
}

void task_2(int j)
{
    for (int i = 0; i < 5; i ++)
        std::cout << "task_2 " << i << std::endl;
}


int main()
{
    //boost::thread 不需要类似start，begin函数启动！
    boost::thread* t1 = new boost::thread(&task_1);
    boost::thread* t2 = new boost::thread(boost::bind(&task_2, 888));

    boost::this_thread::sleep( boost::posix_time::seconds( 1 ) );

    std::cout << "---main---" << std::endl;

    t1->join();
    t2->join();

    return 0;

}

