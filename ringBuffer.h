
#ifndef RINGBUFFER_RINGBUFFER_H
#define RINGBUFFER_RINGBUFFER_H
#include <mutex>
#include <condition_variable>

class ringBuffer {
public:
    ringBuffer(int capacity);
    ~ringBuffer();

    void add(char val);
    char get();


private:

    std::mutex mutex;
    std::condition_variable full_cv;
    std::condition_variable empty_cv;


    char* buffer;
    int bufferSize;
    int in = 0;
    int out = 0;
};


#endif //RINGBUFFER_RINGBUFFER_H
