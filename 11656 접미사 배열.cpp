#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

string str;
vector<string>temp;

int main() {
	cin >> str;
	int len = str.length();

	for (int i = 0; i < len; i++) {
		temp.push_back(str.substr(i, len - i));
	}

	
	sort(temp.begin(), temp.end());
	for (int i = 0; i < len; i++) {
		cout << temp[i] << endl;
	}
}
