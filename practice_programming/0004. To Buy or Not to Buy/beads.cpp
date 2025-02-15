/**
 * brute force solution: check every combination of the strings
 * How to make it more efficient?
*/

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <climits>

using namespace std;

typedef vector<pair<char, int>> BeadCount;
typedef pair<int, int> ExtraMissing;

BeadCount count_beads(const string &s) {
    map<char, int> counts;
    for (char c : s) {
        counts[c]++;
    }
    BeadCount bead_count(counts.begin(), counts.end());
    sort(bead_count.begin(), bead_count.end());
    return bead_count;
}

BeadCount add_counts(const BeadCount &count1, const BeadCount &count2) {
    map<char, int> result;
    for (const auto &p : count1) {
        result[p.first] += p.second;
    }
    for (const auto &p : count2) {
        result[p.first] += p.second;
    }
    BeadCount combined(result.begin(), result.end());
    sort(combined.begin(), combined.end());
    return combined;
}

ExtraMissing count_extra_and_missing_beads(const BeadCount &total_counts, const BeadCount &required_counts) {
    map<char, int> total_map;
    for (const auto &p : total_counts) {
        total_map[p.first] += p.second;
    }
    
    map<char, int> required_map;
    for (const auto &p : required_counts) {
        required_map[p.first] += p.second;
    }
    
    int extra_beads = 0;
    for (const auto &p : total_map) {
        char c = p.first;
        int total = p.second;
        int required = required_map[c];
        extra_beads += max(0, total - required);
    }
    
    int missing_beads = 0;
    for (const auto &p : required_map) {
        char c = p.first;
        int required = p.second;
        missing_beads += max(0, required - total_map[c]);
    }
    
    return make_pair(extra_beads, missing_beads);
}

void main_solution() {
    string desired_string;
    int N;
    cin >> desired_string >> N;
    
    vector<string> shop_strings(N);
    for (int i = 0; i < N; ++i) {
        cin >> shop_strings[i];
    }
    
    BeadCount required_beads = count_beads(desired_string);
    // cout << "Required beads: ";
    // for (const auto &p : required_beads) {
    //     cout << p.first << ":" << p.second << ", ";
    // }
    // cout << endl;
    int required_beads_count = 0;
    for (const auto &p : required_beads) {
        required_beads_count += p.second;
    }

    vector<BeadCount> shop_bead_counts;
    for (const auto &s : shop_strings) {
        shop_bead_counts.push_back(count_beads(s));
    }
    // cout << "Shop beads: " << endl;
    // for (const auto &bead_count : shop_bead_counts) {
    //     for (const auto &p : bead_count) {
    //         cout << p.first << ":" << p.second << ", ";
    //     }
    //     cout << endl;
    // }
    
    // {collected_beads_tuple: (extra_beads, missing_beads)}
    map<BeadCount, ExtraMissing> dp;
    dp[{}] = make_pair(0, required_beads_count);
    
    // brute force solution: check every combination of the strings
    for (const auto &shop_beads : shop_bead_counts) {
        auto new_dp = dp;
        for (const auto &p : dp) {
            BeadCount collected_beads = p.first;
            BeadCount combined_beads = add_counts(collected_beads, shop_beads);
            
            ExtraMissing extra_and_missing = count_extra_and_missing_beads(combined_beads, required_beads);
            if (new_dp.find(combined_beads) == new_dp.end()) {
                new_dp[combined_beads] = extra_and_missing;
            }
        }
        dp = new_dp;
    }
    // // print dp
    // for(const auto &p : dp) {
    //     BeadCount collected_beads = p.first;
    //     ExtraMissing counts = p.second;
    //     cout << "Collected beads: ";
    //     for (const auto &p : collected_beads) {
    //         cout << p.first << ":" << p.second << ", ";
    //     }
    //     cout << "Extra: " << counts.first << ", Missing: " << counts.second << endl;
    // }
    
    int min_extra = INT_MAX;
    int min_missing = INT_MAX;
    for (const auto &p : dp) {
        ExtraMissing counts = p.second;
        int extra = counts.first;
        int missing = counts.second;
        if (missing == 0) {
            min_extra = min(min_extra, extra);
            min_missing = 0;
        } else {
            min_missing = min(min_missing, missing);
        }
    }
    
    if (min_missing > 0) {
        cout << "No " << min_missing << endl;
    } else {
        cout << "Yes " << min_extra << endl;
    }
}

int main() {
    main_solution();
    return 0;
}
