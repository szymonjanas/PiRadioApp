#include "Radio.hpp"

int main(int argc, char **argv)
{

    radio::Radio radioApp(argc, argv);
    radioApp.start();

    return 0;
}
