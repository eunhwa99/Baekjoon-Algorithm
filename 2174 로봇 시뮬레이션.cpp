#include<iostream>
using namespace std;
//dy={0,1,0,-1}
//dx={1,0,-1,0}
//dir={오,아,왼,위}

class robot {
	int y;
	int x;
	int dir;


public:
	robot() = default;
	robot(int y, int x, int d) {
		this->y = y;
		this->x = x;
		this->dir = d;
	}

public:
	int getX() {
		return this->x;
	}
	int getY() {
		return this->y;
	}
	void turnLeft() {
		this->dir += 3;
		this->dir %= 4;
	}
	void turnRight() {
		this->dir += 1;
		this->dir %= 4;
	}
	int move(int a, int b) { // 가로 세로
		int curdir = this->dir;
		if (curdir == 0) { //오
			this->x += 1;
			if (this->x >= a) return -1;
		}
		else if (curdir == 1) {
			this->y += 1;
			if (this->y >= b) return -1;
		}
		else if (curdir == 2) {
			this->x -= 1;
			if (this->x < 0) return -1;
		}
		else {
			this->y -= 1;
			if (this->y < 0) return -1;
		}
		return 1;
	}
};

/*
void robot::turnLeft() {

}

void robot::turnRight() {

}*/
int A, B, N, M;
robot* arr = new robot[101];
int chk[101][101], result;
int number[101], repeat[101];
char direction[101];

int main() {
	cin >> A >> B >> N >> M;
	
	for (int i = 0; i < N; i++) {
		int a, b, d;
		char c;
		cin >> a >> b >> c;

		if (c == 'E') d = 0;
		else if (c == 'W') d = 2;
		else if (c == 'N') d = 3;
		else d = 1;
		arr[i] = robot(B - b, a - 1, d);
		chk[B - b][a - 1] = i + 1;
	}
	
	
	for (int i = 0; i < M; i++) {
		cin >> number[i] >> direction[i] >> repeat[i];
	}

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < repeat[i]; j++) {
			if (direction[i] == 'L') {
				arr[number[i] - 1].turnLeft();
			}
			else if (direction[i] == 'R') {
				arr[number[i] - 1].turnRight();
			}
			else {
				int cx = arr[number[i] - 1].getX();
				int cy = arr[number[i] - 1].getY();

				if (arr[number[i] - 1].move(A, B) == -1) {
					result = 1;
					cout << "Robot " << number[i] << " crashes into the wall\n";
					return 0;
				}
				else {
					int x = arr[number[i] - 1].getX();
					int y = arr[number[i] - 1].getY();
					if (chk[y][x]) {
						cout << "Robot " << number[i] << " crashes into robot " << chk[y][x] << '\n';
						return 0;
					}
					else chk[cy][cx] = 0, chk[y][x] = number[i];

				}

			}
		}
	}
		cout << "OK";
}

