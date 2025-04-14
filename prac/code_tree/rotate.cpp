#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 시계방향 90도 회전 (새 배열 할당)
vector<vector<int>> rotate90Clockwise(const vector<vector<int>>& matrix) {
    if(matrix.empty()) return {};
    int r = matrix.size();
    int c = matrix[0].size();
    // 회전 후 배열 크기는 c x r
    vector<vector<int>> rotated(c, vector<int>(r, 0));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            // (i, j) -> (j, r-1-i)
            rotated[j][r - 1 - i] = matrix[i][j];
        }
    }
    return rotated;
}
void inplace_cw_90(vector<vector<int>>& mat) {
    // NxN 일 때
    int n = mat.size();
    // 1. 전치 (transpose)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(mat[i][j], mat[j][i]);
        }
    }
    // 2. 각 행을 뒤집기
    for (int i = 0; i < n; i++) {
        reverse(mat[i].begin(), mat[i].end());
    }
}

// 반시계방향 90도 회전 (새 배열 할당)
vector<vector<int>> rotate90Counterclockwise(const vector<vector<int>>& matrix) {
    if(matrix.empty()) return {};
    int r = matrix.size();
    int c = matrix[0].size();
    // 회전 후 배열 크기는 c x r
    vector<vector<int>> rotated(c, vector<int>(r, 0));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            // (i, j) -> (c-1-j, i)
            rotated[c - 1 - j][i] = matrix[i][j];
        }
    }
    return rotated;
}

void inplace_ccw_90(vector<vector<int>>& mat) {
    // NxN 일 때
    int n = mat.size();
    // 1. 전치 (transpose)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(mat[i][j], mat[j][i]);
        }
    }
    // 2. 각 열을 뒤집기
    for (int j = 0; j < n; j++) {
        for (int i = 0, k = n - 1; i < k; i++, k--) {
            swap(mat[i][j], mat[k][j]);
        }
    }
}

// 180도 회전 (새 배열 할당)
vector<vector<int>> rotate180(const vector<vector<int>>& matrix) {
    if(matrix.empty()) return {};
    int r = matrix.size();
    int c = matrix[0].size();
    // 180도 회전은 크기가 그대로 r x c
    vector<vector<int>> rotated(r, vector<int>(c, 0));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            // (i, j) -> (r-1-i, c-1-j)
            rotated[r - 1 - i][c - 1 - j] = matrix[i][j];
        }
    }
    return rotated;
}

// 행렬 출력 함수
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int elem : row)
            cout << elem << " ";
        cout << "\n";
    }
}

int main() {
    // 예시: 3x4 직사각형 배열
    vector<vector<int>> mat = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    cout << "원본 배열:\n";
    printMatrix(mat);

    auto cw = rotate90Clockwise(mat);
    cout << "\n시계방향 90도 회전:\n";
    printMatrix(cw);

    auto ccw = rotate90Counterclockwise(mat);
    cout << "\n반시계방향 90도 회전:\n";
    printMatrix(ccw);

    auto rot180 = rotate180(mat);
    cout << "\n180도 회전:\n";
    printMatrix(rot180);

    return 0;
}
