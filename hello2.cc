# include <iostream>
# include "TRandom.h"
using namespace std;
void test()
{
TRandom *rnd = new TRandom(time(0));
Double_t x = rnd->Rndm();
cout << "x = " << x << endl;
}
# ifndef __CINT__
int main()
{
test();
return 0;
}
# endif
