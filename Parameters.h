#pragma once

unsigned constexpr FRAME_RATE = 200;

float constexpr USER_WINDOW_HEIGHT = 800; //������ ����
float constexpr USER_WINDOW_WIDTH = 650; //������ ����
float constexpr OFFSET_HEIGHT = USER_WINDOW_HEIGHT / 10; //������

float constexpr FIELD_WINDOW_HEIGHT = 2 * USER_WINDOW_HEIGHT / 5; //������ ����
float constexpr FIELD_WINDOW_WIDTH = USER_WINDOW_WIDTH; //������ ����
unsigned constexpr NUMBER_BLOCKS_IN_ROW = 7; //���������� ������ � ������
unsigned constexpr NUMBER_BLOCKS_IN_COLUMN = 5; // ���������� ������ � �������

float constexpr BALL_RADIUS = USER_WINDOW_WIDTH / 40; //������ ����
float constexpr BALL_X = USER_WINDOW_WIDTH / 2 - BALL_RADIUS; //���������� � ���� 
float constexpr BALL_Y = 17 * USER_WINDOW_HEIGHT / 20; //���������� Y ����

float constexpr PLATE_HEIGHT = USER_WINDOW_HEIGHT / 35; //������ ���������
float constexpr PLATE_WIDTH = USER_WINDOW_WIDTH / 4; //������ ���������
float constexpr PLATE_X = BALL_X - PLATE_WIDTH / 2 + BALL_RADIUS; //���������� � ���������
float constexpr PLATE_Y = BALL_Y + 2 * BALL_RADIUS; //���������� Y ���������

float constexpr TEXT_SIZE = USER_WINDOW_HEIGHT / 10; //������ ������
float constexpr TEXT_X = USER_WINDOW_WIDTH / 50; //���������� ������
float constexpr TEXT_Y = -USER_WINDOW_WIDTH / 100; //���������� ������

float constexpr INCREASE_SPEED = 1.5;
unsigned constexpr BONUS_NUMBER = 6;