class Solution {
public:
    bool patternMatching(string pattern, string value);
};

bool Solution::patternMatching(string pattern, string value) {
    // 先处理pattern或者value为空的情况
    if (pattern.empty()) return value.empty();
    int cnta = 0, cntb = 0;
    for (auto c: pattern) if (c == 'a') cnta++; else cntb++;
    if (value.empty()) return cnta  == 0 || cntb == 0;
    // pattern和value均非空，处理pattern中某个字符出现次数为0的情况
    if (cnta == 0 || cntb == 0) {
        if (cntb == 0) cntb = cnta;
        if (value.size() % cntb) return false;
        int lenb = value.size() / cntb;
        string b = value.substr(0, lenb);
        for (int i = lenb - 1; i < value.size(); i += lenb) {
            for (int j = i, k = b.size() - 1; k >= 0; k--, j--)
                if (value[j] != b[k]) return false;
        }
        return true;
    }
    // 处理cnta与cntb都不为0的情况
    // 枚举二元一次方程的根，lena和lenb
    for (int lena = 0; lena * cnta <= value.size(); lena++) {
        if ((value.size() - lena * cnta) % cntb) continue;
        int lenb = (value.size() - lena * cnta) / cntb;
        string a = "", b = "";
        int idx = 0;
        bool flag = true;
        for (int i = 0; i < pattern.size(); i++) {
            if (pattern[i] == 'a') {
                if (lena == 0) continue;
                if (a.empty()) { a = value.substr(idx, lena); idx += lena; continue;}
                int j = 0;
                for (; j < a.size() && idx < value.size(); j++, idx++)
                    if (value[idx] != a[j]) { flag = false; break; }
                if (j < a.size()) { flag = false; break; }
            } else {
                if (lenb == 0) continue;
                if (b.empty()) { b = value.substr(idx, lenb); idx += lenb; continue; }
                int j = 0;
                for (; j < b.size() && idx < value.size(); j++, idx++)
                    if (value[idx] != b[j]) { flag = false; break; }
                if (j < b.size()) { flag = false; break; }
            }
        }
        if (flag) return true;
    }
    return false;
}
