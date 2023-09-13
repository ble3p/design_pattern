#include "mapSite.h"
/*
alias : Virtual Constructor
参与者:
    Product 定义工厂方法所创建的对象的接口
    ConcreteProduct 实现Product接口
    Creator 声明工厂方法, 该方法返回一个Product类型的对象. Creator也可以
定义一个工厂方法的缺省， 它返回一个缺省的ConcreteProduct对象
            可以调用工厂方法以创建一个Product对象
    ConcreteCreator 重定义工厂以返回一个ConcreteProduct
*/

// ============================================类定义 =============================================================//

// class MazeGameFactory
// {
// public:
//     Maze * CreateMaze();

//     // factory_methods make product;
//     virtual Maze* MakeMaze() const { return new Maze; }
//     virtual Room* MakeRoom(int n) const { return new Room(n); }
//     virtual Wall* MakeWall() const { return new Wall; }
//     virtual Door* MakeDoor(Room *r1, Room *r2) const { return new Door(r1,r2); }
// };

// 重定义CreateMaze:
Maze* MazeGameFactory::CreateMaze() 
{
    Maze *aMaze = MakeMaze();

    Room *r1 = MakeRoom(1);
    Room *r2 = MakeRoom(2);

    Door *theDoor = MakeDoor(r1, r2);

    aMaze -> AddRoom(r1);
    aMaze -> AddRoom(r2);

    r1 -> SetSide(North, MakeWall());
    r1 -> SetSide(East, theDoor);
    r1 -> SetSide(South, MakeWall());
    r1 -> SetSide(West, MakeWall());
    
    r2 -> SetSide(North, MakeWall());
    r2 -> SetSide(East, MakeWall());
    r2 -> SetSide(South, MakeWall());
    r2 -> SetSide(West, theDoor);
    return aMaze;
}

// 不同的游戏可以创建MazeGameFactory的子类以特别指明一些迷宫的部件
class BombedMazeGameFactory : public MazeGameFactory
{
public:
    BombedMazeGameFactory();

    virtual Wall* MakeWall() const { return new BombedWall;}
    virtual Room* MakeRoom(int n) const { return new RoomWithABomb(n);}
};

class EnchantedMazeGameFactory : public MazeGameFactory
{
public:
    EnchantedMazeGameFactory();

    virtual Room* MakeRoom(int n) const { return new EnchantedRoom(n, CastSpell()); }
    virtual Door* MakeDoor(Room *r1, Room *r2) const { return new DoorNeedingSpell(r1, r2); }
protected:
    Spell* CastSpell() const;
};

