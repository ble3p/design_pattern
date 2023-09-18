/*
    alias: Wrapper
    参与者:
            Component 定义一个对象接口，可以给这些对象动态地添加职责
            ConcreteComponent 定义一个对象， 可以给这个对象添加一些职责
            Decorator 维持一个指向Component对象的指针, 并定义一个Component接口一致的接口
            ConcreteDecorator 向组件中添加职责
    协作:
            Decorator将请求转发给它的Component对象，并有可能在转发请求前后执行一些附加的动作

    动机: 
            有时我们希望给某个对象而不是整个类添加一些功能。例如，一个图形用户界面工具箱允许你对任意一个用户界面组件添加一些特性，例如边框，或是一些行为，例如窗口滚动。
            使用继承机制是添加功能的一种有效途径，从其他类继承过来的边框特性可以被多个子类的实例所使用。但这种方法不够灵活，因为边框的选择是静态的，用户不能控制对组件加边框的方式和时机
*/

/*=======================================================类声明============================================================*/
class VisualComponent;

/*=======================================================VisualComponent============================================================*/
class VisualComponent
{
public:
    VisualComponent();

    virtual void Draw();
    virtual void Resize();
    // ...
};

/*=======================================================Decorator============================================================*/
class Decorator : public VisualComponent
{
public:
    Decorator(VisualComponent*);

    virtual void Draw();
    virtual void Resize();
    // ...
private:
    VisualComponent* _component;
};

void Decorator::Draw()
{
    _component -> Draw();
}

void Decorator::Resize()
{
    _component -> Resize();
}

/*=======================================================ConcreteDecorator============================================================*/
class BorderDecorator : public Decorator
{
public:
    BorderDecorator(VisualComponent*, int borderWidth);

    virtual void Draw();
private:
    void DrawBorder(int);
private:
    int _width;
    
};

void BorderDecorator::Draw()
{
    Decorator::Draw();
    DrawBorder(_width);
}


