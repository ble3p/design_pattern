/*
    alias: Action, Transaction
   参与者:
            Command 声明执行操作的接口
            ConcreteCommand 将一个接受者对象绑定与一个动作,调用接受者相应的操作, 以实现Execute
            Client 创建一个具体命令对象并设定接受者
            Invoker 要求该命令执行这个请求
            Reciver 知道如何实施与执行一个请求相关的操作。 任何类都可能作为一个接受者
    协作:
            当客户提交一个请求时,请求沿链传递直至有一个ConcreteHandler对象负责处理它
*/

//===================================================类定义======================================================
#include <list>
class Command;
class Application;
class Document;
//===================================================类实现======================================================
class Command
{
public:
    virtual ~Command();

    virtual void Execute() = 0;
protected:
    Command();
};

class OpenCommand : public Command
{
public:   
    OpenCommand(Application*);

    virtual void Execute();
protected:
    virtual const char* AskUser();
private:
    Application* _application;
    char *_response;
};

OpenCommand::OpenCommand(Application *a)
{
    _application = a;
}

void OpenCommand::Execute()
{
    // const char *name = AskUser();
    // if (name != 0)
    // {
    //     Document *document = new Document(name);
    //     _application -> Add(document);
    //     document -> Open();
    // }
}

class PasteCommand : public Command
{
public:
    PasteCommand(Document *);

    virtual void Execute();
private:
    Document *_document;
};

PasteCommand::PasteCommand(Document *doc)
{
    _document = doc;
}

void PasteCommand::Execute() 
{
    // _document -> Paster();
}

class MacroCommand : public Command
{
public:
    MacroCommand();
    virtual ~MacroCommand();

    virtual void Add(Command*);
    virtual void Remove(Command*);

    virtual void Execute();
private:
    std::list<Command*> *_cmds;
};

void MacroCommand::Execute()
{
    std::list<Command*>::iterator i = _cmds -> begin();

    for (auto it = i; it != _cmds -> end(); ++it)
    {
        Command *c = *it;
        c -> Execute();
    }
}

void MacroCommand::Add(Command *c)
{
    _cmds -> push_back(c);
}

void MacroCommand::Remove(Command *c)
{
    // _cmds 删除cj
}
