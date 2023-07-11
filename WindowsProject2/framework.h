// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <random>
#include <math.h>
#include <commdlg.h>
#include <stdio.h>

// GDI+
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")

#define PI 3.14159
#define RAD_TO_ANGLE (180.0/PI);
#define ANGLE_TO_RAD (PI/180);
#define LENGTH 70

#define X 0
#define Y 1

#define timer_1 11
#define timer_2 12

//#define WIDTH 1024
//#define HEIGHT 768
#define WIDTH 1280
#define HEIGHT 720

#define WIDTH2 (WIDTH-2)
#define HEIGHT2 (HEIGHT-22)
#define SCORE 10