#pragma once
#include<string>
#include<vector>
#include<memory>
#include<algorithm>
#include<bitset>
#include<array>

/*
 ECS(Entity - Component - System)是一种设计模式。
 将对象的功能分解为三个独立的部分（Entity、Component、System），以提高代码的可维护性、灵活性和性能。

1、【Entity】		: 实体。 可以看作是一个标识符或者一唯一的标签。Entity本身没有任何行为或功能，它仅用于标识一个对象

2、【Component】		: 组件。 是实体的功能单元，用于描述实体的特定行为或属性。
					  组件可以附加到一个或多个实体上。比如，物体的位置组件、渲染组件、碰撞组件等。组件之间是独立的，没有直接联系。

3、【System】		: 系统。 是处理实体和组件的核心部分。系统是一组逻辑的集合，用于处理一类特定的组件，例如渲染系统、碰撞检测系统等。
					  系统在每个游戏循环中运行，根据组件的数据进行处理，并更新实体的状态。
					  系统之间是相互独立的，它们可以并行运行，从而提高性能。

		在一个ECS系统中，不同的实体（Entities）由它们所包含的Component组合而成。
		例如，你有一个玩家角色，它可能包含多个Component：
			SpriteComponent	（用于渲染玩家角色的外观）、
			PhysicsComponent（用于处理玩家角色的物理碰撞）、
			InputComponent	（处理玩家输入）等……。
		这些Component协同工作，为实体赋予了不同的功能。

*/

class Entity;
class Component;

using ComponentID = std::size_t;
using GroupID = std::size_t;
constexpr ComponentID maxComponent = 32;
using ComponentBitSet = std::bitset<maxComponent>;
using ComponentArray = std::array<Component*, maxComponent>;

inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

// ComponentID id1 = getComponentID<PositionComponent>(); 每个类型单独计算ID
template <typename T>
inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}


// Component类是一个抽象基类，它定义了所有Component的基本行为和属性。
class Component
{
public:
	Entity* entity;
	virtual  ~Component() = default;

	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};

};


// ECS设计模式通过将实体(Entity)拆分为多个独立的Component，使得游戏开发者能够更灵活地设计和组合实体的行为
class Entity
{
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;
	ComponentArray componentArr;
	ComponentBitSet componentBitset;

public:
	void update()
	{
		for (auto& c : components)c->update();
		

	}
	void draw()
	{
		for (auto& c : components)c->draw();
	}
	bool isActive() 
	{
		return active; 
	}
	void destory()
	{
		active = false;
	}
	
	/*
	查找某一Entity中有没有组件Component<???>
	*/
	template<typename T>  
	bool hasComponent() const
	{
		return componentBitset[getComponentTypeID<T>()];
	}

	// 
	template<typename T, typename... TArgs> 
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));
		componentArr[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;
		c->init();
		return *c;
	}

	template<typename T> 
	T& getComponent() const
	{
		auto ptr(componentArr[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
	//MasterPlayer.getComponent<PositionComponent>().setXpos(25);
};



/*Manager类： Manager类是ECS模式的核心组成之一，它通常包括各种管理器，如EntityManager、ComponentManager、SystemManager等。
 
	EntityManager： 负责创建、销毁和管理实体（Entities）。维护实体的列表，为每个实体分配唯一的标识符，以及管理实体的生命周期。

	ComponentManager： 负责管理各种不同类型的组件（Components）。它可以为每个组件类型维护一个存储空间，处理组件的添加、删除和查询等操作。

	SystemManager： 负责管理系统（Systems），系统是处理实体和组件之间交互逻辑的模块。系统可以根据需要更新特定类型的实体，以实现游戏逻辑。
*/
class Manager 
{
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void update()
	{
		for (auto& e : entities)
		{
			e->update();
		}
	}
	void draw()
	{
		for (auto& e : entities)
		{
			e->draw();
		}
	}
	void refresh()
	{
		entities.erase(
			std::remove_if(std::begin(entities), 
			std::end(entities),
			[](const std::unique_ptr<Entity> &mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities)
			);
	}
	Entity& addEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return * e;
	}
};