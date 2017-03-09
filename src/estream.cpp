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
	if(b.first == 16)
		return b.second - 16;
	if(b.second >= 41)
		return b.second - b.first;
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
	if(s == 16)
		return (d-16);
	
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
	ifstream fp("../paths/usanet/a.txt");
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
	if(flag == 0)
		return (vector<int> ());
	
	//display(a[0]);
}
vector<int> get_backup(int src,int dest)			//choosing the longest path as backup path
{
	ifstream fp("../paths/usanet1/a.txt");
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
			a.push_back(path);
			//cout<<path.size()<<" ";
	}

	unsigned int max=0,c;
	for(unsigned int r = 0; r < a.size(); r++)
		if(max < a[r].size())
			max=a[r].size(),c=r;
	
	if(max == 0)
		return vector<int>();
	return a[c];
}
vector<int> get_path(int src,int dest)			//choosing the longest path as backup path
{
	ifstream fp("../paths/usanet/a.txt");
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
			return path;
			//cout<<path.s()<<" ";
	}
}

void display(vector<int> a)									//display the vector
{
	for(unsigned int i = 0; i < a.size(); i++)
		cout<<a[i]<<" ";
	cout<<endl;
}

pair<int,int> search_src_dest(int src, vector<vector<int> > p)		//search whether src or dest is present
{
	int max = 0;
    for(unsigned int i = 0; i < p.size(); i++)
    {
		for(unsigned int j = 0; j < p[i].size(); j++)
		{
			if(p[i][j] == src && j > max)
				return make_pair(i,j);
		}
    }
   
    return make_pair(-1,-1);
}

vector<int> check_longest(vector<pair<int,int> > r)			//finding the request giving the longest backup path
{
	vector<int> p,pm;
	unsigned int max = 0;
	for(unsigned int i=0; i < r.size(); i++)
	{
		p = get_backup(r[i].first, r[i].second);
		if (p.size() > max)
		{
			max = p.size();
			pm = p;
			longest=make_pair(r[i].first,r[i].second);
		}
	}
	cout<<"Request first served: "<<longest.first<<" "<<longest.second<<endl;
	cout<<"Longest backup path:";
	display(pm);
	return pm;
}

int block = 0;

int main()
{
	ifstream fp("../testing/usanet100/2.txt");
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
	bpath.push_back(check_longest(set_pairs));					//finding the longest backup path request
	path.push_back(check_longest(set_pairs));
	for(unsigned int i=0; i < bpath[0].size(); i++)					//storing served pairs
	{
		for(unsigned int j = i+1 ; j < bpath[0].size(); j++)
		{
			served.push_back(make_pair(bpath[0][i], bpath[0][j]));
		}
	}
	
	vector<int> temp;
	vector<int> temp1,temp2;
	temp1 = get_primary(bpath, longest.first, longest.second);
	ppath.push_back(temp1);
	path.push_back(temp1);
	
	int gain = 0;
	for(unsigned int i=0;i< set_pairs.size(); i++)					//serving the requests sequentially
	{
		if(set_pairs[i] == longest || set_pairs[i].first == set_pairs[i].second || set_pairs[i].second >= 42)
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
				//path.push_back(temp);
				temp1 = get_primary(t, src, dest);
				if(temp1.empty())
					block++;
				else
				{
					for(unsigned int i=0; i < temp.size(); i++)
						for(unsigned int j = i+1 ; j < temp.size(); j++)
							served.push_back(make_pair(temp[i], temp[j]));
					ppath.push_back(temp1);
				}
			}
			
		}
		
		else if(p.second >= 0 && q.second < 0)						//only src is present
		{
			cout<<"Src present\n";
			int s = bpath[p.first].size()-1;
			vector<int> x;
			
				x = get_backup(bpath[p.first][s],dest);
			//concatenate x to end of path[p.first]
			temp1 = get_primary(bpath, src, dest);
			if(temp1.empty())
			{
				cout<<"no link disjoint primary\n";
				temp = get_backup(src, dest);
				cout<<"New backup path:";display(temp);
				bpath.push_back(temp);
				//path.push_back(temp);
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
			else
			{
				cout<<"Stream extended: ";
				display(x);
				
				gain += bpath[p.first].size()-1 - p.second; 
				cout<<"Gain: "<<bpath[p.first].size()-1 - p.second<<endl;
				bpath[p.first].pop_back();
				path[p.first].pop_back();
				for(unsigned int i = 0; i < bpath[p.first].size(); i++)
					for(unsigned int j = 0; j < x.size(); j++)
						served.push_back(make_pair(bpath[p.first][i],x[j]));
				bpath[p.first].insert(bpath[p.first].end(), x.begin(), x.end());
				path[p.first].insert(path[p.first].end(), x.begin(), x.end());
				cout<<"Stream: ",display(path[p.first]);
				path.push_back(temp1);
				ppath.push_back(temp1);
			}
		}
		
		else if(q.second >= 0 && p.second < 0)						//only dest is present
		{
			cout<<"dest present"<<endl;
			vector<int> x;
			int j = 0;
			while(x.empty())
				x = get_backup(src,bpath[q.first][j++]);
			
						//get_primary(path, src, dest);
			temp1 = get_primary(bpath, src, dest);
			if(temp1.empty())
			{
				cout<<"no link disjoint primary"<<endl;
				temp = get_backup(src, dest);
				cout<<"New backup path:";display(temp);
				bpath.push_back(temp);
				//path.push_back(temp);
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
				path[q.first].insert(path[q.first].begin(), x.begin(), x.end()); 
				bpath[q.first].insert(bpath[q.first].begin(), x.begin(), x.end());
				display(bpath[q.first]);
				for(unsigned int i = 0; i < x.size(); i++)
					for(unsigned int j = 0; j < bpath[q.first].size(); j++)
						served.push_back(make_pair(x[i],bpath[q.first][j]));		
				path.push_back(temp1);
				ppath.push_back(temp1);
			}
		}
		
		else if(p.second < 0 && q.second < 0)   									//none is present
		{
			temp=get_backup(set_pairs[i].first,set_pairs[i].second);
			cout<<"None present"<<endl;
			//cout<<"New backup path:";display(temp);
			bpath.push_back(temp);
			//path.push_back(temp);
			cout<<"Backup Path: ",display(temp);
			//get_primary(path, set_pairs[i].first, set_pairs[i].second);
			
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
			
		}
	}
	cout<<"Total gain estreams: "<<gain<<endl;
	cout<<"Blocked requests: "<<block<<endl;
	fo<<gain;
}
