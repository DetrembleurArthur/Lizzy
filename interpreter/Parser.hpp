#ifndef PARSER_HPP
#define PARSER_HPP
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
//#include <algorithm>

namespace lizzy
{
    struct SolidSeparator
    {
        std::string beg;
        std::string end;
        SolidSeparator(std::string&& beg, std::string&& end) : beg(beg), end(end)
        {
            
        }
    };

    class Parser
    {
    private:
        std::vector<std::string> separators;
        std::vector<SolidSeparator> solidSeparators;
        std::vector<std::string> tokens;
    public:
        Parser();
        void parse(const std::string& expr);
        void merge();
        std::vector<std::string>& getTokens();
        static std::string& normalize_ctrl_chars(std::string& content);
        static void replace_str_by_str(std::string& content, const std::string& old_c, const std::string& new_c);
        static std::string load_file(const std::string& filename);
        static std::vector<std::string> parse(std::string content, const std::vector<std::string>& separators);
        static std::vector<std::string> merge(const std::vector<std::string>& ref, const std::vector<SolidSeparator>& solidSeparators);
    };
}

#endif
/*

bool Recognizer::isInteger(const string& expr)
{
    auto len = expr.size();
	for(int i = expr[0] == '-'; i < len; i++)
	{
		if(not isdigit(expr[i]))
            return false;
	}
	return true;
}

bool Recognizer::isFloat(const string& expr)
{
    auto len = expr.size();
	int ptCounter = 0;
	for(int i = expr[0] == '-'; i < len; i++)
	{
		if(not isdigit(expr[i]))
		{
			if(i != 0 and i != len - 1 and ptCounter == 0 and expr[i] == '.')
			{
				ptCounter++;
			}
			else
			{
                
				return false;
			}
		}
	}
	return true;
}

*/