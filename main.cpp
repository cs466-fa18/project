#include <iostream>
#include <bits/stdc++.h>
#include <cstdlib>
#include <random>
#include "russians.h"
#include "hirscherg.h"

using namespace std;

typedef long long ll;

typedef vector<int> vint;
typedef pair<vint, vint> vpair;


int edit_distance(const vector<int> &v, const vector<int> &w) {
    unsigned long m = v.size() + 1, n = w.size() + 1;
    vector<vector<int> > dp(m, vector<int>(n));

    // Initialize borders
    for (int i = 0; i < m; i++) {
        dp[i][0] = i;
    }


    for (int i = 0; i < n; i++) {
        dp[0][i] = i;
    }

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (v[i - 1] == w[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
            }
        }
    }

    return dp[m - 1][n - 1];
}


vector<int> string_to_vector(const string &s) {
    vector<int> result(s.length());
    for (int i = 0; i < s.length(); i++) {
        result[i] = s[i];
    }
    return result;
}

vector<int> generate_random_array(int n, int s) {
    mt19937 rng;
    rng.seed(std::random_device()());
    uniform_int_distribution<mt19937::result_type> dist(0, s - 1);

    vector<int> result;
    for (int i = 0; i < n; i++) {
        result.push_back(dist(rng));
    }
    return result;
}

string generate_random_string(int n, int s) {
    mt19937 rng;
    rng.seed(std::random_device()());
    uniform_int_distribution<mt19937::result_type> dist(0, s - 1);

    vector<char> result;
    for (int i = 0; i < n; i++) {
        result.push_back('0' + (char) dist(rng));
    }
    return string(result.begin(), result.end());
}

int char_count(string s) {
    int r = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != '-')
            r++;
    }
    return r;
}

void print_alignment(pstring alignment) {
    cout << alignment.first << endl;
    cout << alignment.second << endl;
}

void test1() {
    string sequence1 = "001011011001001";
    for (int i = 0; i < 3; i++) {
        sequence1 += sequence1;
    }
    string sequence2 = "001011110101001";
    for (int i = 0; i < 6; i++) {
        sequence2 += sequence2;
    }
    map<int, vector<int> > result;

    pstring alignment = hirschberg_russians(sequence1, sequence2, 4, 2);
    print_alignment(alignment);
    cerr << "Edit distance naive: " << edit_distance(string_to_vector(sequence1), string_to_vector(sequence2)) << endl;
}

void test2() {
    string seq1 = generate_random_string(800, 2);
    string seq2 = generate_random_string(1000, 2);
    cerr << "Sequence 1: " << seq1 << endl;
    cerr << "Sequence 2: " << seq2 << endl;

    pstring alignment = hirschberg_russians(seq1, seq2, 4, 2);
    print_alignment(alignment);
    cerr << "Len1: " << char_count(alignment.first) << "\t" << "Len2: " << char_count(alignment.second) << endl;
    cerr << "Edit distance naive: " << edit_distance(string_to_vector(seq1), string_to_vector(seq2)) << endl;
}

int main() {
    test2();
}