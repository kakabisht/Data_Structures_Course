#include <iostream>
#include <string>
#include <vector>

using std::string;
using namespace std;

typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    for (size_t i = 0; i + s.size() <= t.size(); ++i)
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    return ans;
}

ull hash_func(const string& s,const ull &prime, const ull &x)
{
	unsigned long long hash = 0;
	for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
		hash = (hash * x + s[i]) % prime;
	return hash; 
}
std::vector<ull> PrecomputeHash(const string& T, const string& t_substr, const size_t &pattern_size, const ull &prime, const ull &x)
{
	size_t text_size = T.size();
	vector<ull> H(text_size - pattern_size + 1);

	H[text_size - pattern_size] = hash_func(t_substr, prime, x);
	
	
	ull y = 1;
	for (size_t i = 1; i <= pattern_size; ++i)
	{
		y = (y * x) % prime;
	}
	

	for (int i = text_size - pattern_size - 1; i >= 0; --i)
	{
		H[i] = (ull)(((H[i + 1] * x) + T[i] - (y * T[i + pattern_size])) % prime);
	}
	return H;
}

void RibinKarp(const Data& input) {
	// parse the input;
	const string& p = input.pattern, t = input.text;
	ull prime = 100000007; // We can try bigger prime numbers to minimize the probability of missing the substring and false alarms/false positives.
	ull x = 1;
	
	size_t pattern_size = p.size();
	size_t text_size = t.size();

	ull pattern_hash = hash_func(p, prime, x);
	string t_substr = t.substr(text_size - pattern_size, pattern_size);

	std::vector<ull> H = PrecomputeHash(t, t_substr, pattern_size, prime, x);
	
	for (int i = 0 ; i <= text_size - pattern_size; ++i)
	{
		if ((H[i] == pattern_hash) && (t.substr(i, pattern_size).compare(p) == 0)) {
			std::cout << i << " ";
		}
	}

	std::cout << std::endl;
}



int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    RibinKarp(read_input());

    return 0;
}
