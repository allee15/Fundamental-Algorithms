#include <iostream>
#include <vector>

using namespace std;

class Solution{
public:
    string alegere(string &s1, string &s2, string &s3)
    {
        string sol=s1;
        if(sol.size()>s2.size())
            sol=s2;
        if(sol.size()>s3.size())
            sol=s3;

        return sol;
    }

    string shortestCommonSupersequence(string str1, string str2)
    {
        vector<vector<string>> secv(str1.size()+1, vector<string>(str2.size()+1,""));
        for(int i=1;i<=str1.size();i++)
            secv[i][0]=secv[i-1][0]+ str1[i-1];

        for(int i=1;i<=str2.size();i++)
            secv[0][i]=secv[0][i-1]+str2[i-1];

        for(int i=1;i<=str1.size();i++)
        {
            for(int j=1;j<=str2.size();j++)
            {
                string t;
                if(str1[i-1] == str2[j-1])
                    t=secv[i-1][j-1]+str1[i-1];
                else
                    t=secv[i-1][j-1]+str1[i-1]+str2[j-1];

                string t1=secv[i-1][j]+str1[i-1];
                string t2= secv[i][j-1]+str2[j-1];
                secv[i][j] = alegere(t1,t2,t);
            }
        }

        return secv[str1.size()][str2.size()];
    }
};

// Complexitate: O(M*N)
