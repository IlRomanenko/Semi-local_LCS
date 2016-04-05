#include "Base.h"
#include "Tiskin_LCS.h"
#include "Stupid_LCS.h"

namespace generator
{
    random_device engine;

    pair<string, string> generateStrings(size_t common, size_t length)
    {
        if (common == 0)
            common = 1;

        uniform_int_distribution<int> random('a', 'z');
        uniform_int_distribution<int> int_random(0, 1000);

        pair<string, string> ans;
        char chr;

        for (size_t i = 0; i < common; i++)
        {
            chr = random(engine);
            ans.first.push_back(chr);
            ans.second.push_back(chr);
        }

        size_t pos;
        for (size_t i = 0; i + common < length; i++)
        {
            pos = int_random(engine) % ans.first.length();
            ans.first.insert(ans.first.begin() + pos, random(engine));
            pos = int_random(engine) % ans.second.length();
            ans.second.insert(ans.second.begin() + pos, random(engine));
        }
        return ans;
    }

    void generateAndCheckTest(size_t common, size_t length, bool needLogging = false, string filename = "")
    {
        cout << "Common : " << common << "  Length : " << length << endl;
        auto strings = generateStrings(common, length);

        auto answer = Stupid_LCS(strings.first, strings.second);
        auto solution = calculateSuffixPrefixLCS(strings.first, strings.second);

        if (needLogging)
        {
            ofstream log(filename, ios_base::app);
            log << endl << endl << "Common : " << common << "  Length : " << length << endl;

            log << "A = " << strings.first << endl << "B = " << strings.second << endl;

            log << endl << "Answer : " << endl;
            for (size_t i = 0; i < strings.first.length(); i++)
            {
                for (size_t j = 0; j < strings.second.length(); j++)
                    log << answer[i][j] << ' ';
                log << endl;
            }

            log << endl << "Solution : " << endl;
            for (size_t i = 0; i < strings.first.length(); i++)
            {
                for (size_t j = 0; j < strings.second.length(); j++)
                    log << solution[i][j] << ' ';
                log << endl;
            }

            log.flush();
            log.close();
        }

        for (size_t i = 0; i < strings.first.length(); i++)
        {
            for (size_t j = 0; j < strings.second.length(); j++)
            {
                if (answer[i][j] != solution[i][j])
                {
                    cout << "Failed test !" << endl;
                    return;
                }
            }
        }
        cout << "Test passed" << endl << endl;
        return;
    }
};



int main()
{
    for (int i = 0; i < 20; i++)
    {
        generator::generateAndCheckTest((i + 1) * 20, (i + 1) * 100);
    }

    cout << endl << "With logging to simple.txt" << endl << endl;
    for (int i = 0; i < 5; i++)
    {
        generator::generateAndCheckTest((i + 1) * 20, (i + 1) * 100, true, "simple.txt");
    }

    
    cout << "End of testing" << endl;
    getchar();
    return 0;
}