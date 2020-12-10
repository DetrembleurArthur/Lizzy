#include "Parser.hpp"

using namespace lizzy;
using namespace std;


Parser::Parser()
{
    separators = {"\n", " ", "\t", "/*", "*/", "\\'", "\\\"", "\"", "\\'", "'", "()", "(", ")", ","};
    solidSeparators = {{"\"", "\""}, {"'", "'"}, {"/*", "*/"}};
}

void Parser::parse(const std::string& expr)
{
    tokens = parse(expr, separators);
}

void Parser::merge()
{
    tokens = merge(tokens, solidSeparators);
}

vector<string>& Parser::getTokens()
{
    return tokens;
}

std::vector<std::string>& Parser::getSeparators()
{
    return separators;
}

size_t Parser::size(const std::vector<std::string>& tokens)
{
    auto len = tokens.size();
    for(const auto& token : tokens)
    {
        for(auto sep : separators)
        {
            if(token == sep)
            {
                len--;
                break;
            }
        }
    }
    return len;
}

string Parser::load_file(const string& filename)
{
    string content;
    ifstream file(filename);
    if(file)
    {
        string buffer;
        while(getline(file, buffer))
        {
            content += buffer.substr(0, buffer.find("//")) + "\n";
        }
    }
    return content;
}

vector<string> Parser::parse(string content, const vector<string>& separators)
{
    vector<string> tokens;
    size_t temp = 0;
    string currentSep;
    while(temp != string::npos)
    {
        temp = string::npos;
        for(auto sep : separators)
        {
            size_t temp2 = content.find(sep);
            if(temp2 < temp)
            {
                temp = temp2;
                currentSep = sep;
            }
        }
        if(temp != string::npos)
        {
            const string& temp3 = content.substr(0, temp);
            if(temp3.size())
                tokens.push_back(temp3);
            
            tokens.push_back(currentSep);
            content = content.substr(temp+currentSep.size());
        }
    }
    
    if(content.size())
        tokens.push_back(content);
    return tokens;
}

vector<string> Parser::merge(const vector<string>& ref, const vector<SolidSeparator>& solidSeparators)
{
    string currentSep;
    string buffer;
    vector<string> merged;
    for(auto token : ref)
    {
        if(not currentSep.empty())
        {
            if(token == currentSep)
            {
                buffer += currentSep;
                if(currentSep != "*/")
                    merged.push_back(normalize_ctrl_chars(buffer));
                currentSep.clear();
                buffer.clear();
            }
            else
            {
                buffer += token;
            }
        }
        else
        {
            for(auto&& ssep : solidSeparators)
            {
                if(token == ssep.beg)
                {
                    currentSep = ssep.end;
                    buffer = token;
                    break;
                }
            }
            if(currentSep.empty())
            {
                if(token != " " and token != "\t" and token != "\n")
                {
                    merged.push_back(normalize_ctrl_chars(token));
                }
            }
        }
    }
    if(!buffer.empty())
        merged.push_back(normalize_ctrl_chars(buffer));
    return merged;
}

void Parser::replace_str_by_str(string& content, const string& old_c, const string& new_c)
{
    auto pos = string::npos;
    while((pos = content.find(old_c)) != string::npos)
    {
        content.replace(pos, old_c.length(), new_c);
    }
}

string& Parser::normalize_ctrl_chars(string& content)
{
    if(content.find("\\") == string::npos) return content;
    replace_str_by_str(content, "\\n", "\n");
    if(content.find("\\") == string::npos) return content;
    replace_str_by_str(content, "\\t", "\t");
    if(content.find("\\") == string::npos) return content;
    replace_str_by_str(content, "\\e", "\e");
    if(content.find("\\") == string::npos) return content;
    replace_str_by_str(content, "\\f", "\f");
    if(content.find("\\") == string::npos) return content;
    replace_str_by_str(content, "\\v", "\v");
    if(content.find("\\") == string::npos) return content;
    replace_str_by_str(content, "\\b", "\b");
    if(content.find("\\") == string::npos) return content;
    replace_str_by_str(content, "\\a", "\a");
    if(content.find("\\") == string::npos) return content;
    replace_str_by_str(content, "\\r", "\r");
    if(content.find("\\") == string::npos) return content;
    replace_str_by_str(content, "\\033", "\033");
    if(content.find("\\") == string::npos) return content;
    replace_str_by_str(content, "\\0", "\0");
    return content;
}

bool Parser::isInteger(const string& expr)
{
    auto len = expr.size();
	for(int i = expr[0] == '-'; i < len; i++)
	{
		if(not isdigit(expr[i]))
            return false;
	}
	return true;
}

bool Parser::isFloat(const string& expr)
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

bool Parser::isBool(const string& expr)
{
    return expr == "true" or expr == "false";
}

bool Parser::isString(const string& expr)
{
    if(expr.size() >= 2)
    {
        return (expr.front() == '\"' and expr.back() == '\"') or (expr.front() == '\'' and expr.back() == '\'');
    }
    return false;
}

bool Parser::isConst(const string& expr)
{
    return isBool(expr) or isString(expr) or isInteger(expr) or isFloat(expr);
}

bool Parser::isIdentifier(const std::string& expr)
{
    return expr.size() >= 2 and expr.front() == '$';
}
