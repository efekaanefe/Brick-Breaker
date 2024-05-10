#ifndef CONSTANTS_H
#define CONSTANTS_H
#pragma once
#include "raylib.h"

const int screenWidth = 1600;
const int screenHeight = 900;
const Color backgroundColor = BLACK;

const int playerWidth = 200;
const int playerHeight = 30;
const Color playerColor = DARKGRAY;

const int ballRadius = 10;
const int ballSpeed = 500;
const Color ballColor = WHITE;

const int startX = 50;
const int startY = 50;
const int numRows = 10; 
const int numCols = 10;
const int blockWidth = (screenWidth-startX*2)/numCols;
const int blockHeight = 25;


#endif