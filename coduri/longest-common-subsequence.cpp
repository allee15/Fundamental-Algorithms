#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution{
public:
    int longestCommonSubsequence(string text1, string text2)
    {
        int nr=0;
        if(text1.size() >= text2.size())
        {
            vector<vector<int>>secv(text2.size()+1, vector<int>(text1.size()+1,0));
            for(int i=0;i<text2.size();i++)
                for(int j=0;j<text1.size();j++)
                    if(text2[i] == text1[j])
                        secv[i+1][j+1]= secv[i][j]+1;
                    else
                        secv[i+1][j+1]= max(secv[i][j+1], secv[i+1][j]);

            nr = secv[text2.size()][text1.size()];
        }
        else
        {
            vector<vector<int>>secv(text1.size()+1, vector<int>(text2.size()+1,0));
            for(int i=0;i<text1.size();i++)
                for(int j=0;j<text2.size();j++)
                    if(text1[i] == text2[j])
                        secv[i+1][j+1]= secv[i][j]+1;
                    else
                        secv[i+1][j+1]= max(secv[i][j+1], secv[i+1][j]);

            nr = secv[text1.size()][text2.size()];
        }

        return nr;
    }
};

// Complexitate: O(M*N)