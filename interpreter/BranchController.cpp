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

void BranchController::bwhile(int iptr)
{
    Branch *branch = new Branch();
    branch->iptr = iptr;
    branch->type = WHILE;
    branch->toward = nullptr;
    branchStack.push(branch);
}

void BranchController::bendwhile(int iptr)
{
    Branch *branch = new Branch();
    branch->iptr = iptr;
    branch->type = ENDWHILE;
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
                if(branch->type == ELSE or branch->type == WHILE)
                {
                    throw LZException(to_string(end->iptr) + ":" + "else statement must not terminate " + type(branch->type) + " statement");
                }
                break;
            
            case ELIF:
                if(branch->type == ELSE or branch->type == WHILE)
                {
                    throw LZException(to_string(end->iptr) + ":" + "elif statement must not terminate " + type(branch->type) + " statement");
                }
                break;
            case ENDIF:
                if(branch->type == WHILE)
                    throw LZException(to_string(end->iptr) + ":" + "endif statement must not terminate " + type(branch->type) + " statement");
                break;
            case ENDWHILE:
                if(branch->type == IF or branch->type == ELIF or branch->type == ELSE)
                    throw LZException(to_string(end->iptr) + ":" + "endwhile statement must not terminate " + type(branch->type) + " statement");
                end->toward = branch;
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
    while((pb = branchStack.top())->type != IF and pb->type != WHILE)
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
        case WHILE:
        case ENDWHILE:
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
    if(commandName == "root.lizzy.lang.if") bif(iptr);
    else if(commandName == "root.lizzy.lang.endif" or
            commandName == "root.lizzy.lang.end.if") bendif(iptr);
    else if(commandName == "root.lizzy.lang.else") belse(iptr);
    else if(commandName == "root.lizzy.lang.elif") belif(iptr);
    else if(commandName == "root.lizzy.lang.while") bwhile(iptr);
    else if(commandName == "root.lizzy.lang.endwhile" or
            commandName == "root.lizzy.lang.end.while") bendwhile(iptr);
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
        case WHILE:return "while";
        case ENDWHILE:return "endwhile";
        default:return "none";
    }
}

int BranchController::jump(int failedBranch)
{
    return branchMap[failedBranch]->toward->iptr - 1;
}

int BranchController::rif(int iptr, bool cond)
{
    if(not cond)
    {
        iptr = jump(iptr);
    }
    
    conditionStack.push(cond);
    return iptr;
}

int BranchController::relse(int iptr)
{
    if(not conditionStack.empty())
    {
        if(conditionStack.top())
        {
            iptr = jump(iptr);
        }
        
    }
    return iptr;
}

int BranchController::relif(int iptr, bool cond)
{
    if(not conditionStack.empty())
    {
        if(conditionStack.top() or not cond)
        {
            iptr = jump(iptr);
        }
        else
        {
            conditionStack.top() = true;
        }
    }
    return iptr;
}

void BranchController::rendif(int iptr)
{
    if(not conditionStack.empty())
    {
        conditionStack.pop();
    }
}

int BranchController::rwhile(int iptr, bool cond)
{
    if(not cond)
    {
        iptr = jump(iptr);
    }
    conditionStack.push(cond);
    return iptr;
}

int BranchController::rendwhile(int iptr)
{
    if(not conditionStack.empty())
    {
        if(conditionStack.top())
            iptr = jump(iptr);
        else
            conditionStack.pop();
    }
    return iptr;
}
