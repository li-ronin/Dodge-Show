#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Collision.h"
#include "ECS/Components.h"




SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera{0, 0, 800, 640};
//std::vector<ColliderComponent*> Game::colliders;
bool Game::isRunning = false;

Manager manager;
AssetManager* Game::assets = new AssetManager(&manager);
auto& player(manager.addEntity());


auto& players(manager.getGroup(Game::groupPlayers));
auto& tiles(manager.getGroup(Game::groupMap));
auto& collisions(manager.getGroup(Game::groupColliders));

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
	
	assets->AddTexture("terrain", "assets/map.png");
	assets->AddTexture("player", "assets/timo1.png");

	//const char* mapfile = "assets/map.png";
	Map* map = new Map("terrain", 2, 32);
	map->LoadMap("assets/map.map", 25, 20);

	player.addComponent<TransformComponent>(0, 0, 150, 150, 0.7);
	player.addComponent<SpriteComponent>("player", true);
	//player.addComponent<KeyboardController>();
	player.addComponent<MouseController>();
	player.addComponent<ColliderComponent>("player");
	// 将entity加入到它们各自的group中，然后按顺序渲染
	player.addGroup(groupPlayers);
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
		if (event.key.keysym.sym == SDLK_f)
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
	SDL_Rect playerCollider = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	manager.refresh();
	manager.update();	

	for (auto& c : collisions)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCollider))
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	camera.x = player.getComponent<TransformComponent>().position.x - 400;
	camera.y = player.getComponent<TransformComponent>().position.y - 320;
	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;
	if (camera.x > camera.w) camera.x = camera.w;
	if (camera.y > camera.h) camera.y = camera.h;

	// 判断player是否遇到障碍物
	//for (auto a : colliders)
	//{
	//	Collision::AABB(player.getComponent<ColliderComponent>(), *a);	
	//}
	
}


void Game::render()
{
	// 注意Render的顺序很重要，若最后加载map，则map会覆盖在人物上面
	SDL_RenderClear(renderer);
	// manager.draw();
	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& c : collisions)
	{
		c->draw();
	}
	for (auto& p : players)
	{
		p->draw();
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