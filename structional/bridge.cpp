/*
    alias: Handle/Body
    参与者:
            Abstraction 定义抽象类的接口
            RefinedAbstration 扩充由Abstraction定义的接口
            Implementor 定义实现类的接口，该接口不一定要与Abstraction的接口完全一致: 事实上这两个接口可以完全不同。
        一般来讲，Implementor接口仅提供基本操作,而Abstraction则定义了基于这些基本操作的较高层次的操作
            ConcreteImplementor 实现Implementor接口并定义它的具体实现
*/
/*=======================================================类声明============================================================*/
class WindowImp;

/*=======================================================基础类定义============================================================*/
class View {};
class Point {};
class Coord {};

/*=======================================================Abstraction============================================================*/
class Window
{
public:
    Window(View *contents);
    
    virtual void DrawContents();

    virtual void Open();
    virtual void Close();
    virtual void Iconify();
    virtual void Deiconify();

    virtual void SetOrigin(const Point &at);
    virtual void SetExtent(const Point &extent);
    virtual void Raise();
    virtual void Lower();
    virtual void DrawLine(const Point&, const Point&);
    virtual void DrawRect(const Point&, const Point&);
    virtual void DrawPolygon(const Point[], int n);
    virtual void DrawText(const char*, const Point&);

protected:
    WindowImp* GetWindowImp();
    View* GetView();
private:
    WindowImp* _imp;
    View* _contents;
};

void Window::DrawRect(const Point &p1, const Point &p2)
{
    WindowImp * imp = GetWindowImp();
    // imp -> DeviceRect(p1.X(), p1.Y(), p2.X(), p2.Y());
}

/*=======================================================Implementor============================================================*/
class WindowImp
{
public:
    virtual void ImpTop() = 0;
    virtual void ImpBottom() = 0;
    virtual void ImpSetExtent(const Point&) = 0;
    virtual void ImpSetOrigin(const Point&) = 0;

    virtual void DeviceRect(Coord, Coord, Coord, Coord) = 0;
    virtual void DeviceText(const char*, Coord, Coord) = 0;
    virtual void DeviceBitmap(const char*, Coord, Coord) = 0;

protected:
    WindowImp();
};

/*=======================================================RefinedAbstration============================================================*/
class ApplicationWindow : public Window
{
public:
    // ...
    virtual void DrawContents();
};

void ApplicationWindow::DrawContents() 
{
    // GetView() -> DrawOn(this);
}

class IconWindow : public Window
{
public:
    // ...
    virtual void DrawContents();
private:
    // const char& _bitmapName;
};

/*=======================================================ConcreteImplementor============================================================*/
class XWindowImp : public WindowImp
{
public:
    XWindowImp();

    virtual void DeviceRect(Coord, Coord, Coord, Coord);
    // ...

private:
    // lots of X window system-specific state
    // Display* _dpy;
    // Drawale _winid;
    // GC _gc;
};

class PMWindowImp : public WindowImp
{
public:
    PMWindowImp();

    virtual void DeviceRect(Coord, Coord, Coord, Coord);
    // ...

private:
    // lots of PM window system-specific state
    // HPS _hps;
};

// 不同系统之间对应可能是不同的实现

void XWindowImp::DeviceRect(Coord x0, Coord y0, Coord x1, Coord y1)
{
    // int x = round(min(x0, x1));
    // int y = round(min(y0, y1));
    // int w = round(abs(x0 - x1));
    // int h = round(abs(y0 - y1));
    // XDrawRectangle(_dpy, _winid, _gc, x, y, w, h);
}

void PMWindowImp::DeviceRect(Coord x0, Coord y0, Coord x1, Coord y1)
{
    // Coord left = min(x0, x1);
    // Coord right = max(x0, x1);
    // Coord bottom = min(y0, y1);
    // Coord top = max(y0, y1);

    //...调用PM系统接口
}
