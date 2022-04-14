#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<vector<pair<int, int>>> rotations;
int blockSize;
// arr에 해당하는 블럭의 90도 돌린 상태를 return
vector<string> rotate(const vector<string>& arr) {
	vector<string> ret(arr[0].size(), string(arr.size(), ' '));
	for (int i = 0; i < arr.size(); i++)
		for (int j = 0; j < arr[0].size(); j++)
			ret[j][arr.size() - i - 1] = arr[i][j];
	return ret;
}
// 블럭을 90도씩 돌려가면서 블럭의 제일 상단 왼쪽에 있는칸을 원점으로
// 블럭의 좌표들을 rotations에 저장한다.
void generateRotations(vector<string>& block) {
	rotations.clear();
	rotations.resize(4);
	for (int rot = 0; rot < 4; rot++) {
		int originY = -1, originX = -1;
		for(int i=0; i<block.size(); i++)
			for (int j = 0; j < block[i].size(); j++) 
				if (block[i][j] == '#') {
					// 원점설정
					if (originY == -1) {
						originY = i;
						originX = j;
					}
					// 원점을 기준으로 블럭의 좌표 삽입
					rotations[rot].push_back(make_pair(i - originY, j - originX));
				}
		// block 90도 돌리기
		block = rotate(block);
	}
	// 좌우 대칭일 경우 중복제거
	sort(rotations.begin(), rotations.end());
	rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());
	blockSize = rotations[0].size();
}
int boardH, boardW;
vector<string> board;
int covered[10][10];
// 지금까지 찾은 최적해
int best;
// delta가 1이면 블록놓기 -1이면 놓았던 블록 빼기
bool set(int y, int x, const vector<pair<int, int>>& block, int delta) {
	int ret = true;
	for (int i = 0; i < block.size(); i++) {
		int ny = y + block[i].first;
		int nx = x + block[i].second;
		// 게임판을 벗어나면 블럭못놓음
		if (ny < 0 || ny >= boardH || nx < 0 || nx >= boardW)
			ret = false;
		// 이미 채워져있으면 +1하고 ret = false한 다음 delta==-1일떄 -1
		else if ((covered[ny][nx] += delta) > 1)
			ret = false;
	}
	return ret;
}
// 남은 빈칸수의 합 / blockSize 만큼 블록을 더 채웠을때 best보다 작으면 가지치기
bool pruning(int placed) {
	int emptys = 0;
	for (int i = 0; i < boardH; i++)
		for (int j = 0; j < boardW; j++) {
			if (covered[i][j] == 0)
				emptys++;
		}
	return (emptys / blockSize) + placed <= best ? true : false;
}
// placed: 지금까지 놓은 블럭의 수
void search(int placed) {
	// 가지치기
	if (pruning(placed))return;
	int y = -1, x = -1;
	// 빈칸 찾는중
	for (int i = 0; i < boardH; i++) {
		for(int j=0; j<boardW; j++)
			if (covered[i][j] == 0) {
				y = i;
				x = j;
				break;
			}
		if (y != -1)break;
	}
	// 빈칸 없으면 return
	if (y == -1) {
		best = max(best, placed);
		return;
	}
	// 블록을 돌려가며 게임판 채워보기
	for (int i = 0; i < rotations.size(); i++) {
		if (set(y, x, rotations[i], 1))
			search(placed + 1);
		// 게임판 원상복구 
		set(y, x, rotations[i], -1);
	}
	// 채울 수 없는 빈칸은 일단 막아놓는다.
	covered[y][x] = 1;
	search(placed);
	covered[y][x] = 0;
}
int solve() {
	best = 0;
	for (int i = 0; i < boardH; i++) {
		for (int j = 0; j < boardW; j++)
			covered[i][j] = (board[i][j] == '#' ? 1 : 0);
	}
	search(0);
	return best;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		board.clear();
		int blockH, blockW;
		vector<string> block;
		cin >> boardH >> boardW >> blockH >> blockW;
		for (int i = 0; i < boardH; i++) {
			string str;
			cin >> str;
			board.push_back(str);
		}
		for (int i = 0; i < blockH; i++) {
			string str;
			cin >> str;
			block.push_back(str);
		}
		generateRotations(block);
		cout << solve() << endl;
	}
}