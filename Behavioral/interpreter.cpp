/*
    alias: Action, Transaction
   参与者:
            AbstreactExpression 声明一个抽象的解释操作，这个接口为抽象语法树中所有的节点所共享
            TerminalExpression 实现与文法中的终结符相关联的解释操作, 一个句子中的每个终结符需要该类的一个实例
            NonterminalExpression 非终结
            Context 包含解释器之外的一些全局信息
            Client 构建表示该文法定义的语言中一个特定的句子的抽象语法树。调用解释操作
    协作:
            Client 构建一个句子，它是NonterminalExpression 和 TerminialExpression的实例
*/

//===================================================类定义======================================================
class BooleanExp;
class Context;
class VariableExp;
//===================================================类实现======================================================
class BooleanExp
{
public:
    BooleanExp();
    virtual ~BooleanExp();

    virtual bool Evaluate(Context&) = 0;
    virtual BooleanExp* Replace(const char*, BooleanExp&) = 0;
    virtual BooleanExp* Copy() const = 0;
};

class Context
{
public:
    bool Lookup(const char*) const;
    void Assign(VariableExp*, bool);
};

class VariableExp : public BooleanExp
{
public:
    VariableExp(const char*);
    virtual ~VariableExp();

    virtual bool Evaluate(Context&);
    virtual BooleanExp* Replace(const char*, BooleanExp&);
    virtual BooleanExp* Copy() const;
private:
    char *_name;
};

VariableExp::VariableExp(const char *name)
{
    // _name = strdup(name);
}

bool VariableExp::Evaluate(Context &aContext)
{
    return aContext.Lookup(_name);
}

BooleanExp* VariableExp::Copy() const 
{
    return new VariableExp(_name);
}

BooleanExp* VariableExp::Replace(const char *name, BooleanExp &exp)
{
    // if (strcmp(name, _name) == 0)
    //     return exp.Copy();
    // else
    //     return new VariableExp(_name);
}


class AndExp : public BooleanExp
{
public:
    AndExp(BooleanExp*, BooleanExp*);
    virtual ~AndExp();

    virtual bool Evaluate(Context&);
    virtual BooleanExp* Replace(const char*, BooleanExp&);
    virtual BooleanExp* Copy() const;

private:
    BooleanExp *_operand1;
    BooleanExp *_operand2;
};

AndExp::AndExp(BooleanExp *op1, BooleanExp *op2)
{
    _operand1 = op1;
    _operand2 = op2;
}

bool AndExp::Evaluate(Context &aContext)
{
    return _operand1 -> Evaluate(aContext) && _operand1 -> Evaluate(aContext);
}

BooleanExp* AndExp::Copy() const
{
    return new AndExp(_operand1 -> Copy(), _operand2 -> Copy());
}

BooleanExp* AndExp::Replace(const char *name, BooleanExp &exp)
{
    return new AndExp(_operand1 -> Replace(name, exp), _operand2 -> Replace(name, exp));
}
