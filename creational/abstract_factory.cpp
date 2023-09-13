#include "mapSite.h"
/*
alias : kit
参与者:     
    AbstractFactory 声明一个创建抽象产品对象的接口
    ConcreteFactory 实现创建具体产品对象的操作
    AbstractProduct 为一产品对象声明一个接口
    ConcreteProduct 定义一个被相应的具体工厂创建的产品对象, 实现AbstractProduct接口
*/

// ============================================类定义 =============================================================//
    
// class MazeFactory
// {
// public:
//     MazeFactory();

//     virtual Maze* MakeMaze() const
//     { return new Maze; }

//     virtual Wall* MakeWall() const
//     { return new Wall;}

//     virtual Room* MakeRoom(int n) const
//     { return new Room(n); }

//     virtual Door* MakeDoor(Room *r1, Room *r2) const
//     { return new Door(r1, r2); }
// };

class EnchantedMazeFactory : public MazeFactory
{
public:
    EnchantedMazeFactory();

    virtual Room* MakeRoom(int n) const
    { return new EnchantedRoom(n, CastSpell()); }
    
    virtual Door* MakeDoor(Room *r1, Room *r2) const
    { return new DoorNeedingSpell(r1, r2); }

protected:
    Spell* CastSpell() const;
};

class BombedMazeFactory : public MazeFactory
{
public:
    virtual Wall* MakeWall() const
    { return new BombedWall; }

    virtual Room* MakeRoom(int n) const 
    { return new RoomWithABomb(n); }
    
};

Maze* MazeGame::CreateMaze (MazeFactory& factory)
{
    Maze* aMaze = factory.MakeMaze();
    Room* r1 = factory.MakeRoom(1);
    Room* r2 = factory.MakeRoom(2);
    Door* aDoor = factory.MakeDoor(r1, r2);

    aMaze -> AddRoom(r1);
    aMaze -> AddRoom(r2);

    r1 -> SetSide(North, factory.MakeWall());
    r1 -> SetSide(East, aDoor);
    r1 -> SetSide(South, factory.MakeWall());
    r1 -> SetSide(West, factory.MakeWall());
    
    r2 -> SetSide(North, factory.MakeWall());
    r2 -> SetSide(East, factory.MakeWall());
    r2 -> SetSide(South, factory.MakeWall());
    r2 -> SetSide(West, aDoor);

    return aMaze;
}

