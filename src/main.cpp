#include <system.hpp>
#include <iostream>
#include <stdexcept>

int main() {
    try {
        WindowManager window = WindowManager("Snake", 800, 600);
        
        while(!window.endFlag()) {
            window.initNewFotogram();
            
            
            
            window.endFotogram();
        }
    } catch(const std::runtime_error &e) {
        std::cerr << "Fatal error: " << std::endl;
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
