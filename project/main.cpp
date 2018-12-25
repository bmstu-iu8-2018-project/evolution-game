#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <gtest/gtest.h>
#include "sourses/Evolution.hpp"

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    Evolution evolution;
    evolution.Menu();
    return 0;
}
