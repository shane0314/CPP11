#include "NblExpr.h"

int main()
{
	NblExpr exp1("(5 + 6 * (7 + 3) / 3) / 4 + 5");
	cout << exp1.getExpr() << " = " << exp1.calc() << endl;
	NblExpr exp3("1 * ( 7 - (2 + 3 ) )+ 8 / 2");
	cout << exp3.getExpr() << " = " << exp3.calc() << endl;///
	NblExpr exp2("(5 + 6 * (7 + 3) / 3) / 4 + 5 + 1 * ( 7 - (2 + 3 )) + 8 / 2");
	cout << exp2.getExpr() << " = " << exp2.calc() << endl;
	NblExpr exp4("-1 + (-21 + 3) * (-4)+10/2+2*2+2+2/5");
	cout << exp4.getExpr() << " = " << exp4.calc() << endl;

	return 0;
}
