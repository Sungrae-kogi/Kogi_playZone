#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string str;
vector<char> result;
int value =0;

int main(){
	cin >> str;

	for(int i=0; i<str.size(); i++){
		//알파벳이면 결과 리스트에 삽입
		if(isalpha(str[i])){
			result.push_back(str[i]);
		}
		//숫자라면 따로 더해둔다 char에서 -'0'을 하면 그에맞는 숫자값이됨 꼼수임
		else{
			value += str[i] -'0';
		}
	}
	sort(result.begin(), result.end());

	for(int i=0; i<result.size(); i++){
		cout << result[i];
	}
	if(value !=0)
		cout << value;
	cout << endl;

	return 0;
}
