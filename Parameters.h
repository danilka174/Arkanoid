#pragma once

unsigned constexpr FRAME_RATE = 200;

float constexpr USER_WINDOW_HEIGHT = 800; //высота окна
float constexpr USER_WINDOW_WIDTH = 650; //ширина окна
float constexpr OFFSET_HEIGHT = USER_WINDOW_HEIGHT / 10; //отступ

float constexpr FIELD_WINDOW_HEIGHT = 2 * USER_WINDOW_HEIGHT / 5; //высота пол€
float constexpr FIELD_WINDOW_WIDTH = USER_WINDOW_WIDTH; //ширина пол€
unsigned constexpr NUMBER_BLOCKS_IN_ROW = 7; //количество блоков в строке
unsigned constexpr NUMBER_BLOCKS_IN_COLUMN = 5; // количество блоков в столбце

float constexpr BALL_RADIUS = USER_WINDOW_WIDTH / 40; //радиус м€ча
float constexpr BALL_X = USER_WINDOW_WIDTH / 2 - BALL_RADIUS; //координата ’ м€ча 
float constexpr BALL_Y = 17 * USER_WINDOW_HEIGHT / 20; //координата Y м€ча

float constexpr PLATE_HEIGHT = USER_WINDOW_HEIGHT / 35; //высота платформы
float constexpr PLATE_WIDTH = USER_WINDOW_WIDTH / 4; //ширина платформы
float constexpr PLATE_X = BALL_X - PLATE_WIDTH / 2 + BALL_RADIUS; //координата ’ платформы
float constexpr PLATE_Y = BALL_Y + 2 * BALL_RADIUS; //координата Y платформы

float constexpr TEXT_SIZE = USER_WINDOW_HEIGHT / 10; //размер текста
float constexpr TEXT_X = USER_WINDOW_WIDTH / 50; //координаты текста
float constexpr TEXT_Y = -USER_WINDOW_WIDTH / 100; //координаты текста

float constexpr INCREASE_SPEED = 1.5;
unsigned constexpr BONUS_NUMBER = 6;