# Projekt-semestralny

This is a Snake Game repository. It's a final project made for a C++ object oriented programming course.

It was written using the Raylib library, available [here](https://www.raylib.com/).

[Here](https://github.com/raysan5/raylib) is it's github repository.

This project is overcomplicated in some places, but that was a requirement (we had to demonstrate understanding of C++ functionalities).

## Movement

Movement is done by WSAD. The snake dies when its head touches a wall, or its body. The snake grows as it eats the food appearing on the screen randomly. If the food appears where the snake's body is, the snake also grows.

## How to run

If there is no ```build``` folder:
(in the main project directory)

```bash
mkdir build && cd build
cmake ..
make
./MyExecutable
```

If there is an existing build folder:

```bash
cd build
cmake ..
make
./MyExecutable
```
