#include "Renderer.h"
#include <glad/glad.h>
#include "DebugUtils.h"

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    va.Bind();
    ib.Bind();
    shader.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), ib.GetIndexType(), 0));
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
