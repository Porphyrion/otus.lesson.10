#include <iostream>
#include "application.h"

int main(int argc, char const *argv[]) {

    if(argc > 1){
        long N = atoi(argv[1]);
        Application bulkmt(N);
        bulkmt.run();
    } else {
        std::cout<<"Few arguments"<<std::endl;
    }
    return 0;
}
