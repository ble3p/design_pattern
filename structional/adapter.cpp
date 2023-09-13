/*
    alias : Wrapper
    参与者：
            Target 定义Client使用的与特定领域相关的接口
            Clinet 与Target接口的对象协同
            Adaptee 定义一个已经存在的接口，这个接口需要适配
            Adapter 对Adapter的接口与Target接口进行适配

*/
/* =======================================================类声明=========================================================*/
class TextView;
class TextShape;

/* =======================================================基础定义=========================================================*/
class Coord
{
public:
    Coord();
    Coord(int val);
    Coord operator+(Coord &rhs) { return coord_ + rhs.coord_; }
private:
    int coord_;
};

class Point
{
public:
    Point(Coord x, Coord y);
private:
    Coord coord_x;
    Coord coord_y;
};

class Manipulator
{
public:
    Manipulator();
    virtual void drag(Point &, Point &) ;
    
protected:
    TextView *mal_;
};

class TextManipulator : public Manipulator
{
public:
    TextManipulator();
    TextManipulator(const TextShape *);
    virtual void drag(Point &, Point &) {}
};


/* =======================================================target=========================================================*/
class Shape // Shape假定有一个边框，这个边框由它相对的两角bottomLeft, topRight定义
{
public:
    Shape();
    virtual void BoundingBox( Point &bottomLeft, Point &topRight) const;
    virtual Manipulator* CreateManipulator() const; // Manipulator 知道怎么去驱动图形
};

/* =======================================================Adaptee=========================================================*/
class TextView // TextView由原点(x, y)、 宽度width和高度height定义
{
public:
    TextView();
    void GetOrigin(Coord &x, Coord &y) const;
    void GetExtent(Coord &width, Coord &height) const;
    virtual bool IsEmpty() const;
};

/* =======================================================Adapter=========================================================*/
class TextShape : public Shape, private TextView //是不同接口之间的适配器
{
public:
    TextShape();

    virtual void BoundingBox(Point &bottomLeft, Point &topRight) const;
    virtual bool IsEmpty() const;
    virtual Manipulator* CreateManipulator() const;
};

void TextShape::BoundingBox(Point &bottomLeft, Point &topRight) const
{
    Coord bottom, left, width, height;

    GetOrigin(bottom, left);
    GetExtent(width, height);

    bottomLeft = Point(bottom, left);
    topRight = Point(bottom + height, left = width);
}

bool TextShape::IsEmpty() const
{
    return TextView::IsEmpty();
}

Manipulator* TextShape::CreateManipulator() const // 返回一个操作器，操作器实现原本adaptee没有的功能
{
    return new TextManipulator(this);
}
