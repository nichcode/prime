
#include "prime/prime.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <array>
#include <cstdlib>
#include <vector>

#define MAX_TEXTURE_SLOTS 16

// shaders
str s_vertexSrc = R"(

    #version 330 core

    layout(location = 0) in vec2 a_position;
    layout(location = 1) in vec4 a_color;
    layout (location = 2) in vec2 a_textureCoords;
    layout (location = 3) in float a_textureIndex;

    out vec4 v_color;
    out vec2 v_textureCoords;
    out float v_textureIndex;

    layout(std140) uniform projectionBlock
    {
	    mat4 u_viewProjection;
    };

    void main()
    {
        v_color = a_color;
        v_textureCoords = a_textureCoords;
        v_textureIndex = a_textureIndex;
        gl_Position = u_viewProjection * vec4(a_position, 0.0, 1.0);
    }
)";

// shaders
str s_pixelSrc = R"(

    #version 330 core

    layout(location = 0) out vec4 color;

    in vec4 v_color;
    in vec2 v_textureCoords;
    in float v_textureIndex;

    uniform sampler2D u_textures[16];

    void main()
    {
        switch(int(v_textureIndex))
        {
            case 0: color = texture(u_textures[0], v_textureCoords) * v_color; break;
            case 1: color = texture(u_textures[1], v_textureCoords) * v_color; break;
            case 2: color = texture(u_textures[2], v_textureCoords) * v_color; break;
            case 3: color = texture(u_textures[3], v_textureCoords) * v_color; break;
            case 4: color = texture(u_textures[4], v_textureCoords) * v_color; break;
            case 5: color = texture(u_textures[5], v_textureCoords) * v_color; break;
            case 6: color = texture(u_textures[6], v_textureCoords) * v_color; break;
            case 7: color = texture(u_textures[7], v_textureCoords) * v_color; break;
            case 8: color = texture(u_textures[8], v_textureCoords) * v_color; break;
            case 9: color = texture(u_textures[9], v_textureCoords) * v_color; break;
            case 10: color = texture(u_textures[10], v_textureCoords) * v_color; break;
            case 11: color = texture(u_textures[11], v_textureCoords) * v_color; break;
            case 12: color = texture(u_textures[12], v_textureCoords) * v_color; break;
            case 13: color = texture(u_textures[13], v_textureCoords) * v_color; break;
            case 14: color = texture(u_textures[14], v_textureCoords) * v_color; break;
            case 15: color = texture(u_textures[15], v_textureCoords) * v_color; break;
        }
    }
)";

class Renderer2D;

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
		glm::vec2 texCoords;
		f32 texIndex;
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

		std::array<prime::Ref<prime::Texture2D>, MAX_TEXTURE_SLOTS> textureSlots{};
		u32 textureIndex = 1;
	};

	prime::Ref<prime::Context> m_context;
	prime::Device* m_device;
	glm::vec4 m_vertices[4]{};
	glm::vec2 m_texCoords[4]{};
	glm::mat4 m_matrix{};
	glm::mat4 m_identity;
	Data m_data;

public:
	Renderer2D() : m_device(nullptr)
	{
		m_identity = glm::mat4(1.0f);
	}

	void Init(prime::Device* device, prime::Window* window);
	void Shutdown();

	void SetClearColor(u8 r, u8 g, u8 b, u8 a);
	void Clear();

	void SetViewport(prime::Viewport& viewport);
	void SetLogicalSize(prime::Viewport& viewport);

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

	void SetBlendmode(prime::Blendmode blendmode)
	{
		m_context->SetBlendmode(blendmode);
	}

	void Draw(const prime::Rect& rect, const Color& color);
	void Draw(prime::Rect& rect, prime::Ref<prime::Texture2D>& texture, const Color& color = { 255, 255, 255, 255 });
	void Present();

private:
	f32 GetTextureIndex(prime::Ref<prime::Texture2D>& texture);
};

void Renderer2D::Init(prime::Device* device, prime::Window* window)
{
	m_device = device;
	m_context = device->CreateContext(window);
	m_context->SetVSync(true);

	prime::VertexbufferLayout layout;
	layout.AddBufferElement({ prime::DataTypeFloat2 });
	layout.AddBufferElement({ prime::DataTypeFloat4 });
	layout.AddBufferElement({ prime::DataTypeFloat2 });
	layout.AddBufferElement({ prime::DataTypeFloat });
	layout.ProcessElements();

	m_vertices[0] = { 0.0f,  0.0f, 0.0f, 1.0f };
	m_vertices[1] = { 1.0f,  0.0f, 0.0f, 1.0f };
	m_vertices[2] = { 1.0f,  1.0f, 0.0f, 1.0f };
	m_vertices[3] = { 0.0f,  1.0f, 0.0f, 1.0f };

	m_texCoords[0] = { 0.0f, 1.0f };
	m_texCoords[1] = { 1.0f, 1.0f };
	m_texCoords[2] = { 1.0f, 0.0f };
	m_texCoords[3] = { 0.0f, 0.0f };

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

	i32 samplers[MAX_TEXTURE_SLOTS]{};
	for (u32 i = 0; i < MAX_TEXTURE_SLOTS; i++) { samplers[i] = i; }

	m_data.shader->Bind();
	m_data.shader->SetIntArray("u_textures", samplers, MAX_TEXTURE_SLOTS);

	prime::Ref<prime::Texture2D> texture = device->CreateTexture2D(prime::TextureProperties());
	m_data.textureSlots[0] = texture;

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
	if (m_context->GetViewport() ==nullptr) {
		SetLogicalSize(viewport);
	}
	m_context->SetViewport(viewport);
}

void Renderer2D::SetLogicalSize(prime::Viewport& viewport)
{
	m_matrix = glm::ortho(viewport.x,
		(f32)viewport.width,
		(f32)viewport.height,
		viewport.y,
		-1.0f,
		1.0f);

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

		for (u32 i = 0; i < m_data.textureIndex; i++) {
			m_data.textureSlots[i]->Bind(i);
		}

		m_context->DrawIndexed(prime::PrimitiveTopologyTriangles, m_data.count);
	}

	m_data.count = 0;
	m_data.textureIndex = 1;
	m_data.vertexbufferPtr = m_data.vertexbufferBase;
}

void Renderer2D::Draw(const prime::Rect& rect, const Color& color)
{
	glm::vec4 rectColor = glm::vec4(0.0f);
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
		m_data.vertexbufferPtr->texCoords = m_texCoords[i];
		m_data.vertexbufferPtr->texIndex = 0.0f;
		m_data.vertexbufferPtr++;
	}
	m_data.count += 6;
}

void Renderer2D::Draw(prime::Rect& rect, prime::Ref<prime::Texture2D>& texture, const Color& color)
{
	glm::vec4 rectColor = glm::vec4(0.0f);
	rectColor.r = (f32)color.r / 255;
	rectColor.g = (f32)color.g / 255;
	rectColor.b = (f32)color.b / 255;
	rectColor.a = (f32)color.a / 255;

	glm::mat4 transform = glm::translate(m_identity, { rect.x, rect.y, 0.0f })
		* glm::scale(m_identity, { rect.width, rect.height, 1.0f });

	f32 textureIndex = 0.0f;
	if (texture.get()) { textureIndex = GetTextureIndex(texture); }

	for (size_t i = 0; i < 4; i++)
	{
		m_data.vertexbufferPtr->position = transform * m_vertices[i];
		m_data.vertexbufferPtr->color = rectColor;
		m_data.vertexbufferPtr->texCoords = m_texCoords[i];
		m_data.vertexbufferPtr->texIndex = textureIndex;
		m_data.vertexbufferPtr++;
	}
	m_data.count += 6;
}

void Renderer2D::Present()
{
	m_context->SwapBuffers();
}

f32 Renderer2D::GetTextureIndex(prime::Ref<prime::Texture2D>& texture)
{
	f32 textureIndex = 0.0f;
	for (uint32_t i = 1; i < m_data.textureIndex; i++)
	{
		if (m_data.textureSlots[i]->GetHandle() == texture->GetHandle())
		{
			textureIndex = (f32)i;
			break;
		}
	}

	if (textureIndex == 0.0f)
	{
		textureIndex = (f32)m_data.textureIndex;
		m_data.textureSlots[m_data.textureIndex] = texture;
		m_data.textureIndex++;
	}
	return textureIndex;
}

class PlayerBullet
{
	Renderer2D* m_renderer;
	prime::Ref<prime::Texture2D> m_texture;
	prime::Rect m_rect;
	f32 m_speed =  300.0f;
	b8 m_shouldDestroy = false;
	u32 m_ID;

public:
	PlayerBullet() : m_renderer(nullptr), m_ID(0) {}

	void Init(Renderer2D* renderer, prime::Ref<prime::Texture2D>& texture, f32 x, f32 y, u32 id)
	{
		m_texture = texture;
		m_rect.width = (f32)m_texture->GetWidth();
		m_rect.height = (f32)m_texture->GetHeight();
		m_rect.x = x;
		m_rect.y = y;

		m_ID = id;
		m_renderer = renderer;
	}

	void Render()
	{
		m_renderer->Draw(m_rect, m_texture);
	}

	void Update(f32 deltaTime)
	{
		const prime::Viewport* view = m_renderer->GetViewport();
		m_rect.y -= m_speed * deltaTime;

		if (m_rect.y + m_rect.height < view->y) {
			m_shouldDestroy = true;
		}
	}

	b8 ShouldDestroy() 
	{
		return m_shouldDestroy;
	}

	prime::Rect GetRect() const
	{
		return m_rect;
	}

	bool operator==(const PlayerBullet& b)
	{
		return m_ID == b.m_ID;
	}

	bool operator!=(const PlayerBullet& b)
	{
		return m_ID != b.m_ID;
	}
};

class Player
{
	Renderer2D* m_renderer;
	prime::Ref<prime::Texture2D> m_texture;
	prime::Rect m_rect;
	f32 m_speed = 300.0f;
	u32 m_bulletID;

public:
	Player() : m_renderer(nullptr), m_bulletID(0) {}

	void Init(Renderer2D* renderer, prime::Ref<prime::Texture2D> texture)
	{
		const prime::Viewport* view = renderer->GetViewport();
		m_texture = texture;
		m_rect.width = (f32)m_texture->GetWidth();
		m_rect.height = (f32)m_texture->GetHeight();
		m_rect.x = view->width / 2.0f - m_rect.width / 2.0f;
		m_rect.y = view->height - m_rect.height * 2.0f;
		m_renderer = renderer;
	}

	void Render()
	{
		m_renderer->Draw(m_rect, m_texture);
	}

	void Update(f32 deltaTime, prime::Window* window)
	{
		const prime::Viewport* view = m_renderer->GetViewport();

		if (window->GetKeyState(prime::Key_Right)) {
			m_rect.x += m_speed * deltaTime;

			if (m_rect.x > view->width) {
				m_rect.x = 0.0f - m_rect.width;
			}
		}

		else if (window->GetKeyState(prime::Key_Left)) {
			m_rect.x -= m_speed * deltaTime;

			if (m_rect.x + m_rect.width < view->x) {
				m_rect.x = view->width + m_rect.width;
			}
		}
	}

	void FireBullet(prime::Ref<prime::Texture2D> texture, std::vector<PlayerBullet>& bullets)
	{
		PlayerBullet bullet;
		f32 centerX = m_rect.x + (m_rect.width / 2.0f) - 5.0f;
		f32 centerY = m_rect.y - 15.0f;
		bullet.Init(m_renderer, texture, centerX, centerY, m_bulletID);
		bullets.emplace_back(bullet);

		m_bulletID++;
	}

	void Center()
	{
		const prime::Viewport* view = m_renderer->GetViewport();
		m_rect.x = view->width / 2.0f - m_rect.width / 2.0f;
		m_rect.y = view->height - m_rect.height * 2.0f;
	}

	prime::Rect GetRect() const
	{
		return m_rect;
	}
};

class Enemy
{
	Renderer2D* m_renderer;
	prime::Ref<prime::Texture2D> m_texture;
	prime::Rect m_rect;
	f32 m_speed = 150.0f;
	u32 m_ID;

public:
	Enemy() : m_renderer(nullptr), m_ID(0) {}

	void Init(Renderer2D* renderer, prime::Ref<prime::Texture2D>& texture, f32 x, f32 y, u32 id)
	{
		m_texture = texture;
		m_rect.width = (f32)m_texture->GetWidth();
		m_rect.height = (f32)m_texture->GetHeight();
		m_rect.x = x;
		m_rect.y = y;

		m_ID = id;
		m_renderer = renderer;
	}

	void Render()
	{
		m_renderer->Draw(m_rect, m_texture);
	}

	void Update(f32 deltaTime)
	{
		const prime::Viewport* view = m_renderer->GetViewport();

		m_rect.x += m_speed * deltaTime;

		if (m_rect.x + m_rect.width >= view->width) {
			m_rect.x -= 5.0f;
			m_speed *= -1;
		}
		else if (m_rect.x <= view->x) {
			m_rect.x += 5.0f;
	        m_speed *= -1;
		}
	}

	prime::Rect GetRect() const
	{
		return m_rect;
	}

	bool operator==(const Enemy& b)
	{
		return m_ID == b.m_ID;
	}

	bool operator!=(const Enemy& b)
	{
		return m_ID != b.m_ID;
	}
};

Player player;
prime::Ref<prime::Texture2D> pBulletTexture;
std::vector<PlayerBullet> playerBullets;
std::vector<Enemy> enemies;
prime::Ref<prime::Texture2D> enemyTexture;
Renderer2D renderer;
u32 enemiesCreated = 0;

f32 enemyPosX[5] = { 50.0f, 250.0f, 450.0f, 650.0f, 750.0f };
f32 enemyPosY[5] = { 100.0f, 150.0f, 200.0f, 250.0f, 200.0f };

void OnWindowResize(const prime::Window* w, u32 width, u32 height)
{
	Renderer2D* renderer = (Renderer2D*)w->GetUserData();
	prime::Viewport view;
	view.width = width;
	view.height = height;
	renderer->SetViewport(view);
}

void OnKey(const prime::Window* window, u16 key, i32 scancode, u8 action)
{
	if (key == prime::Key_Space && action == PPRESS) {
		player.FireBullet(pBulletTexture, playerBullets);
	}
}

void GenerateEnemies()
{
	while (enemies.size() < 5) {

		srand((u32)time(NULL));
		int random = rand() % 5;

		Enemy enemy;
		enemy.Init(&renderer, enemyTexture, enemyPosX[random], enemyPosY[random], enemiesCreated);
		enemies.emplace_back(enemy);

		enemiesCreated++;
	}
}

b8 GameTest()
{
	prime::Device device;
	device.Init(prime::DriverTypesOpenGL);

	prime::Window window;
	prime::WindowProperties props;
	props.title = "GameTest Window";
	props.width = 1000;
	props.height = 600;
	window.Init(props);

	renderer.Init(&device, &window);
	renderer.SetClearColor(40, 40, 40, 255);
	renderer.SetBlendmode(prime::BlendmodeBlend);

	window.SetUserData(&renderer);

	prime::Viewport viewport;
	viewport.width = window.GetWidth();
	viewport.height = window.GetHeight();
	renderer.SetViewport(viewport);

	prime::Ref<prime::Texture2D> playerTexture;
	playerTexture = device.CreateTexture2D("textures/player.png");
	player.Init(&renderer, playerTexture);

	prime::SetWindowResizeCallback(OnWindowResize);
	prime::SetWindowKeyCallback(OnKey);

	prime::Timestep timestep;
	enemyTexture = device.CreateTexture2D("textures/enemy.png");

	enemies.reserve(20);

	for (int x = 0; x < 5; x++) {
		Enemy enemy;
		enemy.Init(&renderer, enemyTexture, enemyPosX[x], enemyPosY[x], enemiesCreated);
		enemies.emplace_back(enemy);
		enemiesCreated++;
	}
	
	pBulletTexture = device.CreateTexture2D("textures/player_bullet.png");
	enemies.reserve(20);

	while (!window.ShouldClose())
	{
		prime::PollEvents();
		timestep.Tick();

		renderer.Clear();
		player.Update(timestep.GetDT(), &window);

		for (Enemy& enemy : enemies) {
			enemy.Update(timestep.GetDT());
			enemy.Render();
		}

		for (PlayerBullet& bullet : playerBullets) {
			bullet.Update(timestep.GetDT());
			bullet.Render();
		}

		for (PlayerBullet& bullet : playerBullets) {
			if (bullet.ShouldDestroy()) {
				auto itBullet = std::find(playerBullets.begin(), playerBullets.end(), bullet);
				if (itBullet != playerBullets.end()) {
					playerBullets.erase(itBullet);
				}
			}

			for (Enemy& enemy : enemies) {
				if (bullet.GetRect().CollideRect(enemy.GetRect())) {
					auto itBullet = std::find(playerBullets.begin(), playerBullets.end(), bullet);
					if (itBullet != playerBullets.end()) {
						playerBullets.erase(itBullet);
					}

					auto itEnemy = std::find(enemies.begin(), enemies.end(), enemy);
					if (itEnemy != enemies.end()) {
						enemies.erase(itEnemy);
					}
				}
			}
		}

		GenerateEnemies();

		player.Render();
		renderer.Flush();
		renderer.Present();
	}

	renderer.Shutdown();
	window.Destroy();
	enemies.clear();

	return PPASSED;
}
