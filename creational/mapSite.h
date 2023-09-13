enum Direction {North, South, East, West};
typedef char Spell;

/******************************************************基础设施**********************************************************/
class MapSite // 迷宫设施基类
{
public:
    virtual void Enter() = 0;
};

// 房间类
class Room : public MapSite // 普通房间
{
public:
    Room(int roomNo);

    MapSite* GetSide(Direction) const;
    void SetSide(Direction, MapSite*);

    virtual void Enter();

private:
    MapSite* _sides[4];
    int _roomNumber;
};

class EnchantedRoom : public Room // 魔法咒语房间
{
public:
    EnchantedRoom(int roomNo, Spell *spell);

    virtual void Enter();

private:
    Spell *_spell;
};

class RoomWithABomb : public Room // 炸弹房
{
public:
    RoomWithABomb(int roomNo);
    virtual void Enter();
private:
    int boom_time;
};

// 墙
class Wall : public MapSite
{
public:
    Wall();
    Wall(const Wall &other) {}

    virtual Wall* Clone() { return new Wall(*this); }
    virtual void Enter();
};

class BombedWall : public Wall
{
public:
    BombedWall();
    virtual void Enter();
private:
    bool _bomb;
};


// 门
class Door : public MapSite
{
public:
    Door(Room* = 0, Room* = 0);
    Door(const Door& other) : _room1(other._room1), _room2(other._room2) {}

    virtual void Initialize(Room* r1, Room* r2) 
    {
        _room1 = r1;
        _room2 = r2;
    }
    virtual Door* Clone() const { return new Door(*this);}
    virtual void Enter();
    Room* OtherSideFrom(Room*);

private:
    Room* _room1;
    Room* _room2;
    bool _isOpen;
};

class DoorNeedingSpell : public Door
{
public:
    DoorNeedingSpell(Room* = 0, Room* = 0);

    virtual void Enter();
private:
    Spell *_spell;
    
};


/******************************************************迷宫**********************************************************/
class Maze
{
    public: 
        Maze();
        
        void AddRoom(Room*);
        Room* RoomNo(int) const;
    private:
        // ...
};

/******************************************************abstract_factory**********************************************************/
class MazeFactory
{
public:
    MazeFactory();

    virtual Maze* MakeMaze() const
    { return new Maze; }

    virtual Wall* MakeWall() const
    { return new Wall;}

    virtual Room* MakeRoom(int n) const
    { return new Room(n); }

    virtual Door* MakeDoor(Room *r1, Room *r2) const
    { return new Door(r1, r2); }
};


/******************************************************builder**********************************************************/
class MazeBuilder
{
public:
    virtual void BuildMaze() {}
    virtual void BuildRoom(int room) {}
    virtual void BuildDoor(int roomFrom, int roomTo) {}

    virtual Maze* GetMaze() { return 0;}
};
/******************************************************factory_method**********************************************************/
// mapSite的子类Room、Door、Wall就充当着factory_method中的product 或是concreteProduct
// 其子类特殊的Room、Door、Wall就充当着concreteProduct
class MazeGameFactory
{
public:
    Maze * CreateMaze();

    // factory_methods make product;
    virtual Maze* MakeMaze() const { return new Maze; }
    virtual Room* MakeRoom(int n) const { return new Room(n); }
    virtual Wall* MakeWall() const { return new Wall; }
    virtual Door* MakeDoor(Room *r1, Room *r2) const { return new Door(r1,r2); }
};

/******************************************************prototype**********************************************************/
class MazePrototypeFactory : public MazeFactory
{
public:
    MazePrototypeFactory(Maze*, Wall*, Room*, Door*);

    virtual Maze* MakeMaze() const;
    virtual Room* MakeRoom(int) const;
    virtual Wall* MakeWall() const;
    virtual Door* MakeDoor(Room*, Room*) const;

private:
    Maze* _prototypeMaze;
    Room* _prototypeRoom;
    Wall* _prototypeWall;
    Door* _prototypeDoor;
};

/******************************************************singleton**********************************************************/
// 保证一个类仅有一个实例
// class MazeFactory
// {
// public:
//     static MazeFactory* Instance();
//     
// protected:
//     MazeFactory();
// private:
//     static MazeFactory* _instance;
// };

// MazeFactory* MazeFactory::_instance = 0;

// MazeFactory* MazeFactory::Instance()
// {
//     if (_instance == 0)
//     {
//         _instance = new MazeFactory;
//     }
//     return _instance;
// }


// 考虑多个子类的情况
// MazeFactory* MazeFactory::Instance() 
// {
//     if (_instance == 0)
//     {
//         const char *mazestyle = getenv("MAZESTYLE"); // 从环境变量中获取迷宫唯一实例

//         if (strcmp(mazestyle, "bombed") == 0 )
//         {
//             _instance = new BombedMazeFactory;
//         }
//         else if (strcmp(mazestyle, "enchanted") == 0)
//         {
//             _instance = new EnchantedMazeFactory;
//         }
//         // ........

//         else 
//         {
//             _instance = new MazeFactory;
//         }
//     }
// }


/******************************************************迷宫生成**********************************************************/
class MazeGame
{
public:
    Maze* CreateMaze();
    Maze* CreateMaze(MazeFactory &);
    Maze* CreateMaze(MazeBuilder &);
};
