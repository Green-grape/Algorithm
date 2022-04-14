#include<iostream>
#include<cstring>
using namespace std;
const int MAXN = 20;
// candidates[길이][합][이미 넣은 숫자 집합] = 넣을 수 있는 숫자 집합
int candidates[10][46][1024];
// set에 있는 숫자들의 갯수
int getSize(int set) {
	int ret = 0;
	for (int i = 1; i < 10; i++)
		if (set & (1 << i))
			ret++;
	return ret;
}
// set에 있는 숫자들의 합
int getSum(int set) {
	int ret = 0;
	for (int i = 1; i < 10; i++) {
		if (set & (1<<i))
			ret += i;
	}
	return ret;
}
// candidates미리 계산
void generateCandidates() {
	memset(candidates, 0, sizeof(candidates));
	// [1,9]의 부분집합을 전부 생성
	for (int set = 0; set < 1024; set += 2) {
		int l = getSize(set), s = getSum(set);
		// set의 모든 부분집합에 대해 candidates갱신
		int subset = set;
		while (true) {
			candidates[l][s][subset] |= (set & ~subset);
			if (subset == 0) break;
			subset = (subset - 1) & set;
		}
	}
}
// color: 각 칸의 색깔(검은칸, 힌트칸 = 0, 흰칸 = 1)
// value: 각 흰 칸에 쓴 숫자(아직 쓰지 않은 칸은 0)
// hint: 각 칸에 해당하는 두 힌트의 번호
int n, color[MAXN][MAXN], value[MAXN][MAXN], hint[MAXN][MAXN][2];
// sum: 힌트칸에 쓰인 숫자 length: 힌트칸에 해당하는 흰칸의 수
// known: 힌트 칸에 해당하는 흰 칸에 쓰인 숫자들의 집합
int q, sum[MAXN * MAXN], length[MAXN * MAXN], known[MAXN * MAXN];
// (y,x)에 val을 쓴다
void put(int y, int x, int val) {
	for (int h = 0; h < 2; h++)
		known[hint[y][x][h]] += (1 << val);
	value[y][x] = val;
}
// (y,x)에 쓴 val를 지운다
void remove(int y, int x, int val) {
	for (int h = 0; h < 2; h++)
		known[hint[y][x][h]] -= (1 << val);
	value[y][x] = 0;
}
// 힌트 번호가 주어질때 후보의 집합을 반환
int getCandHint(int hint) {
	return candidates[length[hint]][sum[hint]][known[hint]];
}
// 좌표가 주어질 때 해당 칸에 들어갈 수 있는 후보의 집합을 반환
int getCandCoord(int y, int x) {
	return getCandHint(hint[y][x][0]) &
		getCandHint(hint[y][x][1]);
}
// value에 적힌 값을 출력
void printSolution() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << value[i][j] << " ";
		cout << endl;
	}
}
// 답을 찾았으면 true, 아니면 false를 반환
bool search() {
	// 흰 칸중 후보수가 최소인 칸 찾기
	int y = -1, x = -1, minCands = 1023;
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			if (color[i][j] == 1 && value[i][j] == 0) {
				int cands = getCandCoord(i, j);
				if (getSize(minCands) > getSize(cands)) {
					minCands = cands;
					y = i; x = j;
				}
			}
	// 흰칸이 있는데 들어갈 수 있는 숫자가 없으면 return false;
	if (minCands == 0) return false;
	// 모든칸이 채워졌으면 출력후 return true;
	if (y == -1) {
		printSolution();
		return true;
	}
	// 빈 칸에 대해서 계산한 부분집합의 요소들을 하나씩 대입해 본다
	for (int val = 1; val < 10; val++) 
		if (minCands & (1 << val)) {
			put(y, x, val);
			if (search()) return true;
			remove(y, x, val);
		}
	return false;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		memset(hint, 0, sizeof(hint));
		memset(value, 0, sizeof(value));
		memset(color, 0, sizeof(color));
		memset(sum, 0, sizeof(sum));
		memset(length, 0, sizeof(length));
		memset(known, 0, sizeof(known));
		cin >> n;
		for(int i=0; i<n; i++)
			for (int j = 0; j < n; j++) {
				cin >> color[i][j];
			}
		cin >> q;
		for (int i = 0; i < q; i++) {
			int y, x, dir, s;
			cin >> y >> x >> dir >> s;
			hint[y - 1][x - 1][dir] = i;
			sum[i] = s;
			int len = 0;
			// 힌트가 담당하는 흰 칸들을 가로 세로 나눠서 
			// 힌트가 담당하는 length와 흰칸에 대한 hint값을 갱신한다.
			if (dir == 0) {
				int leny = y - 1, lenx = x;
				while (color[leny][lenx]) {
					hint[leny][lenx][0] = i;
					lenx++;
					len++;
				}
			}
			else {
				int leny = y, lenx = x - 1;
				while (color[leny][lenx]) {
					hint[leny][lenx][1] = i;
					leny++;
					len++;
				}
			}
			length[i] = len;
		}
		generateCandidates();
		search();
	}
}