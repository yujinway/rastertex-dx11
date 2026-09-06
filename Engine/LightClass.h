#pragma once

#include <DirectXMath.h>
using namespace DirectX;

class LightClass
{
public:
    LightClass();
    LightClass(const LightClass&);
    ~LightClass();

    void SetDiffuseColor(float red, float green, float blue, float alpha);
    void SetDirection(float x, float y, float z);

    XMFLOAT4 GetDiffuseColor();
    XMFLOAT3 GetDirection();

private:
    XMFLOAT4 m_diffuseColor;
    XMFLOAT3 m_direction;
};
