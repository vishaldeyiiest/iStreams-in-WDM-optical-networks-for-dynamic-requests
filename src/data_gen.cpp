#include <bits/stdc++.h>
using namespace std;

int main()
{
	ofstream fp("../testing/nsfnet200/1.txt");
	int c = 0;
	while(c<=200)
	{
		int s = 15*(rand()/(double)INT_MAX);
		int d = 15*(rand()/(double)INT_MAX);
		if(s == 0 || d == 0 || s == d )
			continue;
		else
			c++;
		
		fp<<s<<" "<<d<<endl;
	}
}
