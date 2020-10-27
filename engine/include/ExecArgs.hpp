#pragma once
#include <string>
#include <unordered_map>

class ExecArgs {

    public:
    typedef void (ExecArgs::* execArgsFuncPtr)(std::string);
    virtual void add(std::string arg, execArgsFuncPtr func);
    virtual void execute(std::string arg1, std::string arg2);

    private:
    std::unordered_map<std::string, execArgsFuncPtr> argsFuncs;

};

void ExecArgs::add(std::string arg, execArgsFuncPtr func)
{
    argsFuncs[arg] = func;
}
void ExecArgs::execute(std::string arg1, std::string arg2)
{
    if (argsFuncs.find(arg1) != argsFuncs.end()){
        (this->* argsFuncs.at(arg1))(arg2);
    }
}
