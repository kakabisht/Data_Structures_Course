#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

void max_sliding_window_naive(vector<int> const & A, int w) {
    for (size_t i = 0; i < A.size() - w + 1; ++i) {
        int window_max = A.at(i);
        for (size_t j = i + 1; j < i + w; ++j)
            window_max = max(window_max, A.at(j));

        cout << window_max << " ";
    }

    return;
}

void max_sliding_window(vector<int> const & A, int w) {

    int n = A.size();
    int left[n],right[n];
    
    for(int i = 0; i < n; i++){
        if(!(i%w))
            left[i] = A[i];
        else
            left[i] = max(left[i-1],A[i]);
    }
    

    for(int i = n-1; i >= 0; i--){
        if(i == n-1 || !((i+1)%w))
            right[i] = A[i];
        else
            right[i] = max(right[i+1],A[i]);
    }
    
    vector<int>ans;
    for(int i = 0; i <= n - w; i++){
        if(!(i%w)){
            ans.push_back(right[i]);
        }else{
            ans.push_back(max(left[i+w-1],right[i]));
        }
    }
    for (int i = 0; i < ans.size(); ++i)
        std::cout<<ans[i]<<" ";

}


int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window(A, w);

    return 0;
}