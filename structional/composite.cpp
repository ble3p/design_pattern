/*
    参与者:
            Component 为组合中的对象声明接口, 在适当的情况下，实现所有类共有接口的缺省行文, 声明一个接口用于访问和管理Component的子组件
        在递归结构中定义一个接口，用于访问一个父部件，并在合适的情况下实现它。
            Leaf 在组合中表示叶节点对象，叶节点没有子节点, 在组合中定义图元对象的行为
            Composite 定义有子部件的那些部件的行为，存储子部件，在Component接口中实现与子部件有关的操作
            Client 通过Component接口曹总组合部件的对象

    动机: 
            在绘图编辑器和图形捕捉系统这样的图形应用程序中，用户可以使用简单的组件创建复杂的图表。用户可以组合多个简单的组件以形成一些较大的组件
        这些组件又可以组合成更大的组件。一个简单的实现方法是Text和Line这样的图元定义一些类，另外定义一些类作为这些图元的容器类(Container)
            然而这种方法存在一个问题: 使用这些类的代码必须区别对待图元对象与容器对象，而实际上大多数情况下用户认为它们是一样的。对这些类区别使用
        ，使得程序更加复杂。Composite模式描述了如何使用递归组合，使得用户不必对这些类进行区别
*/
/*=======================================================类声明============================================================*/
class Equipment;
class Watt;
class Currency;
template <class T> class Iterator;
template <class Iter> class List
{
public:
    List();
};
/*=======================================================Component============================================================*/
class Equipment
{
public:
    virtual ~Equipment();

    const char* Name() { return _name; }

    virtual Watt Power();
    virtual Currency NetPrice();
    virtual Currency DiscountPrice();

    virtual void Add(Equipment*);
    virtual void Remove(Equipment*);
    virtual Iterator<Equipment*>* CreateIterator();

protected:
    Equipment(const char*);
private:
    const char* _name;
};

/*=======================================================Leaf============================================================*/
class FloppyDisk : public Equipment
{
public:
    FloppyDisk(const char*);
    virtual ~FloppyDisk();

    virtual Watt Power();
    virtual Currency NetPrice();
    virtual Currency DiscountPrice();
    
};

/*=======================================================Composite============================================================*/
class CompositeEquipment : public Equipment
{
public:
    virtual ~CompositeEquipment();

    virtual Watt Power();
    virtual Currency NetPrice();
    virtual Currency DiscoutnPrice();

    virtual void Add(Equipment*);
    virtual void Remove(Equipment*);
    virtual Iterator<Equipment*>* CreateIterator(); 

protected:
    CompositeEquipment(const char*);
private:
    List<Equipment*> _equipment;
};

/*
Currency CompositeEquipment::NetPrice()
{
    Iterator<Equipment*>* i = CreateIterator();
    Currency total = 0;

    for (i -> First(); !i -> IsDone(); i -> Next())
    {
        total += i -> CurregentIterm() -> NetPrice();
    }
    delete i;
    return total;
}
*/

class Chassis : public CompositeEquipment
{
public:
    Chassis(const char*);
    virtual ~Chassis();

    virtual Watt Power();
}

