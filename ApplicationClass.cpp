#include "ApplicationClass.h"

ApplicationClass::ApplicationClass()
{
}

ApplicationClass::ApplicationClass(const ApplicationClass&)
{
}

ApplicationClass::~ApplicationClass()
{
}

bool ApplicationClass::Initialize(int, int, HWND)
{
    return true;
}

void ApplicationClass::Shutdown()
{
    return;
}

bool ApplicationClass::Frame()
{
    return true;
}

bool ApplicationClass::Render()
{
    return true;
}
