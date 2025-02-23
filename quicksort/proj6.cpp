#include <iostream> //input 
#include <string> 
#include <unordered_map> // hashtable
#include <cctype>  
#include <vector>
#include <algorithm> 
#include <chrono>
using namespace std;

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    char ch;
    string current;
    unordered_map<string, int> wordCount;   // setting up the 3 hashtables
    unordered_map<string, int> numberCount;
    unordered_map<char, int> charCount;

    unordered_map<string, int> wordPos;  // to preserve the first occurance of a word/number
    unordered_map<string, int> numberPos;
    int position = 0;
    while(cin.get(ch))
    {
        charCount[ch]++;

        if (isalpha(ch))
        {
            if(!current.empty() && isdigit(current[0]))
            // current is a number, store before resetting and creating new current
            {
                numberCount[current]++;
                if(numberPos.find(current) == numberPos.end())
                {
                    numberPos[current] = position;
                }
                current.clear();
            }
            current += tolower(ch);
        }
        else if (isdigit(ch))
        {
            if(!current.empty() && isalpha(current[0]))
            {
                wordCount[current]++;
                if(wordPos.find(current) == wordPos.end())
                {
                    wordPos[current] = position;
                }
                current.clear();
            }
            current += tolower(ch);
        }
        else // ex, space
        {
            if (!current.empty())
            {
                if (isalpha(current[0]))
                {
                    wordCount[current]++;
                    if (wordPos.find(current) == wordPos.end())
                    {
                        wordPos[current] = position;
                    }
                }
                else if (isdigit(current[0]))
                {
                    numberCount[current]++;
                    if (numberPos.find(current) == numberPos.end())
                    {
                        numberPos[current] = position;
                    } 
                }
                current.clear(); // resets current word/number
            }
        }
        position++;
    }

    //End of input situations
    if (!current.empty())
    {
        if (isalpha(current[0]))
        {
            wordCount[current]++;

            if (wordPos.find(current) == wordPos.end())
            {
                wordPos[current] = position;
            }
        }
        else if (isdigit(current[0]))
        {
            numberCount[current]++;

            if (numberPos.find(current) == numberPos.end())
            {
                numberPos[current] = position;
            }
        }
    }

    // creating copy of hashtables as vector
    vector<pair<char, int>> charVec(charCount.begin(), charCount.end());
    vector<pair<string, int>> wordVec(wordCount.begin(), wordCount.end());
    vector<pair<string, int>> numberVec(numberCount.begin(), numberCount.end());

    // sort through each vector
    std::sort(charVec.begin(), charVec.end(), [](const auto &a, const auto &b)
    {
        if(a.second == b.second)
            return int(a.first) < int(b.first); // highest ASCII value
        return a.second > b.second;
    });

    std::sort(wordVec.begin(), wordVec.end(), [&wordPos](const auto &a, const auto &b)
    {
        if(a.second == b.second)
            return wordPos[a.first] < wordPos[b.first];
        return a.second > b.second;
    });

    std::sort(numberVec.begin(), numberVec.end(), [&numberPos](const auto &a, const auto &b)
    {
        if(a.second == b.second)
            return numberPos[a.first] < numberPos[b.first];
        return a.second > b.second;
    });

    cout << "\nTotal of " << charVec.size() << " characters, 10 most used characters:\n";
    for(int i = 0; i < min(10, (int)charVec.size()); i++)
    {
        cout << "No. " << i << ": ";
        if(charVec[i].first == '\n')
        {
            cout << "\\n";
        }
        else
        {
            cout << charVec[i].first;
        }   
        cout << "\t\t" << charVec[i].second << '\n';
    }

    cout << "\nTotal of " << wordVec.size() << " words, 10 most used words:\n";
    for(int i = 0; i < min(10, (int)wordVec.size()); i++)
    {
        cout << "No. " << i << ": " << wordVec[i].first << "\t\t" << wordVec[i].second << '\n';
    }

    cout << "\nTotal of " << numberVec.size() << " numbers, 10 most used numbers:\n";
    for(int i = 0; i < min(10, (int)numberVec.size()); i++)
    {
        cout << "No. " << i << ": " << numberVec[i].first << "\t\t" << numberVec[i].second << '\n';
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time: " << duration.count() << " seconds\n";
    return 0;
}