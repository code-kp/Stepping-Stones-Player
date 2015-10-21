#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

#define fli(i,x,y) for(ll i = x; i < y ; i++ )

vector<pair<ll,ll> > lst;
ll arr[12][12], dup[12][12];

// to check the boundary limit
bool checkthis(ll i, ll j){
	if(i>=0 && i<12)
		if(j>=0 && j<12)
			return 1;

	return 0;
}

bool checkBound(ll i,ll j){
	if(i == 0 || i == 11 || j == 0 || j == 11)
		return 1;

	return 0;
}

bool checkCorner(ll i,ll j){
	if(i == 0 || i == 11){
		if(j == 0 || j == 11)
			return 1;
	}

	return 0;
}

//find the value gained if n is placed at poll i,j
vector<ll> findVal(ll i,ll j,ll n){
	
	ll ans=0;
	
	vector<ll> cot(8);

	ll chI = 1,chJ = 1;
	//top - right
	while(checkthis(i-chI,j+chJ) && arr[i-chI][j+chJ] == (3^n)){
		cot[0]++;

		chI++,chJ++;
	}
	if(!(checkthis(i-chI,j+chJ) && arr[i-chI][j+chJ] == n))
		cot[0] = 0;

	//bottom - right
	chI = 1, chJ = 1;
	while(checkthis(i+chI,j+chJ) && arr[i+chI][j+chJ] == (3^n)){
		cot[1]++;

		chI++,chJ++;
	}
	if(!(checkthis(i+chI,j+chJ) && arr[i+chI][j+chJ] == n))
		cot[1] = 0;

	//bottom - left
	chI = 1, chJ = 1;
	while(checkthis(i+chI,j-chJ) && arr[i+chI][j-chJ] == (3^n)){
		cot[2]++;
		chI++,chJ++;
	}
	if(!(checkthis(i+chI,j-chJ) && arr[i+chI][j-chJ] == n))
		cot[2] = 0;

	//top - left
	chI = 1, chJ = 1;
	while(checkthis(i-chI,j-chJ) && arr[i-chI][j-chJ] == (3^n)){
		cot[3]++;

		chI++,chJ++;
	}
	if(!(checkthis(i-chI,j-chJ) && arr[i-chI][j-chJ] == n))
		cot[3] = 0;

	//top
	chI = 1;
	while(checkthis(i-chI,j) && arr[i-chI][j] == (3^n)){
		cot[4]++;

		chI++,chJ++;
	}
	if(!(checkthis(i-chI,j) && arr[i-chI][j] == n))
		cot[4] = 0;

	//bottom
	chI = 1;
	while(checkthis(i+chI,j) && arr[i+chI][j] == (3^n)){
		cot[5]++;

		chI++,chJ++;
	}
	if(!(checkthis(i+chI,j) && arr[i+chI][j] == n))
		cot[5] = 0;

	//left
	chJ = 1;
	while(checkthis(i,j-chJ) && arr[i][j-chJ] == (3^n)){
		cot[6]++;

		chI++,chJ++;
	}
	if(!(checkthis(i,j-chJ) && arr[i][j-chJ] == n))
		cot[6] = 0;

	//right
	chJ = 1;
	while(checkthis(i,j+chJ) && arr[i][j+chJ] == (3^n)){
		cot[7]++;

		chI++,chJ++;
	}
	if(!(checkthis(i,j+chJ) && arr[i][j+chJ] == n))
		cot[7] = 0;

	fli(i,0,8){
		ans += cot[i];
	}

	return cot;
}

void changeit(vector<ll> cot, pair<ll,ll> tmp,ll n){
	
	fli(i,1,cot[0]+1){
		arr[tmp.first - i][tmp.second + i] = n;
	}
	fli(i,1,cot[1]+1){
		arr[tmp.first + i][tmp.second + i] = n;
	}
	fli(i,1,cot[2]+1){
		arr[tmp.first + i][tmp.second - i] = n;
	}
	fli(i,1,cot[3]+1){
		arr[tmp.first - i][tmp.second - i] = n;
	}
	fli(i,1,cot[4]+1){
		arr[tmp.first - i][tmp.second] = n;
	}
	fli(i,1,cot[5]+1){
		arr[tmp.first + i][tmp.second] = n;
	}
	fli(i,1,cot[6]+1){
		arr[tmp.first][tmp.second - i] = n;
	}
	fli(i,1,cot[7]+1){
		arr[tmp.first][tmp.second + i] = n;
	}

	arr[tmp.first][tmp.second] = n;
}

ll changeTheir(ll n, ll cot){
	if(cot > 3){
		ll ans=0;
		fli(i,0,12)
			fli(j,0,12)
				if(arr[i][j] == n)
					if(checkCorner(i,j))
						ans += 1000;
					else if(checkBound(i,j))
						ans += 50;
					else
						ans++;
				else if(arr[i][j] == (3^n))
					if(checkCorner(i,j))
						ans -= 1000;
					else if(checkBound(i,j))
						ans -= 50;
					else
						ans--;


		return ans;
	}

	vector<pair<ll,ll> > lst;
	vector<vector<ll> > mainList;
	fli(i,0,12){
		fli(j,0,12){
			if(arr[i][j] == 0){
				vector<ll> val = findVal(i,j,n); 

				if(val.size() > 0){
					ll tmp = 0;
					fli(k,0,8)
						tmp += val[k];

					if(tmp > 0 ){	
						mainList.push_back(val);
						lst.push_back(make_pair(i,j));
					}
				}
			}
		}
	}

	ll len = lst.size();
	ll take[12][12];
	ll maxx;
	fli(k,0,len){
		pair<ll,ll> pr = lst[k];

		//copying original data
		fli(i,0,12)
			fli(j,0,12)
				take[i][j] = arr[i][j];

		changeit(mainList[k],pr,n);

		ll turn = changeTheir(n^3,cot+1);

		if(!k){
			maxx = turn;
		}
		else{
			if(cot & 1){
				maxx = min(maxx,turn);
			}
			else
				maxx = max(maxx,turn);
		}
		
		//replacing original data
		fli(i,0,12)
			fli(j,0,12)
				arr[i][j] = take[i][j];
	}


	return maxx;
}

int main(){
	//freopen("in.txt","r",stdin);
	ll n;
	cin>>n;

	fli(i,0,12)
		fli(j,0,12)
			cin>>arr[i][j];

	vector<pair<ll,ll> > lst;
	vector<vector<ll> > mainList;
	fli(i,0,12){
		fli(j,0,12){
			if(arr[i][j] == 0){
				vector<ll> val = findVal(i,j,n); 

				if(val.size() > 0){
					ll tmp = 0;
					fli(k,0,8)
						tmp += val[k];

					if(tmp > 0 ){
						mainList.push_back(val);
						lst.push_back(make_pair(i,j));
					}
				}
			}
		}
	}
	ll timed = time(0);
	ll len = lst.size();
	pair<ll,ll> ans;
	vector<pair<ll, pair<ll,ll> > > anss;
	bool flag = 0;
	fli(k,0,len){
		pair<ll,ll> pr = lst[k];

		if(checkCorner(pr.first,pr.second)){
			ans = pr;
			flag = 1;
			//cout<<pr.first<<" "<<pr.second<<"\n";
			break;
		}

		//copying data
		fli(i,0,12)
			fli(j,0,12)
				dup[i][j] = arr[i][j];

		changeit(mainList[k],pr,n);
		ll temp = changeTheir(n^3,1);

		anss.push_back(make_pair(temp,pr));

		//replacing original data
		fli(i,0,12)
			fli(j,0,12)
				arr[i][j] = dup[i][j];
	}

	if(!flag){
		sort(anss.begin(),anss.end());
		ans = anss[anss.size()-1].second;
/*		if(n == 2)
			ans = anss[0].second;
*/	}


	cout<<(char)('A'+ ans.first)<<""<<(char)('A'+ ans.second); 

	return 0;
}

