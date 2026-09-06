#include "ApplicationClass.h"


ApplicationClass::ApplicationClass()
{
    m_Direct3D = 0;
    m_Camera = 0;
    m_Model = 0;
    m_LightShader = 0;
    m_Light = 0;
}


ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}


ApplicationClass::~ApplicationClass()
{
}


bool ApplicationClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
    char textureFilename[128];
    bool result;

    m_Direct3D = new D3DClass;
    if (!m_Direct3D)
    {
        return false;
    }

    result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH,
                                    SCREEN_NEAR);
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
        return false;
    }

    m_Camera = new CameraClass;
    if (!m_Camera)
    {
        return false;
    }

    m_Camera->SetPosition(0.0f, 0.0f, -5.0f);

    m_Model = new ModelClass;
    strcpy_s(textureFilename, "../data/stone01.tga");

    result = m_Model->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), textureFilename);
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
        return false;
    }

    m_LightShader = new LightShaderClass;
    result = m_LightShader->Initialize(m_Direct3D->GetDevice(), hwnd);
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
        return false;
    }

    m_Light = new LightClass;
    if (!m_Light)
    {
        return false;
    }

    m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_Light->SetDirection(0.0f, 0.0f, 1.0f);

    return true;
}


void ApplicationClass::Shutdown()
{
    if (m_Light)
    {
        delete m_Light;
        m_Light = 0;
    }

    if (m_LightShader)
    {
        m_LightShader->Shutdown();
        delete m_LightShader;
        m_LightShader = 0;
    }

    if (m_Model)
    {
        m_Model->Shutdown();
        delete m_Model;
        m_Model = 0;
    }

    if (m_Camera)
    {
        delete m_Camera;
        m_Camera = 0;
    }

    if (m_Direct3D)
    {
        m_Direct3D->Shutdown();
        delete m_Direct3D;
        m_Direct3D = 0;
    }

    return;
}


bool ApplicationClass::Frame()
{
    static float rotation = 0.0f;
    bool result;

    rotation -= XMConvertToRadians(0.1f);
    if (rotation < 0.0f)
    {
        rotation += XM_2PI;
    }

    result = Render(rotation);
    if (!result)
    {
        return false;
    }

    return true;
}


bool ApplicationClass::Render(float rotation)
{
    XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
    bool result;

    m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

    m_Camera->Render();

    m_Direct3D->GetWorldMatrix(worldMatrix);
    m_Camera->GetViewMatrix(viewMatrix);
    m_Direct3D->GetProjectionMatrix(projectionMatrix);
    
    worldMatrix = XMMatrixRotationY(rotation);

    m_Model->Render(m_Direct3D->GetDeviceContext());

    result = m_LightShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix,
                                   projectionMatrix, m_Model->GetTexture(),
                                   m_Light->GetDirection(), m_Light->GetDiffuseColor());
    if (!result)
    {
        return false;
    }

    m_Direct3D->EndScene();

    return true;
}
