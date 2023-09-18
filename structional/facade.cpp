/*
    参与者:
            Facade 知道哪些子系统类负责处理请求，将客户的请求代理给适当的子系统对象
            Subsystem classes 实现子系统的功能，处理由Facade对象指派的任务,没有facade的任何相关信息；即没有指向facade的指针
    协作:
            客户程序通过发送请求给Facade的方式与子系统通讯，Facade将这些消息转发给适当的子系统对象。尽管是子系统中的有关对象在做实际工作，但Facade模式本身也必须将它的接口转换成子系统的接口,使用Facade的客户程序不需要直接访问子系统对象.

    动机: 
            将一个系统划分成为若干个子系统有利于降低系统的复杂性。一个常见的设计目标是使子系统间的通信和相互依赖关系达到最小。达到该目标的途径之一就是引入一个facade对象，它为子系统中较一般的设施提供了一个单一而简单的界面
            
*/

/*=======================================================类声明============================================================*/
#include <iostream>
using namespace std;
class Scanner;
class Token;
class ProgramNodeBuilder;
class ProgramNode;
class CodeGenerator;
class BytecodeStream;
class RISCodeGenerator
{
    public:
        RISCodeGenerator(BytecodeStream&);
};
/*=======================================================Subsystem classes============================================================*/
class Scanner
{
public:  
    Scanner(istream&);
    virtual ~Scanner();

    virtual Token& Scan();
private:
    istream& _inputStream;
};

class Parser
{
public:
    Parser();
    virtual ~Parser();

    virtual void Parse(Scanner&, ProgramNodeBuilder&);
};

class ProgramNodeBuilder
{
public:
    ProgramNodeBuilder();

    virtual ProgramNode* NewVariable(const char* variableName) const;
    
    virtual ProgramNode* NewReturnStatement( ProgramNode* value) const;

    virtual ProgramNode* NewCondition(ProgramNode* condition, ProgramNode* truePart, ProgramNode* flasePart) const;
    // ...
    ProgramNode* GetRootNode();
private:
    ProgramNode* _node;
};

class ProgramNode
{
public:
    // program node manipulation
    virtual void GetSourcePosition(int &line, int &index);
    // ...

    // child manipulation
    virtual void Add(ProgramNode*);
    virtual void Remove(ProgramNode*);
    // ...

    virtual void Traverse(CodeGenerator&);
protected:
    ProgramNode();
};

/*
class CodeGenerator
{
public:
    virtual void Visit(StatementNode*);
    virtual void Visit(ExpreesionNode*);

protected:
    CodeGenerator(Bytecodestream&);
protected:
    BytecodeStream& _output;
    
};

class ExpreesionNode::Traverse(CodeGenerator& cg)
{
    cg.Visit(this);

    ListIterator<ProgramNode*> i(_children);

    for (i.First(); !i.IsDone(); i.Next())
    {
        i.CurrentIterm() -> Tranverse(cg);
    }
}
*/


/*=======================================================Facade============================================================*/

class Compiler
{
public:
    Compiler();

    virtual void Compile(istream&, BytecodeStream&);
};

void Compiler::Compile(istream& input, BytecodeStream& output)
{
    Scanner scanner(input);
    ProgramNodeBuilder builder;
    Parser parser;

    parser.Parse(scanner, builder);

    RISCodeGenerator generator(output);
    ProgramNode* parseTree = builder.GetRootNode();
    // parseTree -> Traverse(generator);
}
