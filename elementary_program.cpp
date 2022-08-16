// 2.1 Array
void evenOdd(vector<int>& arr) {
    int l = 0;
    int r = arr.size() - 1;
    
    while (l < r) {
        if (arr[l] % 2 == 0) {
            ++l;
        }
        else {
            std::swap(arr[l], arr[r--]);
        }
    }
}
