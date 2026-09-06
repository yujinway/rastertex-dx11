#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_

#include "CameraClass.h"
#include "d3dclass.h"
#include "ModelClass.h"
#include "LightShaderClass.h"
#include "LightClass.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.3f;

class ApplicationClass
{
public:
    ApplicationClass();
    ApplicationClass(const ApplicationClass&);
    ~ApplicationClass();

    bool Initialize(int, int, HWND);
    void Shutdown();
    bool Frame();

    bool Render(float);

private:
    D3DClass* m_Direct3D;
    CameraClass* m_Camera;
    ModelClass* m_Model;
    LightShaderClass* m_LightShader;
    LightClass* m_Light;
    
};

#endif
