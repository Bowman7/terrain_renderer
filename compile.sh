#!/bin/bash

g++ main.cpp trianglelist.cpp  include/ogldev_util.cpp -o run -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lm -g

#run
./run

