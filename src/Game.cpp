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
	// 全屏
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	// 初始化
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// 创建窗口
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		// 创建渲染器
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			// 设置渲染器的颜色
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		//backgroundTexture = IMG_LoadTexture(renderer, "assets/map.png");
		// 启动游戏
		isRunning = true;
	}
	
	//player1 = new GameObject("assets/11.png", 0, 0);
	//player2 = new GameObject("assets/22.png", 300, 300);
	//player1->init();
	//player2->init();
	map1 = new Map();

	// 对player Entity插入组件
	
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
		// 按ESC切换全屏模式
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			Uint32 flags = SDL_GetWindowFlags(window);
			if (flags & SDL_WINDOW_FULLSCREEN)
			{
				SDL_SetWindowFullscreen(window, 0);						// 切换到窗口模式
			}
			else
			{
				SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN); // 切换到全屏模式
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
	// 注意Render的顺序很重要，若最后加载map，则map会覆盖在人物上面
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