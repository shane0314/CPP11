
//

//  main.cpp

//  Demo

//

//  Created by 杜国超 on 17/7/9.

//  Copyright © 2017年 杜国超. All rights reserved.

//

//#include "atomic.hpp"

#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include <sstream>
using namespace std;

//std::atomic<bool> ready(false);
//std::atomic num(0);
std::atomic<int> num(0);

void testThread1()
{

    for (int i = 0;i < 1000;i++) {

        /////////////Do Something/////////

        int temp = num;

        temp++;

        /////////////Do Something End/////////

        num = temp;

    }

}

 

void testThread2()

{

    for (int i = 0;i < 1000;i++)

    {

        /////////////Do Something/////////

        int temp = num;

        temp++;

        /////////////Do Something End/////////

        num = temp;

    }

}

 
int main()

{

    //list temp;

    std::thread thread1(testThread1);

    std::thread thread2(testThread2);

 

    thread1.join();

    thread2.join();

    std::cout << "num = " << num << std::endl;

}

