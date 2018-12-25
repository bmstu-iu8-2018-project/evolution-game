#include <boost/filesystem.hpp>
#include <gtest/gtest.h>

#include "Brain.hpp"
#include "Pixel.hpp"

TEST(BrainConstructAnaSolutionTest, ConstructAnaSolutionTest)
{
    Map map;
    map.UploadFromFile(10, 94, 60);
    std::vector<Pixel*> organisms = map.GetOrganisms();
    size_t x = 0;
    size_t y = 0;
    for (size_t i = 0; i < organisms.size(); ++i)
    {
        x = organisms[i]->GetCellStr();
        y = organisms[i]->GetCellCol();
        std::vector<Hexagon*> vec = organisms[i]->LookAround(map);
        EXPECT_TRUE(vec.size() == 6);
        Hexagon* moveTo = organisms[i]->GetBrain().GetSolution(vec);
        organisms[i]->Move(map, moveTo);
        organisms[i]->SetLifes(0);
        if (moveTo != nullptr)
        {
            if (x - moveTo->GetCellStr() != 0)
                EXPECT_TRUE(x != organisms[i]->GetCellStr());
            if (y - moveTo->GetCellCol() != 0)
                EXPECT_TRUE(y != organisms[i]->GetCellCol());
        } else {
            EXPECT_TRUE(x == organisms[i]->GetCellStr());
            EXPECT_TRUE(y == organisms[i]->GetCellCol());
        }
    }
}
