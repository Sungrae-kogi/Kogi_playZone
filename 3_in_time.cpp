#include <bits/stdc++.h>

using namespace std;

//c++에서는 전역변수로 선언하면 자동으로 0으로 초기화된다.
int h, cnt;

//특정 시각안에 '3'이 포함되어 있는지의 여부
bool check(int h, int m, int s){
	if(h%10==3 || m/10 == 3 || m%10==3 || s/10==3 || s%10 == 3) 
		return true;
	return false;
}

int main(){
	cin >> h;
	for(int i=0; i<=h; i++){
		for(int j=0; j<60; j++){
			for(int k=0; k<60; k++){
				if(check(i,j,k)){
					cnt++;
				}
			}
		}
	}
	cout << cnt << endl;

	return 0;
}
