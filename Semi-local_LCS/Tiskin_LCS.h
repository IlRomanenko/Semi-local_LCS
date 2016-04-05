#pragma once
#include "Base.h"

matrix calculateSuffixPrefixLCS(const string &A, const string &B)
{
    int m = A.length(), n = B.length(), q = max(n, m);

    matrix criticalPoint(4 * q + 1, vector<int>(4 * q + 1, 0));
    matrix res(4 * q + 1, vector<int>(4 * q + 1, 0));

    matrix ans(m, vector<int>(n, 0));   

    vector<int> criticalMoment(4 * q + 1, 0);

    int hor_offset = 2 * q, ver_offset = 2 * q, cur_i, cur_j;


    for (int j = -2 * q + m; j <= 2 * q; j++)
    {
        criticalMoment[j + hor_offset] = j - m;
        criticalPoint[j - m + hor_offset][j + hor_offset] = 1;
    }


    int j0, j1, i0, i1;
    for (int l = 0; l < m; l++)
    {
        cur_i = l + ver_offset;
        for (int i = 0; i < n; i++)
        {
            cur_j = i + hor_offset;

            j0 = cur_j + m - cur_i;
            j1 = cur_j + m - cur_i + 1;

            i0 = criticalMoment[j0 + hor_offset];
            i1 = criticalMoment[j1 + hor_offset];

            if (i0 < i1 && A[l] != B[i])
            {
                criticalPoint[i0 + ver_offset][j0 + hor_offset] = 0;
                criticalPoint[i0 + ver_offset][j1 + hor_offset] = 1;
                criticalPoint[i1 + ver_offset][j0 + hor_offset] = 1;
                criticalPoint[i1 + ver_offset][j1 + hor_offset] = 0;
                criticalMoment[j1 + hor_offset] = i0;
                criticalMoment[j0 + hor_offset] = i1;
            }
        }
    }



    for (int i = -q; i <= q; i++)
    {
        for (int j = -q; j <= i; j++)
            res[i + ver_offset][j + hor_offset] = j - i;
    }


    bool copy = false;

    for (int i = q - 1; i >= -m; i--)
    {
        cur_i = i + ver_offset;
        copy = false;
        for (int j = i + 1; j <= n; j++)
        {
            cur_j = j + hor_offset;

            if (criticalPoint[cur_i + 1][cur_j] == 1)
                copy = true;
            if (copy)
                res[cur_i][cur_j] = res[cur_i + 1][cur_j];
            else
                res[cur_i][cur_j] = min(res[cur_i][cur_j - 1] + 1, res[cur_i + 1][cur_j] + 1);
            res[cur_i][cur_j] = min(res[cur_i][cur_j], m);
        }
    }

    for (int i = 0; i < m; i++)
        for (int j = 1; j <= n; j++)
            ans[i][j - 1] = res[-i + ver_offset][j + hor_offset] - i;

    return ans;
}
