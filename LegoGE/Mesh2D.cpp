#include "Mesh2D.h"

namespace LGE {
	
	Mesh2D::Mesh2D(size_t numVertices, size_t numIndices )
	{
		
		m_vertices = new Vertex[numVertices];
		m_indices = new unsigned int[numIndices];
		m_indicesSize = numIndices;
		m_verticesSize = numVertices;
	}

	Mesh2D::~Mesh2D()
	{
		delete[] m_vertices;
		delete[] m_indices;
		m_vertices = nullptr;
		m_indices = nullptr;
		
	}

	void Mesh2D::SetVertex(Vertex v, size_t index) {
		m_vertices[index] = v;

	}

	void Mesh2D::SetIndexBuffer(unsigned int* buffer)
	{
		m_indices = buffer;


	}
	


	float* Mesh2D::SerialzeToBuffer(size_t* bufferSize)
	{
		size_t size = LGE_2DVERTEX_SIZE * m_verticesSize;
		float *out = new float[size];
		*bufferSize = size;
		for (int i = 0; i < m_verticesSize; i++) {
			Vertex v = m_vertices[i];
			out[(i * LGE_2DVERTEX_SIZE) + 0] = (v.x * m_transform->GetSize().x) + m_transform->GetPosition().x;
			out[(i * LGE_2DVERTEX_SIZE) + 1] = (v.y * m_transform->GetSize().y) + m_transform->GetPosition().y;
			out[(i * LGE_2DVERTEX_SIZE) + 2] = v.z;
			out[(i * LGE_2DVERTEX_SIZE) + 3] = v.w;
		}
		return out;

	}

	void Mesh2D::LoadIntoVertexBuffer(VertexBuffer* buffer, unsigned int offset)
	{
		size_t size;
		float* vertices = SerialzeToBuffer(&size);
		m_offset = buffer->BufferData(vertices, size);

	}

	void Mesh2D::LoadIntoIndexBuffer(IndexBuffer* buffer, unsigned int offset)
	{
		buffer->BufferData(GetIndices(), GetNumIndices());

	}

	Mesh2D* Mesh2D::quad()
	{
		
		Transform* t = new Transform(glm::vec3(0.0f), glm::vec3(100.0f));


		Mesh2D* quad = new Mesh2D(4,6,t);
		quad->SetIndexBuffer(new unsigned int[6]{ 0,1,2,2,3,0 });
		quad->SetVertex(Vertex(0, 0,0.0f,1.0f), 0); //Top left
		quad->SetVertex(Vertex(1, 0, 0.0f,1.0f), 1); //Top right
		quad->SetVertex(Vertex(1, 1, 0.0f,1.0f), 2); // Bottom right
		quad->SetVertex(Vertex(0, 1, 0.0f,1.0f), 3); //Bottom left
		return quad;
	}

	/*Mesh2D* Mesh2D::triangle()
	{
		Mesh2D* triangle = new Mesh2D(3,3);
		triangle->SetIndexBuffer(new unsigned int[3]{ 0,1,2 });
		triangle->SetVertex(Vertex(-0.5f, -0.5f, 0.0f), 0);
		triangle->SetVertex(Vertex(0.5f, -0.5f, 0.0f), 1);
		triangle->SetVertex(Vertex(0.0f, 0.5f, 0.0f), 2);
		return triangle;
	}*/


	LGE_RESULT Mesh2D::GenerateVertexBuffer()
	{
		size_t size = 0;
		float* vertices = SerialzeToBuffer(&size);
		//m_vertexBuffer = new VertexBuffer(vertices,size);

		return LGE_OK;
	}
	LGE_RESULT Mesh2D::GenerateIndexBuffer()
	{
		//m_indexBuffer = new IndexBuffer(GetIndices(), GetNumIndices());
		return LGE_OK;
	}

}


