#include "BranchController.hpp"

using namespace lizzy;
using namespace std;


BranchController::BranchController()
{

}

BranchController::~BranchController()
{
    for(auto it = branchMap.begin(); it != branchMap.end(); it++)
    {
        if(it->second)
            delete it->second;
    }
}

void BranchController::bif(int iptr)
{
    Branch *branch = new Branch();
    branch->iptr = iptr;
    branch->type = IF;
    branch->toward = nullptr;
    branchStack.push(branch);
}

void BranchController::belse(int iptr)
{
    Branch *branch = new Branch();
    branch->iptr = iptr;
    branch->type = ELSE;
    branch->toward = nullptr;
    linkLast(branch);
    branchStack.push(branch);
}

void BranchController::belif(int iptr)
{
    Branch *branch = new Branch();
    branch->iptr = iptr;
    branch->type = ELIF;
    branch->toward = nullptr;
    linkLast(branch);
    branchStack.push(branch);
}

void BranchController::bendif(int iptr)
{
    Branch *branch = new Branch();
    branch->iptr = iptr;
    branch->type = ENDIF;
    branch->toward = nullptr;
    linkLast(branch);
    branchStack.push(branch);
    pop();
}

void BranchController::linkLast(Branch *end)
{
    if(not branchStack.empty())
    {
        Branch *branch = branchStack.top();
        switch(end->type)
        {
            case ELSE:
                if(branch->type == ELSE)
                {
                    throw LZException(to_string(end->iptr) + ":" + "else statement must not terminate other else statement");
                }
                break;
            
            case ELIF:
                if(branch->type == ELSE)
                {
                    throw LZException(to_string(end->iptr) + ":" + "elif statement must not terminate else statement");
                }
                break;
            default:;
        }
        branch->toward = end;
    }
    else
    {
        throw LZException(to_string(end->iptr) + ":" + type(end->type) + " " + " must terminate conditionnal block");   
    }
}

void BranchController::pop()
{
    Branch *pb = nullptr;
    while((pb = branchStack.top())->type != IF)
    {
        branchMap[pb->iptr] = pb;
        check(pb);
        branchStack.pop();
    }
    branchMap[pb->iptr] = pb;
    check(pb);
    branchStack.pop();
}

void BranchController::check(Branch *branch)
{
    switch(branch->type)
    {
        case IF:
        case ELIF:
            if(not branch->toward)
                throw LZException(type(branch->type) + " does not refer to a location");
        default:;
    }
}

void BranchController::finalize()
{
    if(not branchStack.empty())
        throw LZException("one or more branchement expressions are not complete");
}

void BranchController::build(int iptr, std::string commandName)
{
    if(commandName == "if") bif(iptr);
    else if(commandName == "endif") bendif(iptr);
    else if(commandName == "else") belse(iptr);
    else if(commandName == "elif") belif(iptr);
}

void BranchController::show()
{
    cout << "BRANCHS" << endl;
    for(auto it = branchMap.begin(); it != branchMap.end(); it++)
    {
        if(it->second->toward)
            cout << it->first << " " << type(it->second->type) << " -> " << it->second->toward->iptr << endl;
        else
            cout << it->first << " " << type(it->second->type) << endl;
    }
}

std::string BranchController::type(BranchType type)
{
    switch(type)
    {
        case IF:return "if";
        case ELSE:return "else";
        case ELIF:return "elif";
        case ENDIF:return "endif";
        default:return "none";
    }
}

int BranchController::jump(int failedBranch)
{
    return branchMap[failedBranch]->toward->iptr;
}
