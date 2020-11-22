#include <bits/stdc++.h>
using namespace std;

int tmin(int a,int b,int c){
	return min(a,min(b,c));
}

void alignments(string s,string t,vector<vector<int> > &dp,int i,int  j,vector<char> &vs,vector<vector<char> > &ans){
	if(i==0 && j==0){
		ans.push_back(vs);
		return;
	}
	if(i>0 && j>0){
		int m;
		if(s[i-1]==t[j-1])
			m=tmin(dp[i-1][j-1],dp[i-1][j]+1,dp[i][j-1]+1);
		else
			m=tmin(dp[i-1][j-1]+2,dp[i-1][j]+1,dp[i][j-1]+1);
		if(s[i-1]==t[j-1] && m==dp[i-1][j-1]){
			vs.push_back('_');
			alignments(s,t,dp,i-1,j-1,vs,ans);
			vs.pop_back();
		}
		if(s[i-1]!=t[j-1] && m==dp[i-1][j-1]+2){
			vs.push_back('s');
			alignments(s,t,dp,i-1,j-1,vs,ans);
			vs.pop_back();
		}
		if(m==dp[i-1][j]+1){
			vs.push_back('d');
			alignments(s,t,dp,i-1,j,vs,ans);
			vs.pop_back();
		}
		if(m==dp[i][j-1]+1){
			vs.push_back('i');
			alignments(s,t,dp,i,j-1,vs,ans);
			vs.pop_back();
		}
	}
	else if(i>0){
		vs.push_back('d');
		alignments(s,t,dp,i-1,j,vs,ans);
		vs.pop_back();
	}
	else{
		vs.push_back('i');
		alignments(s,t,dp,i,j-1,vs,ans);
		vs.pop_back();
	}
}

int main(){
	// cout<<"Input 2 strings:"<<endl;
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  	#endif
	string s,t;
	cin>>s>>t;
	int n=s.length();
	int m=t.length();
	vector<vector<int> > dp(n+1,vector<int> (m+1));
	for(int i=1;i<=n;i++){
		dp[i][0]=dp[i-1][0]+1;
	}
	for(int i=1;i<=m;i++){
		dp[0][i]=dp[0][i-1]+1;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s[i-1]==t[j-1])
				dp[i][j]=tmin(dp[i-1][j]+1,dp[i][j-1]+1,dp[i-1][j-1]);
			else
				dp[i][j]=tmin(dp[i-1][j]+1,dp[i][j-1]+1,dp[i-1][j-1]+2);
		}
	}
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			cout<<dp[i][j]<<" ";
		}
		cout<<endl;
	}
	vector<vector<char> > ans;
	vector<char> vs;
	alignments(s,t,dp,n,m,vs,ans);
	cout<<ans.size()<<endl;
	for(int j=0;j<ans.size();j++){
		int x=ans[j].size();
		for(int i=x-1;i>=0;i--){
			cout<<ans[j][i]<<"->";
		}
		cout<<"#"<<endl;
	}
	cout<<dp[n][m]<<endl;
	return 0;
}