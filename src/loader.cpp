#include "loader.h"

Loader * Loader::p_instance = nullptr;
std::mutex Loader::m_mutex;

void Loader::increaseCounter(int id)
{
    for (int i = 0; i < 100; ++i)
    {
        // Increment counter atomically 
       
        counter.fetch_add(1);
    }
}


void Loader::test_1()
{

    std::thread t1(&Loader::increaseCounter, this, 1);
    std::thread t2(&Loader::increaseCounter, this, 2);

    t1.join();
    t2.join();


    std::cout << "counter " << counter.load() << "\n";

}

void Loader::loadFile()
{

}

bool Loader::isDoneLoading()
{

    for(int i = 0; i < 100; ++i)
    {
        if (!isDone[i].load())
        {
            std::cout << "current value " << i << "\n";
            return false;
        }
    }
    return true;
}

void Loader::test_2()
{
    for(int i = 0; i < 8; ++i)
    {
        
        std::thread t = std::thread([&](){
            isDone[counter.load()].store(false);
            std:: cout << "thread " << i << "counter " <<  counter.load() << " done \n";
        });
        m_threads.push_back(std::move(t));
        counter.fetch_add(1);
    }


    for (int i = 0 ; i < m_threads.size(); ++i)
    {
        if(m_threads[i].joinable())
        {
            m_threads[i].join();
        }
    }

}

