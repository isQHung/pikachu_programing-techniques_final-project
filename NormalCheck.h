#pragma once
#ifndef _CHECK1_H_
#define _CHECK1_H_

#include "Struct.h"
bool nextcheck(Normal**, int p1, int p2, int q1, int q2, bool = 0);
bool linecheck(Normal**, int p1, int p2, int q1, int q2);
bool Icheck_1(Normal**, int p1, int p2, int q1, int q2, bool = 0);
bool Lcheck(Normal**, int p1, int p2, int q1, int q2, bool = 0);
bool Zcheck(Normal**, int p1, int p2, int q1, int q2, bool = 0);
bool Ucheck(Normal**, int p1, int p2, int q1, int q2, bool = 0);
bool allcheck(Normal**, int p1, int p2, int q1, int q2, bool = 0);
bool checkValidPairs(Normal**, bool = 0);

#endif
