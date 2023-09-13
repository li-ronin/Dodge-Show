#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Collision.h"
#include "ECS/Components.h"


Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());

enum  groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

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
	// ��player Entity�������
	Map::LoadMap("assets/pyxel_16x16.map", 16, 16);
	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("assets/right.png",3,100);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);//��entity���뵽���Ǹ��Ե�group�У�Ȼ��˳����Ⱦ
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

	for (auto a : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *a);	
	}
	
}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

void Game::render()
{
	// ע��Render��˳�����Ҫ����������map����map�Ḳ������������
	SDL_RenderClear(renderer);
	// manager.draw();
	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& e : enemies)
	{
		e->draw();
	}
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
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	tile.addGroup(groupMap);
}