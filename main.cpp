#include <iostream>
#include "application.h"

int main(int argc, char const *argv[]) {

    long N = atoi(argv[1]);
    Application app(N);
    app.run();
    return 0;
}
