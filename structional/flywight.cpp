/*
    参与者:
            FlyWeight 描述一个接口，通过这个接口flyweight可以接受并作用于外部状态
            ConcreteFlyWeight 实现Flyweight接口,并为内部状态增加存储空间. ConcreteFlyweight对象必须是可共享的。它所存储的状态必须是内部的
            UnsharedConcreteFlyweight 并非所有的Flyweight子类都需要被共享
            FlyweightFactory 创建并管理flyweight对象，确保合理地共享flyweight. 当用户请求一个flyweight时，FlyweightFactory对象提供一个已创建的实例或者创建一个
            Client 维持一个对flyWeight的引用, 计算或存储一个flyweight的外部状态

    动机: 
            将可复用的大量细粒度对象放进一个池子里，优先使用池子中的对象而不去创建，以此来节约空间
*/
/*=======================================================类声明============================================================*/
class Window;
class GlyphContext;
class Font;
class BTree;
class Row;
class Column;

class Glyph
{
public:
    virtual ~Glyph();

    virtual void Draw(Window*, GlyphContext&);

    virtual void SetFont(Font*, GlyphContext&);
    virtual Font* GetFont(GlyphContext&);
    virtual void First(GlyphContext&);
    virtual void Next(GlyphContext&);
    virtual bool IsDone(GlyphContext&);
    virtual Glyph *current(GlyphContext&);

    virtual void Insert(Glyph*, GlyphContext&);
    virtual void Remove(GlyphContext&);
};

class Character : public Glyph
{
public:
    Character(char);

    virtual void Draw(Window*, GlyphContext&);
private:
    char _charcode;
};

class GlyphContext
{
public:
    GlyphContext();
    virtual ~GlyphContext();

    virtual void Next(int setp = 1);
    virtual void Insert(int quantity = 1);

    virtual Font* GetFont();
    virtual void SetFont(Font*, int span = 1);
private:
    int _index;
    BTree *_fonts;
};

const int NCHARCODES = 128;

class GlyphFactory
{
public:
    GlyphFactory();
    virtual ~GlyphFactory();
    virtual Character* CreateCharacter(char);
    virtual Row* CreateRow();
    virtual Column* CreateColumn();
    // ...
private:
    Character* _character[NCHARCODES];
};

GlyphFactory::GlyphFactory()
{
    for (int i = 0; i < NCHARCODES; ++i)
    {
        _character[i] = 0;
    }
}

Character* GlyphFactory::CreateCharacter(char c)
{
    if (!_character[c])
    {
        _character[c] = new Character(c);
    }

    return _character[c];
}

// Row* GlyphFactory::CreateRow()
// {
//     return new Row;
// }

// Column* GlyphFactory::CreateColumn() 
// {
//     return new Column;
// }
