#pragma once
#include<string>
#include<vector>
#include<memory>
#include<algorithm>
#include<bitset>
#include<array>

/*
 ECS(Entity - Component - System)��һ�����ģʽ��
 ������Ĺ��ֽܷ�Ϊ���������Ĳ��֣�Entity��Component��System��������ߴ���Ŀ�ά���ԡ�����Ժ����ܡ�

1����Entity��		: ʵ�塣 ���Կ�����һ����ʶ������һΨһ�ı�ǩ��Entity����û���κ���Ϊ���ܣ��������ڱ�ʶһ������

2����Component��		: ����� ��ʵ��Ĺ��ܵ�Ԫ����������ʵ����ض���Ϊ�����ԡ�
					  ������Ը��ӵ�һ������ʵ���ϡ����磬�����λ���������Ⱦ�������ײ����ȡ����֮���Ƕ����ģ�û��ֱ����ϵ��

3����System��		: ϵͳ�� �Ǵ���ʵ�������ĺ��Ĳ��֡�ϵͳ��һ���߼��ļ��ϣ����ڴ���һ���ض��������������Ⱦϵͳ����ײ���ϵͳ�ȡ�
					  ϵͳ��ÿ����Ϸѭ�������У�������������ݽ��д���������ʵ���״̬��
					  ϵͳ֮�����໥�����ģ����ǿ��Բ������У��Ӷ�������ܡ�

		��һ��ECSϵͳ�У���ͬ��ʵ�壨Entities����������������Component��϶��ɡ�
		���磬����һ����ҽ�ɫ�������ܰ������Component��
			SpriteComponent	��������Ⱦ��ҽ�ɫ����ۣ���
			PhysicsComponent�����ڴ�����ҽ�ɫ��������ײ����
			InputComponent	������������룩�ȡ�����
		��ЩComponentЭͬ������Ϊʵ�帳���˲�ͬ�Ĺ��ܡ�

*/

class Entity;
class Component;
class Manager;
using ComponentID = std::size_t;
using GroupID = std::size_t;

constexpr ComponentID maxComponent = 32;
constexpr GroupID maxGroup = 32;

using ComponentBitSet = std::bitset<maxComponent>;
using GroupBitSet = std::bitset<maxGroup>;

using ComponentArray = std::array<Component*, maxComponent>;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

// ComponentID id1 = getComponentID<PositionComponent>(); ÿ�����͵�������ID
template <typename T>
inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}


// Component����һ��������࣬������������Component�Ļ�����Ϊ�����ԡ�
class Component
{
public:
	Entity* entity;
	virtual  ~Component() = default;

	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};

};


// ECS���ģʽͨ����ʵ��(Entity)���Ϊ���������Component��ʹ����Ϸ�������ܹ���������ƺ����ʵ�����Ϊ
class Entity
{
private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;
	ComponentArray componentArr;
	ComponentBitSet componentBitset;
	GroupBitSet groupBitset;
public:
	Entity(Manager& mManager) : manager(mManager){}
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
	bool hasGroup(GroupID mGroup)
	{
		return groupBitset[mGroup];
	}
	void addGroup(GroupID mGroup);
	void delGroup(GroupID mGroup)
	{
		groupBitset[mGroup] = false;
	}
	/*
	����ĳһEntity����û�����Component<???>
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



/*Manager�ࣺ Manager����ECSģʽ�ĺ������֮һ����ͨ���������ֹ���������EntityManager��ComponentManager��SystemManager�ȡ�
 
	EntityManager�� ���𴴽������ٺ͹���ʵ�壨Entities����ά��ʵ����б�Ϊÿ��ʵ�����Ψһ�ı�ʶ�����Լ�����ʵ����������ڡ�

	ComponentManager�� ���������ֲ�ͬ���͵������Components����������Ϊÿ���������ά��һ���洢�ռ䣬�����������ӡ�ɾ���Ͳ�ѯ�Ȳ�����

	SystemManager�� �������ϵͳ��Systems����ϵͳ�Ǵ���ʵ������֮�佻���߼���ģ�顣ϵͳ���Ը�����Ҫ�����ض����͵�ʵ�壬��ʵ����Ϸ�߼���
*/
class Manager 
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroup> groupedEntities;
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
		for (auto i(0u); i<maxGroup; i++)
		{
			auto& v(groupedEntities[i]); // vector<Entity*> v
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity) 
					{
						return !mEntity->isActive() || !mEntity->hasGroup(i);
					}),
					std::end(v)
			);
		}
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

	void AddToGroup(Entity* mEntity, GroupID mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(GroupID mGroup)
	{
		return groupedEntities[mGroup];
	}

	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return * e;
	}
};