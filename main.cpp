#include <iostream>
#include <thread>
#include "ringBuffer.h"
bool run = true;

//Leser fra ringbufferet
void bufferReader(ringBuffer* buffer){
    while (run){
        std::cout << buffer -> get() << std::flush;
    }
}
//Skriver inn til ringbufferet.
void keyboardReader (ringBuffer* buffer){
    while (run){
        std::string input;
        std::getline(std::cin, input);
        for(int i = 0; i < input.size(); i++){
            buffer -> add(input[i]);
        }
        buffer ->add('\n');

        //Skriv "Stop" for å avslutte programmet.
        if (input == "stop"){
            run = false;
        }
    }
}

//Skriver en tilfeldig bokstav inn i ringbufferet.
void autoinputReader(ringBuffer* buffer){
    while(run){
        buffer->add(rand()%25 + 97);

        //Pauser traden i et sekund.
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    //Setter opp ringbuffer
    ringBuffer buffer(10);

    //Starter de tre traene
    std::thread autoInput(autoinputReader, &buffer);
    std::thread keyboard(keyboardReader, &buffer);
    std::thread reader (bufferReader, &buffer);

    //lar tradene fortsette til de er ferdigkjort
    keyboard.join();
    autoInput.join();
    reader.join();

    //Dekonstruktor for ringbuffer
    buffer .~ringBuffer();
    return 0;
}