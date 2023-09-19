/*
   参与者:
            Handler 定义一个处理请求的接口
            ConcreteHandler 处理它所负责的请求，可访问它的后继者
            Client 向链上的具体处理这对象提交请求
    协作:
            当客户提交一个请求时,请求沿链传递直至有一个ConcreteHandler对象负责处理它
*/

// 每一个可以提供帮助的类继承自帮助类，如果能提供帮助就直接提供帮助，不能提供帮助就上升到父类去找链的下一位
//===================================================类定义======================================================
typedef int Topic;
const Topic NO_HELP_TOPIC = -1;
class HelpHandler;
//===================================================类实现======================================================
class HelpHandler
{
public:
    HelpHandler(HelpHandler *s = 0, Topic = NO_HELP_TOPIC);
    virtual void HandleHelp();
    virtual bool HasHelp();
    virtual void SetHandler(HelpHandler*, Topic);
private:
    HelpHandler *_successor;
    Topic _topic;
};
HelpHandler::HelpHandler(HelpHandler *h, Topic t) : _successor(h), _topic(t) {}

bool HelpHandler::HasHelp() { return _topic != NO_HELP_TOPIC; }

void HelpHandler::HandleHelp()
{
    if (_successor)
    {
        _successor -> HandleHelp();
    }
}

class Widget : public HelpHandler
{
protected:
    Widget(Widget* parent, Topic t = NO_HELP_TOPIC);
private:
    Widget *_parent;
};

Widget::Widget(Widget *w, Topic t) : HelpHandler(w, t)
{
    _parent = w;
}

class Button : public Widget
{
public:
    Button(Widget *d, Topic t = NO_HELP_TOPIC);

    virtual void HandleHelp();
        
};

Button::Button (Widget *h, Topic t) :Widget(h, t) {}

void Button::HandleHelp()
{
    if (HasHelp()) 
    {
        // offer help on the button
    }
    else {
        HelpHandler::HandleHelp();
    }
}

class Dialog : public Widget
{
    Dialog(HelpHandler *h, Topic t = NO_HELP_TOPIC);
    virtual void HandleHelp();

    // Widget operations that Dialog overrides...
    // ...
    
};

Dialog::Dialog(HelpHandler *h, Topic t) : Widget(0)
{
    SetHandler(h, t);
}

void Dialog::HandleHelp()
{
    if (HasHelp())
    {
        // offer help on the dialog
    }
    else
    {
        HelpHandler::HandleHelp();
    }
}

class Application : public HelpHandler
{
public:
    Application(Topic t) : HelpHandler(0, t) {}

    virtual void HandleHelp();
};

void Application::HandleHelp()
{
    // show a list of help topics
}

// Button -> (Widget)Dialog -> (Anything)Application
