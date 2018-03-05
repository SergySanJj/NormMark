#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>


using namespace std;

#define OK   1
#define HALT 0

#define WORK_MAX 1073741824

struct TRule
{
	string from;
	string to;
	bool halt = 0;
};

class NormalAlgo
{
public:
	NormalAlgo(char *adr)
	{
		ifstream fin(adr);

		char tmp[512] = "aa";
		bool switcher = 0;
		TRule tmpRule;
		while (fin >> tmp)
		{
			if (!switcher)
			{
				tmpRule.from = tmp;
				switcher = !switcher;
			}
			else
			{
				
				switcher = !switcher;
				if (tmp[0] == '*')
				{
					tmpRule.halt = 1;
					tmpRule.to = tmp;
				}
				else
				{
					tmpRule.halt = 0;
					tmpRule.to = tmp;
				}
				this->rules.push_back(tmpRule);
			}
			
		}
	}

	void scilentWork(string strInput)
	{
		this->currentRow = strInput;
		int N = 0;
		while (step() && N < WORK_MAX)
			N++;
		clearOut();
	}
	void work(string strInput)
	{
		system("cls");

		this->currentRow = strInput;
		printStr();
		Sleep(1000);

		int N = 0;
		while (step() && N < WORK_MAX)
		{
			N++;
			system("cls");
			printStr();
			Sleep(1000);
		}
		system("cls");
		clearOut();
		printStr();

		if (N == WORK_MAX)
			cout << "\nToo many operations";
	}

	void printStr()
	{
		cout << "\n" << currentRow;
	}
private:
	vector<TRule> rules;
	string currentRow = "";

	bool step()
	{
		bool flag = 0;
		for (int i = 0; i < rules.size(); i++)
		{
			int tmpPos = this->currentRow.find(rules[i].from);
			if (tmpPos>=0)
			{
				
				//currentRow.replace(tmpPos, tmpPos + rules[i].from.size() - 1, rules[i].to);
				//currentRow.replace( rules[i].to);
				//currentRow.replace(0, tmpPos + rules[i].from.size(), rules[i].to);
				string rs="";
				for (int j = 0; j < tmpPos; j++)
					rs += currentRow[j];
				for (int j = 0; j < rules[i].to.size(); j++)
					rs += rules[i].to[j];
				for (int j = tmpPos +rules[i].from.size(); j < currentRow.size(); j++)
					rs += currentRow[j];
				this->currentRow = rs;

				if (rules[i].halt)
					return HALT;
				flag = 1;
				break;
			}
		}
		if (flag)
			return OK;
		return HALT;
	}

	void clearOut()
	{
		int pt = 0;
		while ((pt=currentRow.find("*")) != -1)
		{
			currentRow.replace(pt, 1, "");
		}
	}
	
};

int main()
{
	NormalAlgo NAM("prog.mark");
	NAM.work("@1@");

	cout << "\n";
	system("pause");
	return 0;
}


