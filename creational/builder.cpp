#include "mapSite.h"

/*
参与者:
    Builder 为创建一个product对象的各个部件指定抽象接口
    ConcreteBuilder 实现Builder的接口以构造和装配该产品的各个部件
                    定义并明确它所创建的表示
                    提供一个检索产品的接口
    Director 构建一个使用Builder接口的对象
    Product 表示被构造的复杂对象
            包含定义组成部件的类，包括将这些部件装配成最终产品的接口
*/

// ============================================类定义 =============================================================//

// class MazeBuilder
// {
// public:
//     virtual void BuilderMaze() {}
//     virtual void BuilderRoom(int room) {}
//     virtual void BuilderDoor(int roomFrom, int roomTo) {}

//     virtual Maze* GetMaze() { return 0;}
// };

// 普通迷宫构造器
class StandardMazeBuilder : public MazeBuilder
{
public:
    StandardMazeBuilder();

    virtual void BuildMaze();
    virtual void BuildRoom(int);
    virtual void BuildDoor(int, int);
    virtual Maze* GetMaze();

private:
    Direction CommonWall(Room*, Room*);
    Maze* _currentMaze;
};

StandardMazeBuilder::StandardMazeBuilder()
{
    _currentMaze = 0;
}

void StandardMazeBuilder::BuildMaze()
{
    _currentMaze = new Maze;
}

Maze* StandardMazeBuilder::GetMaze()
{
    return _currentMaze;
}

void StandardMazeBuilder::BuildRoom(int n )
{
    if (!_currentMaze -> RoomNo(n))
    {
        Room *room = new Room(n);
        _currentMaze -> AddRoom(room);

        room -> SetSide(North, new Wall);
        room -> SetSide(South, new Wall);
        room -> SetSide(East, new Wall);
        room -> SetSide(West, new Wall);
    }
}

void StandardMazeBuilder::BuildDoor(int n1, int n2)
{
    Room *r1 = _currentMaze -> RoomNo(n1);
    Room *r2 = _currentMaze -> RoomNo(n2);

    Door *d = new Door(r1, r2);
    r1 -> SetSide(CommonWall(r1, r2), d);
    r2 -> SetSide(CommonWall(r2, r1), d);
}


// 计数迷宫构造器
class CountingMazeBuilder : public MazeBuilder
{
public:
    CountingMazeBuilder();

    virtual void BuildMaze();
    virtual void BuildRoom(int);
    virtual void BuildDoor(int, int);
    virtual void AddWall(int, Direction);

    void GetCounts(int&, int&) const;
private:
    int _doors;
    int _rooms;
};

CountingMazeBuilder::CountingMazeBuilder()
{
    _rooms = _doors = 0;
}

void CountingMazeBuilder::BuildRoom(int)
{
    _rooms++;
}

void CountingMazeBuilder::BuildDoor(int, int)
{
    _doors++;
}

void CountingMazeBuilder::GetCounts(int &rooms, int &doors) const
{
    rooms = _rooms;
    doors = _doors;
}



// 构造迷宫
Maze* MazeGame::CreateMaze(MazeBuilder& builder)
{
    builder.BuildMaze();
    
    builder.BuildRoom(1);
    builder.BuildRoom(2);
    builder.BuildDoor(1, 2);

    return builder.GetMaze();
}




