#include "mapSite.h"
/*
参与者:     
    Prototype 声明一个克隆自身的接口
    ConcretePrototype 实现一个克隆自身的操作
    Client 让一个原型克隆自身从而创建一个新的对象
*/

// ============================================类定义 =============================================================//

// class MazePrototypeFactory : public MazeFactory
// {
// public:
//     MazePrototypeFactory(Maze*, Wall*, Room*, Door*);

//     virtual Maze* MakeMaze() const;
//     virtual Room* MakeRoom(int) const;
//     virtual Wall* MakeWall() const;
//     virtual Door* MakeDoor(Room*, Room*) const;

// private:
//     Maze* _prototypeMaze;
//     Room* _prototypeRoom;
//     Wall* _prototypeWall;
//     Door* _prototypeDoor;
// };

MazePrototypeFactory::MazePrototypeFactory( Maze *m, Wall *w, Room *r, Door *d)
{
    _prototypeMaze = m;
    _prototypeWall = w;
    _prototypeRoom = r;
    _prototypeDoor = d;
}

Wall* MazePrototypeFactory::MakeWall() const
{
    return _prototypeWall -> Clone();
}

Door* MazePrototypeFactory::MakeDoor(Room *r1, Room *r2) const
{
    Door* door = _prototypeDoor -> Clone();
    door -> Initialize(r1, r2);
    return door;
}


// 使用方法
// MazeGame game;
// MazePrototypeFactory simpleMazeFactory( new Maze, new Wall, new Room, new Door);
// MazePrototypeFactory bombedMazeFactory( new Maze, new BombedWall, new RoomWithABomb, New Door);
// Maze *maze = game.CreateMaze(simpleMazeFactory);

// 一个可以被用作原型的对象，例如Wall的实例，必须支持Clone操作，还必须有一个拷贝构造器用于克隆， 还可能需要一个独立的操作来重新初始化内部的状态

// 此为为了适配prototype而修改后的Door， 未修改非必要的代码，但修改方式同下
// class Door : public MapSite
// {
// public:
//     Door(Room* = 0, Room* = 0);
//     Door(const Door& other) : _room1(other._room1), _room2(other._room2) {}

//     virtual void Initialize(Room* r1, Room* r2) 
//     {
//         _room1 = r1;
//         _room2 = r2;
//     }
//     virtual Door* Clone() const { return new Door(*this);}
//     virtual void Enter();
//     Room* OtherSideFrom(Room*);

// private:
//     Room* _room1;
//     Room* _room2;
//     bool _isOpen;
// };

