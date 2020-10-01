#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <map>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <set>
using namespace std;
typedef pair<int,int> pi;
string bstr;
int counter = 0;
int a, b, c;
char cc[100000];
int intt;
long long total = 0;
vector<string> sentence;

set<pi> bridge[100000];
long long totalweight[100000];

//mapping strings to int -- assigning every string an integer
//mapping int to string -- backtrack map

map<string, int> mmsi;
map<int, string> mmis;

int main(){
	
	printf("Welcome to Donald Trump sentence generator!\n");
	printf("Enter the bridge file: ");
	cin >> bstr;
	FILE * pFile;
	pFile = fopen(bstr.c_str(), "r");
	fscanf(pFile, "%d", &counter);
	for (int i = 1; i < counter; i++){
		fscanf(pFile, "%s %d", cc, &intt);
		mmis[intt] = (string)cc;
		mmsi[(string)cc] = intt;
	}
	
	fscanf(pFile, "%lld", &total);
	for (long long i = 0; i < total; i++){
		fscanf(pFile, "%d %d %d", &a, &b, &c);
		bridge[a].insert(make_pair(b, c));
	}
	fclose(pFile);
	for (int i = 0; i < counter; i++){
		for (set<pi>::iterator it = bridge[i].begin(); it != bridge[i].end(); it++){
			totalweight[i] += it -> second;
		}
	}
	srand(time(NULL));
	while (sentence.size() < 5){
		sentence.clear();
		int curnode = 0;
		while (curnode < 1 || curnode > 3){
			
			int path = rand() % totalweight[curnode];
			for (set<pi>::iterator it = bridge[curnode].begin(); it != bridge[curnode].end(); it++){
				if (path - (it -> second) <= 0){
					sentence.push_back(mmis[it -> first]);
					curnode = it -> first;
					break;
				} 
				path -= (it -> second);
			}
		}
	}

	for (vector<string>::iterator it = sentence.begin(); it != sentence.end(); it++){
		if (it != sentence.begin()) printf(" ");
		printf("%s", (*it).c_str());
	}
	printf("\n");
	
	
}
