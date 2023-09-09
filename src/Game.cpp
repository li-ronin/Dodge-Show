#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Collision.h"
#include "ECS/Components.h"


Map* map1;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::vector<ColliderComponent*> Game::colliders;


auto& player(manager.addEntity());
auto& wall(manager.addEntity());
auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());

Game::Game()
{

}

Game::~Game()
{

}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	// ȫ��
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	// ��ʼ��
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// ��������
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		// ������Ⱦ��
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			// ������Ⱦ������ɫ
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		//backgroundTexture = IMG_LoadTexture(renderer, "assets/map.png");
		// ������Ϸ
		isRunning = true;
	}
	
	//player1 = new GameObject("assets/11.png", 0, 0);
	//player2 = new GameObject("assets/22.png", 300, 300);
	//player1->init();
	//player2->init();
	map1 = new Map();

	// ��player Entity�������
	
	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("assets/11.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	wall.addComponent<TransformComponent>(100.0f, 300.0f, 300, 32, 1);
	wall.addComponent<SpriteComponent>("assets/wall.png");
	wall.addComponent<ColliderComponent>("wall");

	tile0.addComponent<TileComponent>(200, 100, 64, 32, 0);
	//tile0.addComponent<ColliderComponent>("nitu");
	tile1.addComponent<TileComponent>(200, 200, 64, 32, 1);
	tile1.addComponent<ColliderComponent>("cao");
	tile2.addComponent<TileComponent>(200, 300, 64, 32, 2);
	tile2.addComponent<ColliderComponent>("qiang");
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		// ��ESC�л�ȫ��ģʽ
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			Uint32 flags = SDL_GetWindowFlags(window);
			if (flags & SDL_WINDOW_FULLSCREEN)
			{
				SDL_SetWindowFullscreen(window, 0);						// �л�������ģʽ
			}
			else
			{
				SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN); // �л���ȫ��ģʽ
			}
		}
		break;
	default:
		break;
	}
}


void Game::update()
{
	manager.refresh();
	manager.update();	
	if (Collision::AABB(player.getComponent<ColliderComponent>(),
		wall.getComponent<ColliderComponent>()))
	{
		player.getComponent<TransformComponent>().velocity * -1;

	}
	for (auto a : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *a);
		
			
		
	}
	
}

void Game::render()
{
	// ע��Render��˳�����Ҫ����������map����map�Ḳ������������
	SDL_RenderClear(renderer);
	//SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
	//map1->DrawMap();
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

void Game::AddTile(int id, int x, int y)
{

}