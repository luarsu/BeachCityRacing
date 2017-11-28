# BeachCityRacing
Simple racing game programmed using C++ and OpenGL

In this game we control a car from a 1st person view that has to collect the stars in the road to increase its score. There is no way to lose on this game, so the road and the entire map never ends as it is loaded in the game based on the player's position. The shape of the road is generated based on a sinusoidal function, and every element on screen (trees, houses, the road, lights...) are loaded and deleted from the map also based on the player's position and the sinusoidal function.

The game also includes a night mode, fog mode, a simple interface to show the car's direction and speed and a wired mode. It also detects collisions with the starts to increase the score.


GAME CONTROLS:
Up/down arrows: Increase/decrease speed
Right/left arrows: Change direction
N: Fog mode
L: Night Mode
S: Wired mode
F: Stop the car completely

This different modes can be combined.

WARNING:
To play this game it's necessary to have the OpenGL and Freeglut libraries intalled correctly. If you don't, the game and the project won't work.

To just play the game execute the BeachCityRacing.exe file once the freeglut library is correctly installed. You can find this file inside the folder BeachCityRacing Game.

To check the code, open the Visual Studio project. The main code of the game is in the Videjuego.cpp file that can be found inside the ProyectoFinal folder. All the code has comments to explain its functioning.

The game was programmed in C++ using the OpenGL and Freeglut library.

Enjoy!
