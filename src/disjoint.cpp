#include <bits/stdc++.h>
using namespace std;

bool check_disjoint(vector<vector<int> > a, vector<int> b)
{
	vector<pair<int, int> > ap, bp;
	for(unsigned int i = 0; i < a.size(); i++)
		for(unsigned int j = 0; j < a[i].size()-1; j++)
		ap.push_back(make_pair(a[i][j],a[i][j+1]));

	for(unsigned int i = 0; i < b.size()-1; i++)
			bp.push_back(make_pair(b[i],b[i+1]));
	
	for(unsigned int i = 0; i < ap.size(); i++)
	{
		for(unsigned int j = 0; j < bp.size(); j++)
		{
			if(find(ap.begin(), ap.end() , bp[j]) != ap.end())
				return false;
			else
				continue;
		}
	}
	return true;
}
bool check_disjoint1(vector<int> a, vector<int> b)
{
	vector<pair<int, int> > ap, bp;
	for(unsigned int i = 0; i < a.size()-1; i++)
		ap.push_back(make_pair(a[i],a[i+1]));

	for(unsigned int i = 0; i < b.size()-1; i++)
			bp.push_back(make_pair(b[i],b[i+1]));
	
	for(unsigned int i = 0; i < ap.size(); i++)
	{
		for(unsigned int j = 0; j < bp.size(); j++)
		{
			if(find(ap.begin(), ap.end() , bp[j]) != ap.end())
				return false;
			else
				continue;
		}
	}
	return true;
}

void write(vector<int> p)
{
	ofstream fo("../paths/usanet/5.txt",ios_base::app);
	for(unsigned int i = 0; i < p.size(); i++)
		fo<<p[i]<<" ";
	fo<<endl;
}

int main()
{	
	string line;
	vector<vector<int> > p;	
	for(int src = 1; src <= 46; src++)
	{
		for(int dest = src+1; dest <= 46; dest++)
		{
			int count = 0;
			vector<int> primary;
			
			ifstream fp("../paths/usanet/a.txt");
			vector<vector<int> > bp;
			while(getline(fp, line))
			{
				istringstream is(line);
				int n;
				vector<int> path;
				while(is >> n)
				{
					path.push_back(n);
				}
				if(path.front() == src && path.back() == dest && count == 0)
				{
					write(path);
					primary = path;
					count++;
					p.push_back(primary);
				}
				if(fp.eof())
					break;
				if(path.front() == src && path.back() == dest && count > 0 && count <= 5 && check_disjoint1(path, primary))
				{
					write(path);
					count++;
				}
			}
			/*
			ifstream fp1("../paths/nsfnet1/a.txt");
			vector<vector<int> > a;
			while(getline(fp1, line))
			{
				stringstream is(line);
				int n;
				vector<int> path;
				while(is >> n)
				{
					path.push_back(n);
				}
				if(path.front() == src && path.back() == dest)
					a.push_back(path);
				if(fp1.eof())
				{
					break;
				}
					//cout<<path.size()<<" ";
			}
			
			if(!a.empty())
			{
				unsigned int max=0,c=0;
				for(unsigned int r = 0; r < a.size(); r++)
					if(max < a[r].size())
						max=a[r].size(),c=r;
				write(a[c]);
			}
			fp1.close();
			#endif*/
			fp.close();
		
		}
	}
}
