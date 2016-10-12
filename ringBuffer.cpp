#include "ringBuffer.h"
#include <Thread>
//Ringbuffer kontruktor
ringBuffer::ringBuffer(int capacity){
    buffer = new char[capacity];
    bufferSize = capacity;
}

//Ringbuffer dekonstruktor
ringBuffer::~ringBuffer(){
    if(buffer != nullptr){
        delete[] buffer;
    }
}

//Legge til tegn i ringbuffer
void ringBuffer::add(char val){
    std::unique_lock<std::mutex> lock(mutex);

    //Stopper traden til den far klarsignal fra ringBuffer::get()
    while ((in + 1) % bufferSize == out){
            full_cv.wait(lock);
    }
    //Setter inn verdi og går til neste plass i ringbuffer
        buffer[in] = val;
        in = (in + 1) % bufferSize;

    //Gir klarsignal til ringBuffer::get()
        empty_cv.notify_one();
}

//Skrive ut tegn fra ringbuffer
char ringBuffer::get(){
    std::unique_lock<std::mutex> lock(mutex);

    //pauser traden til den far klarsignal fra ringBuffer::add()
    while (in == out){
        empty_cv.wait(lock);
    }

    //tar ut tegn fra buffer og gar til neste plass i ringbufferet
    char consumed = buffer[out];
    out = (out + 1) % bufferSize;

    //Gir klarsignal til ringBuffer::add()
    full_cv.notify_one();

    //returnerer tegnet fra ringbufferet,
    return consumed;
}
