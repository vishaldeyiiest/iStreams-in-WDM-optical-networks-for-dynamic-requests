#include <bits/stdc++.h>
#include <vector>
#include <set>
#include <math.h>
using namespace std;
void display(vector<int> );
pair<int,int> longest;
int compute_gain(vector<vector<int> > a, pair<int, int> b)	//to compute gain if the both (src, dest) are present
{
	int max = 0;
	/*if(b.first == 16)
		return b.second - 16;
	if(b.second >= 41)
		return b.second - b.first;
	if(b.first == 37||b.first == 39 )
		return b.second - 37;
	*/
	for(unsigned int i = 0; i < a.size(); i++)
	{
		int p=0,q=0;
		for(unsigned int j=0 ;j < a[i].size(); j++)
		{
			if(a[i][j]==b.first)
				p = j;
			if(a[i][j]==b.second)
				q=j;
			if(p>0 && q>0)
				break;
		}
		int g = abs(p-q);
		if(g>max)
			max = g;
	}
	return max;
}

int compute_gain1(vector<int> a, int s, int d)
{
	int p,q;
	/*if(s == 16)
		return (d-16);
	*/
		for(unsigned int i = 0; i < a.size(); i++)
		{
			if(a[i] == s)
				p = i;
			if(a[i] == d)
				q = i;
		}
		return abs(p-q);
	
}

bool check_disjoint(vector<vector<int> > a, vector<int> b)
{
	vector<pair<int, int> > ap, bp;
	for(unsigned int i = 0; i < a.size(); i++)
	for(unsigned int j = 0; j < a[i].size(); j++)
			ap.push_back(make_pair(a[i][j],a[i][j+1]));

	for(unsigned int j = 0; j < b.size()-1; j++)
	{
		bp.push_back(make_pair(b[j],b[j+1]));
	}
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

vector<int> get_primary(vector<vector<int> > b, int src, int dest)
{
	ifstream fp("../paths/usanet/6.txt");
	string line;
	vector<vector<int> > a;
	while(getline(fp,line))
	{
		stringstream is(line);
		vector<int> path;
		int n;
		while(is >> n)
		{
			path.push_back(n);
		}
		if(path.front() == src && path.back() == dest)
			a.push_back(path);
	}
	int flag=0;
	for(unsigned int i = 0; i < a.size(); i++)
	{
		if(check_disjoint(b, a[i])== true)
		{
			//b.push_back(a[i]);
			cout<<"Primary Path: ";
			display(a[i]);
			flag=1;
			return a[i];
		
		}
		
	}
	fp.close();
	if(flag == 0)
		return (vector<int> ());
	
	//display(a[0]);
}
vector<int> get_backup(int src,int dest)			//choosing the longest path as backup path
{
	ifstream fp("../paths/usanet/6.txt");
	string line;
	vector<vector<int> > a;
	while(getline(fp, line))
	{
		stringstream is(line);
		int n;
		vector<int> path;
		while(is >> n)
		{
			path.push_back(n);
		}

		if(path.front() == src && path.back() == dest)
			//return path;
			a.push_back(path);
			//cout<<path.size()<<" ";
	}
	unsigned int max=0,c;
	for(unsigned int r = 0; r < a.size(); r++)
		if(max < a[r].size())
			max=a[r].size(),c=r;
	fp.close();
	if(max == 0)
		return vector<int>();
	return a[c];
	
}
vector<int> get_extensionpath(vector<int> b, int src,int dest)			//choosing the longest path as backup path
{
	ifstream fp("../paths/usanet/6.txt");
	string line;
	vector<vector<int> > a;
	//int flag = 0;
	while(getline(fp, line))
	{
		stringstream is(line);
		int n;
		vector<int> path;
		while(is >> n)
		{
			path.push_back(n);
		}
		
		if(path.front() == src && path.back() == dest)
		{
			a.push_back(path);
		}	
	}
	fp.close();
	for(unsigned int i = 0; i < a.size(); i++)
	{
		int flag = 0;
		for(unsigned int j = 0; j < a[i].size(); j++)
		{
			for(unsigned int p = 1; p < b.size(); p++)
			{
				if(a[i][j] < b[p])
				{
					flag = 1;
					break;
				}
			}
			if(flag == 1)
				break;
		}
		if(flag == 0)
			return a[i];
	}
	return vector<int> ();		//cout<<path.s()<<" ";
}
vector<int> get_mergepath(vector<int> b, int src,int dest)			//choosing the longest path as backup path
{
	ifstream fp("../paths/usanet/6.txt");
	string line;
	vector<vector<int> > a;
	//int flag = 0;
	while(getline(fp, line))
	{
		stringstream is(line);
		int n;
		vector<int> path;
		while(is >> n)
		{
			path.push_back(n);
		}
		
		if(path.front() == src && path.back() == dest)
		{
			a.push_back(path);
		}	
	}
	fp.close();
	for(unsigned int i = 0; i < a.size(); i++)
	{
		int flag = 0;
		for(unsigned int j = 0; j < a[i].size(); j++)
		{
			for(unsigned int p = 1; p < b.size(); p++)
			{
				if(a[i][j] > b[p])
				{
					flag = 1;
					break;
				}
			}
			if(flag == 1)
				break;
		}
		if(flag == 0)
			return a[i];
	}
	return vector<int> ();		//cout<<path.s()<<" ";
}
void display(vector<int> a)									//display the vector
{
	for(unsigned int i = 0; i < a.size(); i++)
		cout<<a[i]<<" ";
	cout<<endl;
}

pair<int,int> search_src_dest(int src, vector<vector<int> > p)		//search whether src or dest is present
{
	pair<int,int>  x;
	x = make_pair(-1,-1);
    for(unsigned int i = 0; i < p.size(); i++)
    {
		for(unsigned int j = 0; j < p[i].size(); j++)
		{
			if(p[i][j] == src)
				x = make_pair(i,j);
		}
	}
	return x;
}


int block = 0;

int main()
{
	ifstream fp("../testing/usanet300/1.txt");
	ofstream fo("../results.txt",ios_base::app);
	vector<pair<int, int> > set_pairs;
	string line;
	vector<vector<int> > bpath, ppath, path;
	while(getline(fp, line))
	{
		istringstream is(line);
		int n, x;
		pair<int, int> p;
		is >> n , is >> x;
		set_pairs.push_back(make_pair(n,x));
	}
	
	vector<pair<int, int> > served;
	
	vector<int> temp;
	vector<int> temp1,temp2;
	/*temp1 = get_primary(bpath, longest.first, longest.second);
	ppath.push_back(temp1);
	path.push_back(temp1);
	*/
	clock_t t;
	t = clock();
	int gain = 0;
	for(unsigned int i=0;i< set_pairs.size(); i++)					//serving the requests sequentially
	{
		if(set_pairs[i].first == set_pairs[i].second || set_pairs[i].second > 41)
			continue;
			
		int src = set_pairs[i].first;
		int dest = set_pairs[i].second;
		pair<int,int> p = search_src_dest(src, bpath);
		pair<int,int> q = search_src_dest(dest, bpath);
		
		cout<<"Request: "<<src<<" "<<dest<<endl;
		
		if(find(served.begin(), served.end() , set_pairs[i]) != served.end())		//both src and dest are present
		{
			temp1 = get_primary(path, src, dest);
			if(!temp1.empty())
			{
				gain += compute_gain(bpath, set_pairs[i]);
				ppath.push_back(temp1);
				path.push_back(temp1);
				cout<<"Both src and dest present\n";
				cout<<"Gain: "<<compute_gain(bpath, set_pairs[i])<<endl;
				
			}
			else
			{
				cout<<"Both present but no link disjoint primary\n";
				temp = get_backup(src, dest);
				cout<<"New backup path:";display(temp);
				vector<vector<int> > t;
				bpath.push_back(temp);
				t.push_back(temp);
				path.push_back(temp);
				temp1 = get_primary(t, src, dest);
				if(temp1.empty())
					block++;
				else
				{
					for(unsigned int i=0; i < temp.size(); i++)
						for(unsigned int j = i+1 ; j < temp.size(); j++)
							served.push_back(make_pair(temp[i], temp[j]));
					//ppath.push_back(temp1);
				}
			}
			
		}
			
		else if(p.second >= 0 && q.second < 0)						//only src is present
		{
			cout<<"Src present\n";
			//int s = bpath[p.first].back();
			vector<int> x;
			//while(x.empty())
			x = get_extensionpath(bpath[p.first],bpath[p.first].back(),dest);
			if(x.empty())
				cout<<"no extension"<<endl;
			temp1 = get_primary(path, src, dest);
			if(temp1.empty() || x.empty())
			{
				cout<<"no link disjoint primary\n";
				temp = get_backup(src, dest);
				cout<<"new backup path:",display(temp);
				bpath.push_back(temp);
				path.push_back(temp);
				vector<vector<int> > t;
				t.push_back(temp);
				temp2 = get_primary(t, src, dest);
				if(!temp2.empty())
				{
					for(unsigned int i=0; i < temp.size(); i++)
						for(unsigned int j = i+1 ; j < temp.size(); j++)
							served.push_back(make_pair(temp[i], temp[j]));
					ppath.push_back(temp2);
				}
				else
					block++;
			}
			else if(!x.empty())
			{
				cout<<"Stream extended: ";
				display(x);
				
				gain += bpath[p.first].size()-1 - p.second; 
				cout<<"Gain: "<<bpath[p.first].size()-1 - p.second<<endl;
				bpath[p.first].pop_back();
				
				for(unsigned int i = 0; i < bpath[p.first].size(); i++)
					for(unsigned int j = 0; j < x.size(); j++)
						served.push_back(make_pair(bpath[p.first][i],x[j]));
				bpath[p.first].insert(bpath[p.first].end(), x.begin(), x.end());
				//path[p.first].insert(path[p.first].end(), x.begin(), x.end());
				cout<<"Stream: ",display(bpath[p.first]);
				path.push_back(temp1);
				ppath.push_back(temp1);
			}

		}	
		else if(q.second >= 0 && p.second < 0)						//only dest is present
		{
			cout<<"dest present"<<endl;
			vector<int> x;
			int j = 0;
			while(x.empty() && j <= q.second)
				x= get_mergepath(bpath[q.first],src,bpath[q.first][j++]);
				//get_primary(path, src, dest);
			temp1 = get_primary(path, src, dest);
			if(x.empty())
				cout<<"no merge path"<<endl;
			if(temp1.empty() || x.empty())
			{
				cout<<"no link disjoint primary"<<endl;
				temp = get_backup(src, dest);
				cout<<"New backup path:";display(temp);
				bpath.push_back(temp);
				path.push_back(temp);
				vector<vector<int> > t;
				t.push_back(temp);				
				temp2 = get_primary(t, src, dest);
				if(temp2.empty())
					block++;
				else
				{
					for(unsigned int i=0; i < temp.size(); i++)
						for(unsigned int j = i+1 ; j < temp.size(); j++)
							served.push_back(make_pair(temp[i], temp[j]));
					ppath.push_back(temp2);
				}
			}
			else
			{
				cout<<"Stream merged: ";display(x);
				cout<<"Gain: "<<compute_gain1(bpath[q.first],x[x.size()-1],dest)<<endl;
				gain += compute_gain1(bpath[q.first],x[x.size()-1],dest);
				x.pop_back();
				//path[q.first].insert(path[q.first].begin(), x.begin(), x.end()); 
				bpath[q.first].insert(bpath[q.first].begin(), x.begin(), x.end());
				display(bpath[q.first]);
				for(unsigned int i = 0; i < x.size(); i++)
					for(unsigned int j = 0; j < bpath[q.first].size(); j++)
						served.push_back(make_pair(x[i],bpath[q.first][j]));		
				path.push_back(temp);
			}
		}
		# if 1
		else if(p.first >= 0 && q.first >= 0 && p.first != q.first)
		{
			int flag = 0;
			cout<<"Present in different streams"<<endl;
			display(bpath[p.first]),display(bpath[q.first]);
			temp = get_primary(path, src, dest);
			if(!temp.empty())
			{
				vector<int>:: iterator i;
				for(i = bpath[q.first].begin(); i <= bpath[q.first].end(); i++)
				{
					if(*i == bpath[p.first].back())
					{
						bpath[p.first].insert(bpath[p.first].end(),i+1,bpath[q.first].end());
						for(unsigned int i = 0; i < bpath[p.first].size(); i++)
							for(unsigned int j = 0; j < bpath[q.first].size(); j++)
								served.push_back(make_pair(bpath[p.first][i],bpath[q.first][j]));
						flag = 1;
						gain += compute_gain1(bpath[p.first], src, dest);
						cout<<"Gain: "<<compute_gain1(bpath[p.first], src, dest)<<endl;
						display(bpath[p.first]);
						break;
					}
				}
				
			}
			else
			{
				cout<<"no link disjoint primary"<<endl;
				temp = get_backup(src, dest);
				cout<<"New backup path:";display(temp);
				bpath.push_back(temp);
				path.push_back(temp);
				vector<vector<int> > t;
				t.push_back(temp);				
				temp2 = get_primary(t, src, dest);
				if(temp2.empty())
					block++;
				else
				{
					for(unsigned int i=0; i < temp.size(); i++)
						for(unsigned int j = i+1 ; j < temp.size(); j++)
							served.push_back(make_pair(temp[i], temp[j]));
					ppath.push_back(temp2);
				}
			}
		}
		#endif
		else
		{
			cout<<"None present"<<endl; 
			temp=get_backup(set_pairs[i].first,set_pairs[i].second);
			//cout<<"New backup path:";display(temp);
			bpath.push_back(temp);
			path.push_back(temp);
			cout<<"Backup Path: ",display(temp);
			
			
			for(unsigned int i=0; i < temp.size(); i++)
			{
				for(unsigned int j = i+1 ; j < temp.size(); j++)
				{
					served.push_back(make_pair(temp[i], temp[j]));
					//served.push_back(make_pair(path[0][j], path[0][i]));
				}
			}
			//if(!temp.empty())
			temp1 = get_primary(bpath,src,dest);
				
			if(!temp1.empty())
				block++;
			else
				path.push_back(temp1);
			
		}
	}
	t = clock() - t;
	double length = 0;
	for(unsigned int i = 0; i < bpath.size(); i++)
		length += bpath[i].size();
	length = length / (double)100 ;
	cout<<"Total gain new-streams: "<<gain<<endl;
	//cout<<"Total path length: "<<length<<endl;
	//cout<<"Blocked requests: "<<block<<endl;
	cout<<"Time: "<<t/(double)CLOCKS_PER_SEC<<endl;
}
