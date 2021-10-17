#include "Map.h"

Map::Map(const char* filepath)
{
    LoadMap(filepath);
    GenerateGhosts();

}

// -----------------------------------------------------------------------------
// load the map tiles from outer file
// -----------------------------------------------------------------------------
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
        switch (nr)
        {
        case 1:
            walls.push_back(std::make_pair(i, j));
            break;
        case 0:
            pellets.push_back(std::make_pair(i, j));
            isMagic.push_back(0);
            break;
        case 2:
            v_pacman.push_back(std::make_pair(i, j));
            walkable.push_back(std::make_pair(i, j));
            break;
        case 3:
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
}

// -----------------------------------------------------------------------------
// Generate 4 random ghosts
// -----------------------------------------------------------------------------

void Map::GenerateGhosts()
{ 
    for (int i = 0; i < 4; i++)
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0, pellets.size()-1); 
        int pellet = dist6(rng);
        // if there is allready a ghost on this pellet
        if (std::find(v_ghosts.begin(), v_ghosts.end(), pellets[pellet]) != v_ghosts.end())
        {
            i--;
            continue;
        }
        // Don't generate a ghost infront of the respawn position of pacman
        if (pellets[pellet].first < v_pacman[0].first + 10) {
            i--;
            continue;
        }
        v_ghosts.push_back(pellets[pellet]);
    }
    walkable.insert(walkable.end(), pellets.begin(), pellets.end());
}

