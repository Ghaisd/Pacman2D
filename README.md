# This is a project for the university class "PROG2002 - Graphics Programming"

Running the program

To run the program, simply build the program using Visual Studio 2019, opening the repository as a folder, building CMakeLists.txt (by saving it with ctrl+s), and building & running Pacman2D.exe (Tested on windows)
** Game control:
Pacman move using WASD.
Escape key will shutdown the game.
F: full screen mode, H: back to windowed mode
** Optional Features:
1- the pellets has been changed into circle
2- tried to apply multisampling but did not work
3- The screen is resizable(Full screen mode / windowed mode)
4- Magic pellets have been drawn (with no functionality).
** Introduction
the program build and run properly in machines with:

Recent compiler (Visual studio 2019 or GCC >= 9.0)
Recent OpenGL (>= 4.1)
CMake (>= 3.15)
Recent GLFW (>= 3.3.2)
GLAD
C++ >= 11

** Scenario


The program is able to load the scenario provided in the levels/level0
file of this repository. In this file 1s refer to walls, 0s refer to tunnels
and 2 refer to the initial position of /Pacman/.


The program displays the scenario using the maximum possible area of the
window allocated for it and respecting the aspect ratio of the map.


The program displays the tunnel areas in the same color as the background
color (up to the group to choose). The walls areas have a different
color than the background (up to the group to choose).


** Pellets


The program places and displays /pellets/ (pearls or balls) in tunnel
areas. The color of the is  different than the colors of the
background and walls. Pellets have all the same size, but the shape is
symmetrical (e.g, square, diamond, circle);


Pellets dissappear (visually) when /Pacman/ passes over them.


** Pacman


The program place and display a /Pacman/ character that moves only
inside the tunnel areas (it does not traverse walls). Pacman is
animated using the sprite sheet provided in assets/pacman.png.


Movement of /Pacman/ can be directed by the player using the /arrow keys/ (up,
down, left, right). Pacman cannot move outside the map.


** Ghosts

The program place and display /Ghosts/ (number of /ghosts/ decided by the
group) characters which move only inside the /tunnel/ areas (/Ghosts/ do
not traverse walls). The movement of the /Ghosts/ can be random throughout the
game. The /Ghosts/ should be animated using the sprite sheet provided in
assets/pacman.png. The initial position of the /ghosts/ should be random.

** Game mechanics

The game ends when (1) there are no more /pellets/ on the screen or (2) when
/pacman/ collides with any of the /Ghosts/. Ending the game close the window.
The application terminates when the user presses the Escape key.
