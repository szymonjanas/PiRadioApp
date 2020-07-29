#include <iostream>
#include <string>

#include "Communication.hpp"

int main(int argc, char ** argv)
{
    Communication comm("tcp://localhost:5555");
    comm.connect();
    comm.run();
}
