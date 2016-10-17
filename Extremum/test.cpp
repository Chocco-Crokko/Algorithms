#include <cstdio>
#include <cassert>
#include <iostream>
#include <random>
//исходный код
int almostBinarySearch(long long *arr, int left, int right);

int findExtremum(long long *arr, int n) {
    int left = 0, right = 2; // [left, right)
    // пока на концах отрезка [left, right] функция возрастает, смещаем диапазон
    while ((right < n) && (arr[left] < arr[left + 1]) && (arr[right - 1] < arr[right])) {
        left = right;
        right <<= 1;
        if (right > n) {
            right = n;
            break;
        }
    }
    return almostBinarySearch(arr, left, right);
}

int almostBinarySearch(long long *arr, int left, int right) {
    int mid = 0;
    bool isLeftLess, isRightLess;
    while (left < right) {
        mid = left + (right - left) / 2;
        if (right - left <= 2) {
            return arr[left] < arr[mid] ? mid : left;
        }
        isLeftLess = arr[mid - 1] < arr[mid];
        isRightLess = arr[mid + 1] < arr[mid];
        assert(isLeftLess || isRightLess); // не должно быть ..., 6, 4, 7, ...
        if (isLeftLess && isRightLess) {
            return mid;
        }
        else if (isLeftLess && !isRightLess) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }
    return mid;
}
// начало тестов
using std::cout;
using std::cin;
using std::endl;

void test(int k, int n) {
    std::uniform_int_distribution<int> d;
    std::default_random_engine eng;
    for (int size = k; size <= n; size++) {
        long long *arr = new long long[size];
        for (int i = 0; i < size; i++) {
            long long val = d(eng);
            for (int j = 0; j < size; j++) {
                arr[j] = val;
                if (j < i) {
                    val += d(eng);
                }
                else {
                    val -= d(eng);
                }
            }
            if (findExtremum(arr, size) != i) {
                cout << "size = " << size << endl;
                for (int a = 0; a < size; ++a) {
                    cout << arr[a] << ' ';
                }
                cout << endl;
                return;
            }
        }
        cout << size << " - correct\n";
        delete[] arr;
    }
}

int main() {
    int k, n;
    cin >> k >> n;
    test(k, n);
    return 0;
}
