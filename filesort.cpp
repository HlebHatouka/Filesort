#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <exception>
#include<experimental/filesystem>

using namespace std;
namespace fs = std::experimental::filesystem;

void read_from_file(const string &path, vector<string> &text);
void delete_words(vector<string> &text, const string &word);
inline void sort_lines(vector<string> &text);
inline bool sorting(string first, string second);
void write_in_file(const vector<string> &text);

template <typename T>
void buble (vector<T> &text);

int main(int argc, char *argv[])
{
	if (argc!=3)
	{
		cerr << "use: " << *argv << " <path> <word>" << endl;
		exit(EXIT_FAILURE);
	}

	try
	{
		if (fs::exists(argv[1]))
		{
			vector<string> text;
			read_from_file(argv[1], text);
			delete_words(text, argv[2]);
			sort_lines(text);
			//buble(text);
			write_in_file(text);
		}
		else
		{
			cerr << "file does not exist";
			exit(EXIT_FAILURE);
		}
	}
	catch (const exception& e)
	{
		cerr << e.what();
		exit(EXIT_FAILURE);
	}
    return 0;
}

void read_from_file(const string &path, vector<string> &text)
{
	ifstream fin(path);
	string line;
	while (getline(fin, line))
	{
		text.emplace_back(line);
	}
	fin.close();
}

void delete_words(vector<string>& text, const string &word)
{
	for (auto &line : text)
	{
		istringstream istr(line);
		string substr;
		auto start = istr.tellg();
		while (istr>>substr)
		{
			if (substr == word)
				line.erase(unsigned(start), word.size()+1);
			start = istr.tellg();
		}
	}
}

void sort_lines(vector<string>& text)
{
	sort(text.begin(), text.end(), sorting);
}

bool sorting(string first, string second)
{
	for (auto &symbol : first)
		symbol = tolower(symbol);
	for (auto &symbol : second)
		symbol = tolower(symbol);

	return first < second;
}

void write_in_file(const vector<string>& text)
{
	ofstream fout("newfile.txt");
	for (auto iter = text.cbegin(); iter != text.cend(); ++iter)
		fout << *iter << endl;

	fout.close();
}

template <typename T>
void buble(vector<T> &text)
{
	 for (int i = 0; i < text.size() - 1; ++i) 
	 {
        for (int j = 0; j < text.size() - i - 1; ++j)
         {
            if (tolower(text[j]) >tolower(text[j + 1]))
             {
                T temp(text[j]);
                text[j] = text[j + 1];
                text[j + 1] = temp;
            }
        }
    }
}
