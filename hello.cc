# include <iostream>
using namespace std;
void hello()
{
cout << "hello world!" << endl;
}
# ifndef __CINT__
int main()
{hello();
return 0;
}
# endif
