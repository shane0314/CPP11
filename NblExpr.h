#include <iostream>
#include <stack>
#include <vector>
#include <string.h>
#include <stdlib.h>

using namespace std;

class NblExpr {

	char * expr;

public:
	NblExpr(const char *s)
	{
		expr = new char[strlen(s) + 1];
		strcpy(expr, s);
	}
	~NblExpr()
	{
		delete expr;
	}

	char * getExpr() const { return expr; }
	double calc();//计算表达式结果,返回结果类型double
	char getOpr(int &i, int &num); //得到一个运算符或数字
	int calcOnce(stack<char> &oprS, stack<double> &numS);
	int getPrior(char opr); //运算符优先级
};

char NblExpr::getOpr(int &i, int &num)
{
	if ((expr[i] > '9' || expr[i] < '0') && expr[i] != '-')
	{
		//i++; //!!
		return expr[i++]; //运算符
	}
	else if (expr[i] == '-')
	{
	    //负号前面不能是数字
	    for(int j=i-1; j>=0; j--)
	    {
	        if (expr[j] == ' ')
	            continue;
	        else if (expr[j] <= '9' && expr[j] >= '0')
            {   
                //i++;	            
                return expr[i++]; 
            }
	        else
	            break;
	    }
	    //负号后面必须是数字
	    for(int j=i+1; j<=strlen(expr); j++)
	    {
	        if (expr[j] == ' ')
	            continue;
	        else if (expr[j] > '9' || expr[j] < '0')
            {   
                //i++;
                return expr[i++];
            }
            else
                break;
	    }
	    //负数
	    int m_num = 0;
	    for(i++; expr[i] == ' '; i++);
	    while (expr[i] <= '9' && expr[i] >= '0' && i <= strlen(expr))
		{
			m_num = m_num * 10 + expr[i] - '0';
			i++;
		}
		num = -m_num;
		return 'N';
	}
	else
	{
		int m_num = 0; //数字
		while (expr[i] <= '9' && expr[i] >= '0' && i <= strlen(expr))
		{
			m_num = m_num * 10 + expr[i] - '0';
			i++;
		}
		num = m_num;
		return 'N';
	}
}

int NblExpr::calcOnce(stack<char> &oprS, stack<double> &numS)
{
	double num2 = numS.top();//!!pop只弹出，不返回
	numS.pop();
	double num1 = numS.top();
	numS.pop();
	char opr = oprS.top();
	oprS.pop();
	double res;
	
	if (opr == '+')
		res = num1 + num2;
	else if (opr == '-')
		res = num1 - num2;
	else if (opr == '*' || opr == 'X')
		res = num1 * num2;
	else if (opr == '/' && num2 != 0)
		res = num1 / num2;
	else if (num2 ==0){
		cout << "除数不能为零：" << num2 << endl;
		return -1;
	}
	else{
	    cout << "运算符错误：" << opr << endl;
	    return -1;
	}
	numS.push(res);
	return 0;
}

int NblExpr::getPrior(char opr) //NblExpr::
{
	if (opr == '+')
		return 1;
	else if (opr == '-')
		return 1;
	else if (opr == '*')
		return 2;
	else if (opr == '/')
		return 2;
	else
	{
		cout << "无效运算符" << endl;
		return -1;
	}
}

double NblExpr::calc()
{
	int num = 0;
	double result = 0;
	char opr, lastOpr;
	stack<double> numStack;
	stack<char> oprStack;

	int len = strlen(expr);
	int i = 0;

	while (i < len) //0 ~ len-1
	{
		if (expr[i] == ' ')
		{
			i++; //!!!
			continue;
		}
		opr = getOpr(i, num);
		if (opr == 'N')
			numStack.push(num);
		else if (opr == '(')
			oprStack.push(opr);
		else if (opr == ')')
		{
			while (!oprStack.empty() && oprStack.top() != '(')
			{
				//lastOpr = oprStack.top();
				//oprStack.pop();
				calcOnce(oprStack, numStack);
			}
			if (!oprStack.empty())
			    oprStack.pop(); //弹出'('
		}
		else
		{
			while (!oprStack.empty() && oprStack.top() != '('
				&& getPrior(oprStack.top()) >= getPrior(opr))
			{
				calcOnce(oprStack, numStack);
			}
			oprStack.push(opr); //压入当前 运算符
		}
	}//while (i<=len)
	while (!oprStack.empty())
	{
		calcOnce(oprStack, numStack);
	}
	if (!oprStack.empty() || numStack.empty() || numStack.size()>1)
	{
		cout << "计算错误" << endl;
		return 0;
	}
	result = numStack.top();
	return result;
}

