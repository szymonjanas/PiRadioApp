#include <iostream>
#include <string>
#include "Communication.hpp"

int main(int argc, char ** argv)
{
    Communication comm;
    comm.bind("tcp://*:5555");

    system("go run ../server/server.go &");

    comm.run(new StationsDatabaseTxt("../database.txt"));
}
