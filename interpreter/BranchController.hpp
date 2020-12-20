#ifndef BRANCH_CONTROLLER_HPP
#define BRANCH_CONTROLLER_HPP
#include <map>
#include "Exceptions.hpp"
#include <vector>
#include <stack>

namespace lizzy
{
    enum BranchType
    {
        NONE,IF,ELSE,ELIF,ENDIF,WHILE,ENDWHILE
    };

    struct Branch
    {
        int iptr = -1;
        BranchType type = NONE;
        Branch *toward;
    };

    class BranchController
    {
    private:
        std::map<int, Branch*> branchMap;
        std::stack<Branch *> branchStack;
        std::stack<bool> conditionStack;
        void linkLast(Branch *end);
        void pop();
        void check(Branch *branch);
    public:
        BranchController();
        virtual ~BranchController();
        void bif(int iptr);
        void belse(int iptr);
        void belif(int iptr);
        void bendif(int iptr);
        void bwhile(int iptr);
        void bendwhile(int iptr);
        int rif(int iptr, bool cond);
        int relse(int iptr);
        int relif(int iptr, bool cond);
        void rendif(int iptr);
        int rwhile(int iptr, bool cond);
        int rendwhile(int iptr);
        void build(int iptr, std::string commandName);
        int jump(int failedBranch);
        void show();
        void finalize();
        std::string type(BranchType type);
    };
}


#endif
