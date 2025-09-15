#pragma once
#include <windows.h>

// Pumps the OS message queue once; returns false when WM_QUIT is received.
bool PumpMessages();