#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>

using ValueType = int;
int operators(char op)
{
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	return -1;
}

bool isDigit(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	return false;
}
bool isNumber(const std::string& token)
{
	if (token.size() == 0)
	{
		return false;
	}
	if (token[0] == '+' || token[0] == '*' || token[0] == '/' || token[0] == '(' || token[0] == ')')
	{
		return false;
	}
	bool flag = 0;
	if (token[0] == '-')
	{
		if (token.size() == 1)
		{
			return false;
		}
		flag = 1;
	}
	for (size_t i = 0; i < token.size(); ++i)
	{
		if(!isDigit(token[i]))
			return false;
	}
	return true;
}
ValueType calc(const ValueType a, const ValueType b, const char op)
{
	switch(op)
	{
		case '*':
			return a*b;
		case '/':
			if (b == 0)
			{
				throw std::runtime_error("Division by zero!");
			}
			return a/b;
		case '+':
			return a+b;
		case '-':
			return a-b;
		default:
			throw std::runtime_error("Undefine operator!");
	}
}

int main()
{
	try
	{
		ValueType result;
		std::string input = "2026 + (13 - 24 * 3) / 2";
		std::string output = "";
		std::stack<char> ops;
		std::stack<ValueType> number;
		for (size_t i = 0; i < input.size(); ++i)
		{
			if (input[i] == ' ')
			{
				continue;
			}
			else if (input[i] == '(')
			{
				ops.push(input[i]);
			}
			else if (isDigit(input[i]))
			{
				ValueType val = 0;
				while (i < input.size() && isDigit(input[i]))
				{
					val = val * 10 + (input[i] - '0');
					++i;
				}
				--i;
				number.push(val);
				output += std::to_string(val) + " ";
			}
			else if (input[i] == ')')
			{
				while (!ops.empty() && ops.top() != '(')
				{
					ValueType val2 = number.top();
					number.pop();
					ValueType val1 = number.top();
					number.pop();
					char op = ops.top();
					ops.pop();
					output += op;
					output += " ";
					number.push(calc(val1, val2, op));
				}
				if (!ops.empty())
				{
					ops.pop();
				}
			}
			else
			{
				while (!ops.empty() && operators(ops.top()) >= operators(input[i]))
				{
					ValueType val2 = number.top();
					number.pop();
					ValueType val1 = number.top();
					number.pop();
					char op = ops.top();
					ops.pop();
					output += op;
					output += " ";
					number.push(calc(val1, val2, op));
				}
				ops.push(input[i]);
			}
		}
		while (!ops.empty())
		{
			ValueType val2 = number.top();
			number.pop();
			ValueType val1 = number.top();
			number.pop();
			char op = ops.top();
			ops.pop();
			output += op;
			output += " ";
			number.push(calc(val1, val2, op));
		}
		
		if (number.empty())
			throw std::runtime_error("There is no result!");

		result = number.top();
	
		std::cout << "Inf: " << input << std::endl;
		std::cout << "Post: " << output << std::endl;
		std::cout << "Res: " << result << std::endl;
	}
	catch (const std::exception& error)
	{
		std::cerr << "Error: " << error.what() << std::endl;
		return 1;	
	}
	return 0;
}
