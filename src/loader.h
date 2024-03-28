#include <atomic> 
#include <array>
#include <iostream> 
#include <thread> 
#include <mutex>
#include <vector>


class Loader
{
public:
    Loader() {

        std::cout << "Loader() \n"; 
        for (int i = 0; i < 200; ++i)
        {
            isDone[i].store(true);
        }
        //isDone[7].store(false);

    }

    ~Loader() {}

    static Loader * getInstance() {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (!p_instance) {
            p_instance = new Loader();
        }
        return p_instance;
    }

    void test_1();

    void test_2();

    void loadFile();
    bool isDoneLoading();

    void increaseCounter(int id);
private:

    static std::mutex m_mutex;
    static Loader * p_instance;
    std::atomic<int> counter{0};
    std::array<std::atomic<bool>, 200> isDone{{}};
    std::vector<std::thread> m_threads;
};
