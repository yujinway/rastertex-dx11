#include "ModelClass.h"

ModelClass::ModelClass()
{
    m_vertexBuffer = 0;
    m_indexBuffer = 0;
}

ModelClass::ModelClass(const ModelClass&)
{
}

ModelClass::~ModelClass()
{
}

bool ModelClass::Initialize(ID3D11Device* device)
{
    bool result;
    
    result = InitializeBuffers(device);
    if (!result)
    {
        return false;
    }
    
    return true;
}

void ModelClass::Shutdown()
{
    ShutdownBuffers();
    return;
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
    RenderBuffers(deviceContext);
    return;
}

int ModelClass::GetIndexCount()
{
    return m_indexCount;
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
    VertexType* vertices;
    unsigned long* indices;
    D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
    HRESULT result;
    
    m_vertexCount = 3;
    m_indexCount = 3;
    
    vertices = new VertexType[m_vertexCount];
    if (!vertices)
    {
        return false;
    }
    
    indices = new unsigned long[m_indexCount];
    if (!indices)
    {
        return false;
    }
    
    vertices[0].position = XMFLOAT3(-1.0f, -1.0f, 0.0f); // 좌하단
    vertices[0].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
    
    vertices[1].position = XMFLOAT3(0.0f, 1.0f, 0.0f); // 상단 중앙
    vertices[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
    
    vertices[2].position = XMFLOAT3(1.0f, -1.0f, 0.0f); // 우하단
    vertices[2].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
    
    indices[0] = 0; // 좌하단
    indices[1] = 1; // 상단 중앙
    indices[2] = 2; // 우하단
    
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.StructureByteStride = 0;
    
    vertexData.pSysMem = vertices;
    vertexData.SysMemPitch = 0;
    vertexData.SysMemSlicePitch = 0;
    
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
    if (FAILED(result))
    {
        return false;
    }
    
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
    indexBufferDesc.StructureByteStride = 0;

    indexData.pSysMem = indices;
    indexData.SysMemPitch = 0;
    indexData.SysMemSlicePitch = 0;

    result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
    if (FAILED(result))
    {
        return false;
    }
    
    delete [] vertices;
    vertices = 0;

    delete [] indices;
    indices = 0;

    return true;
}

void ModelClass::ShutdownBuffers()
{
    if(m_indexBuffer)
    {
        m_indexBuffer->Release();
        m_indexBuffer = 0;
    }
    
    if(m_vertexBuffer)
    {
        m_vertexBuffer->Release();
        m_vertexBuffer = 0;
    }

    return;
}

void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
    unsigned int stride;
    unsigned int offset;
    
    stride = sizeof(VertexType);
    offset = 0;
    
    deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
    deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    
    return;
}
