#include "Libraries.h"

class Map
{

private:
    int width = 0,
        height = 0,
        nr = 0,
        nrOfGhosts = 0;
    
public:
    std::vector<std::pair<int, int>> walls;
    std::vector<std::pair<int, int>> pellets;
    std::vector<int> isMagic;
    std::vector<std::pair<int, int>> v_pacman;
    std::vector<std::pair<int, int>> v_ghosts;
    std::vector<std::pair<int, int>> walkable;
    std::vector <int> map;

    void LoadMap(const char* filepath);
    void generateGhosts();
};