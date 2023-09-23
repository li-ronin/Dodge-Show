#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Collision.h"
#include "ECS/Components.h"



const char* mapfile="assets/map.png";
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::vector<ColliderComponent*> Game::colliders;
bool Game::isRunning = false;
auto& player(manager.addEntity());

enum  groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};
auto& players(manager.getGroup(groupPlayers));
auto& tiles(manager.getGroup(groupMap));
auto& enemies(manager.getGroup(groupEnemies));

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

	Map::LoadMap("assets/map.map", 25, 20);
	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("assets/timo.png", true);
	player.addComponent<KeyboardController>();
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
	manager.refresh();
	manager.update();	
	Vector2D playerVelocity = player.getComponent<TransformComponent>().velocity;
	int playerSpeed = player.getComponent<TransformComponent>().speed;
	// tiles是vector<Entity*>
	for(auto t : tiles)
	{	
		t->getComponent<TileComponent>().destRect.x -= playerVelocity.x * playerSpeed;
		t->getComponent<TileComponent>().destRect.y -= playerVelocity.y * playerSpeed;
	}
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

void Game::AddTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, mapfile);
	//将entity加入到它们各自的group中，然后按顺序渲染
	tile.addGroup(groupMap);
}