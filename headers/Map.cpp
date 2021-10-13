#include "Map.h"


void Map::LoadMap(const char* filepath)
{

    std::ifstream inFile(filepath);

    if (!inFile) {
        std::cout << "Cannot open file.\n";
        return;
    }

    inFile >> width;
    inFile.ignore(1);
    inFile >> height;
    int i = 1, j = 1;
    while (!inFile.eof())
    {
        inFile >> nr;
        if (nr == 1)
        {
            walls.push_back(std::make_pair(i, j));
        }
        if (nr == 0)
        {
            pellets.push_back(std::make_pair(i, j));    
            isMagic.push_back(0);
        }
        if (nr == 2)
        {
            v_pacman.push_back(std::make_pair(i, j));
        }
        if (nr == 3)
        {
            pellets.push_back(std::make_pair(i, j));
            isMagic.push_back(1);
        }

        i++;
        if (i == 29)
        {
            i = 1;
            j++;
        }
    }

    inFile.close();

   //   for (int i = 0; i < walls.size(); i++)
   //   {
   //       std::cout << walls[i].first << ", " << walls[i].second << std::endl;
   //   }

    for (int i = 0; i < v_ghosts.size(); i++)
    {
        std::cout << v_ghosts[i].first << ", " << v_ghosts[i].second << std::endl;
    }

}


void Map::generateGhosts()
{
    for (int i = 0; i < 4; i++)
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0, pellets.size()); // distribution in range [1, 6].
        std::cout << dist6(rng) << std::endl;
        int pellet = dist6(rng);

        if (std::find(v_ghosts.begin(), v_ghosts.end(), pellets[pellet]) != v_ghosts.end())
        {
            i--;
            continue;
        }
        if (pellets[pellet].first < v_pacman[0].first + 10) {
            i--;
            continue;
        }
        v_ghosts.push_back(pellets[pellet]);

    }
    walkable = pellets;
}