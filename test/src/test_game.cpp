
#include "prime/prime.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// shaders
str s_vertexSrc = R"(

    #version 330 core

    layout(location = 0) in vec2 a_position;
    layout(location = 1) in vec4 a_color;

    out vec4 v_color;

    layout(std140) uniform projectionBlock
    {
	    mat4 u_viewProjection;
    };

    void main()
    {
        v_color = a_color;
        gl_Position = u_viewProjection * vec4(a_position, 0.0, 1.0);
    }
)";

// shaders
str s_pixelSrc = R"(

    #version 330 core

    layout(location = 0) out vec4 color;

    in vec4 v_color;

    void main()
    {
        color = v_color;
    }
)";

class Renderer2D;

class Rect2D
{
public:
	f32 x = 0.0f;
	f32 y = 0.0f;
	f32 width = 50.0f;
	f32 height = 50.0f;
};

struct Color
{
	u8 r;
	u8 g;
	u8 b;
	u8 a;

	Color()
	{
		this->r = 0;
		this->g = 0;
		this->b = 0;
		this->a = 0255;
	}

	Color(u8 r, u8 g, u8 b, u8 a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};

class Renderer2D
{
	struct SpriteVertex
	{
		glm::vec2 position;
		glm::vec4 color;
	};

	struct Data
	{
		prime::Ref<prime::Vertexbuffer> vertexbuffer;
		prime::Ref<prime::Indexbuffer> indexbuffer;
		prime::Ref<prime::Shader> shader;
		prime::Ref<prime::Uniformbuffer> uniformbuffer;

		SpriteVertex* vertexbufferBase = nullptr;
		SpriteVertex* vertexbufferPtr = nullptr;

		u32 maxSprites = 10000, count = 0;
		u32 maxVertices = maxSprites * 4;
		u32 maxIndices = maxSprites * 6;
	};

	prime::Ref<prime::Context> m_context;
	prime::Device* m_device;
	glm::vec4 m_vertices[4]{};
	glm::mat4 m_matrix{};
	glm::mat4 m_identity;
	prime::Viewport* m_view;
	Data m_data;

public:
	Renderer2D() : m_device(nullptr), m_view(nullptr) 
	{
		m_identity = glm::mat4(1.0f);
	}

	void Init(prime::Device* device, prime::Window* window);
	void Shutdown();

	void SetClearColor(u8 r, u8 g, u8 b, u8 a);
	void Clear();

	void SetViewport(prime::Viewport& viewport);

	const prime::Viewport* GetViewport()
	{
		const prime::Viewport* view = m_context->GetViewport();
		if (view) { return view; }
		else {
			PASSERT_MSG(false, "Viewport not found");
			return nullptr;
		}
	}

	void Flush();
	void Draw(Rect2D& rect, const Color& color);
	void Present();
};

void Renderer2D::Init(prime::Device* device, prime::Window* window)
{
	m_device = device;
	m_context = device->CreateContext(window);
	m_context->SetVSync(true);

	prime::VertexbufferLayout layout;
	layout.AddBufferElement({ prime::DataTypeFloat2 });
	layout.AddBufferElement({ prime::DataTypeFloat4 });
	layout.ProcessElements();

	m_vertices[0] = { 0.0f,  0.0f, 0.0f, 1.0f };
	m_vertices[1] = { 1.0f,  0.0f, 0.0f, 1.0f };
	m_vertices[2] = { 1.0f,  1.0f, 0.0f, 1.0f };
	m_vertices[3] = { 0.0f,  1.0f, 0.0f, 1.0f };

	/*m_vertices[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
	m_vertices[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
	m_vertices[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
	m_vertices[3] = { -0.5f,  0.5f, 0.0f, 1.0f };*/

	// indices
	u32* indices = new u32[m_data.maxIndices];
	u32 offset = 0;
	for (u32 i = 0; i < m_data.maxIndices; i += 6)
	{
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

	m_data.vertexbuffer = m_device->CreateVertexBuffer(nullptr, 
		m_data.maxVertices * sizeof(SpriteVertex),
		prime::VertexbufferTypeDynamic);

	m_data.vertexbuffer->Bind();
	m_data.vertexbuffer->SetLayout(layout);

	m_data.vertexbufferBase = new SpriteVertex[m_data.maxVertices];
	m_data.indexbuffer = device->CreateIndexBuffer(indices, m_data.maxIndices);
	m_data.indexbuffer->Bind();

	m_data.shader = device->CreateShader(s_vertexSrc, s_pixelSrc, false);
	m_data.uniformbuffer = device->CreateUniformbuffer(sizeof(glm::mat4), 0);

	delete[] indices;
	m_data.vertexbufferPtr = m_data.vertexbufferBase;
}

void Renderer2D::Shutdown()
{
	delete[] m_data.vertexbufferBase;
}

void Renderer2D::SetClearColor(u8 r, u8 g, u8 b, u8 a)
{
	f32 ndcR = (f32)r / 255;
	f32 ndcG = (f32)g / 255;
	f32 ndcB = (f32)b / 255;
	f32 ndcA = (f32)a / 255;
	m_context->SetClearColor(ndcR, ndcG, ndcB, ndcA);
}

void Renderer2D::Clear()
{
	m_context->Clear();
}

void Renderer2D::SetViewport(prime::Viewport& viewport)
{
	m_matrix = glm::ortho(viewport.x,
		(f32)viewport.width,
		(f32)viewport.height,
		viewport.y,
		-1.0f,
		1.0f);

	m_context->SetViewport(viewport);

	m_data.uniformbuffer->Bind();
	m_data.uniformbuffer->SetData(sizeof(glm::mat4), &m_matrix);
}

void Renderer2D::Flush()
{
	if (m_data.count)
	{
		u32 dataSize = (u32)((u8*)m_data.vertexbufferPtr - (u8*)m_data.vertexbufferBase);
		m_data.vertexbuffer->Bind();
		m_data.vertexbuffer->SetData(m_data.vertexbufferBase, dataSize);

		m_data.shader->Bind();
		m_context->DrawIndexed(prime::PrimitiveTopologyTriangles, m_data.count);
	}

	m_data.count = 0;
	m_data.vertexbufferPtr = m_data.vertexbufferBase;
}

void Renderer2D::Draw(Rect2D& rect, const Color& color)
{
	glm::vec4 rectColor;
	rectColor.r = (f32)color.r / 255;
	rectColor.g = (f32)color.g / 255;
	rectColor.b = (f32)color.b / 255;
	rectColor.a = (f32)color.a / 255;

	glm::mat4 transform = glm::translate(m_identity, { rect.x, rect.y, 0.0f })
		* glm::scale(m_identity, { rect.width, rect.height, 1.0f });

	for (size_t i = 0; i < 4; i++)
	{
		m_data.vertexbufferPtr->position = transform * m_vertices[i];
		m_data.vertexbufferPtr->color = rectColor;
		m_data.vertexbufferPtr++;
	}
	m_data.count += 6;
}

void Renderer2D::Present()
{
	m_context->SwapBuffers();
}

class Player
{
	Renderer2D* m_renderer;
	prime::Window* m_window;
	Rect2D m_rect;
	f32 m_speed = 200.0f;

public:
	Player() : m_renderer(nullptr), m_window(nullptr) {}

	void Init(Renderer2D* renderer, prime::Window* window)
	{
		const prime::Viewport* m_view = renderer->GetViewport();
		m_rect.width = 50.0f;
		m_rect.height = 50.0f;
		m_rect.x = m_view->width / 2.0f - m_rect.width / 2.0f;
		m_rect.y = m_view->height - m_rect.height * 2.0f;

		m_renderer = renderer;
		m_window = window;
	}

	void Render()
	{
		m_renderer->Draw(m_rect, Color(255, 0, 0, 255));
	}

	void Update(f32 deltaTime)
	{
		if (m_window->GetKeyState(prime::Key_Right)) {
			m_rect.x += m_speed * deltaTime;
		}

		else if (m_window->GetKeyState(prime::Key_Left)) {
			m_rect.x -= m_speed * deltaTime;
		}
	}

	void Center()
	{
		const prime::Viewport* m_view = m_renderer->GetViewport();
		m_rect.x = m_view->width / 2.0f - m_rect.width / 2.0f;
		m_rect.y = m_view->height - m_rect.height * 2.0f;
	}
};

void OnWindowResize(const prime::Window* w, u32 width, u32 height)
{
	Renderer2D* renderer = (Renderer2D*)w->GetUserData();
	prime::Viewport view;
	view.width = width;
	view.height = height;
	renderer->SetViewport(view);
}

b8 GameTest()
{
	prime::Device device;
	device.Init(prime::DriverTypesOpenGL);

	prime::Window window;
	prime::WindowProperties props;
	props.title = "GameTest Window";
	window.Init(props);

	Renderer2D renderer;
	renderer.Init(&device, &window);
	renderer.SetClearColor(40, 40, 40, 255);

	window.SetUserData(&renderer);

	prime::Viewport viewport;
	viewport.width = window.GetWidth();
	viewport.height = window.GetHeight();
	renderer.SetViewport(viewport);

	Player m_player;
	m_player.Init(&renderer, &window);

	prime::SetWindowResizeCallback(OnWindowResize);

	prime::Timestep timestep;

	while (!window.ShouldClose())
	{
		prime::PollEvents();
		timestep.Tick();

		m_player.Update(timestep.GetDT());

		renderer.Clear();
		m_player.Render();

		renderer.Flush();
		renderer.Present();
	}

	renderer.Shutdown();
	window.Destroy();

	return PPASSED;
}
