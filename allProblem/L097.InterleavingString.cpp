class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s3.size() != s1.size()+s2.size())return false;
        auto &A = s1, &B = s2, &C = s3;
        vector<vector<bool>>D(s1.size()+1, vector<bool>(s2.size()+1,0));
        D[0][0] = true;
        for (int i = 0; i <= s1.size(); ++i) {
            for (int j = 0; j <= s2.size(); j++) { 
                if (i == 0 && j == 0)continue;
                D[i][j] = (i>0 && D[i-1][j]==1 && C[i+j-1] == A[i-1]) ||
                    (j>0 && D[i][j-1]== 1 && C[i+j-1] == B[j-1]);
            }
        }
        return D[s1.size()][s2.size()];
    }
};
