#pragma once
#include "Base.h"

matrix Stupid_LCS(const string &A, const string &B)
{
    size_t  n = B.length(),
        m = A.length();
    
    matrix ans(m, vector<int>(n, 0)),
        res(m, vector<int>(n, 0));

    
    int tres;
    for (size_t l = 0; l < m; l++)
    {
        size_t offset = l;
        for (size_t i = 0; i < m - offset; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                tres = 0;
                if (i != 0)
                    tres = res[i - 1][j];
                if (j != 0)
                    tres = max(tres, res[i][j - 1]);
                if (A[i + offset] == B[j])
                {
                    if (i != 0 && j != 0)
                        tres = max(tres, res[i - 1][j - 1] + 1);
                    else
                        tres = max(tres, 1);
                }
                res[i][j] = tres;
            }
        }
        for (size_t j = 0; j < n; j++)
            ans[l][j] = res[m - offset - 1][j];
    }
    return ans;
}