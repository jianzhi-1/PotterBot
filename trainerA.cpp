#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <dirent.h>
using namespace std;
//trainerA will start building bridges from scratch
typedef pair<int,int> pi;
char cc[1000];
int counter = 2;

vector <string> v;
char ct;
char dir_name[50];
set<pi> bridge[100000];
map<string, int> mmsi;
map<int, string> mmis;
//mmis[0] = start of string
//mmis[1] = end of string

bool notempty(string sentence){
	bool emp = true;
	for (int i = 0; i < sentence.length(); i++){
		if (sentence[i] != ' '){
			emp = false;
			break;
		}
	}
	return emp;
}

void processv(){
	for (int i = 0; i < v.size(); i++){
		if (mmsi.find(v[i]) == mmsi.end()){
			mmsi[v[i]] = counter;
			mmis[counter] = v[i];
			counter++;
		}
		if (i == 0){
			if (bridge[0].empty() || bridge[0].lower_bound(make_pair(0, -1)) -> first != 0){
				bridge[0].insert(make_pair(mmsi[v[0]], 1));
			} else {
				set<pi>::iterator it = bridge[0].lower_bound(make_pair(mmsi[v[0]], -1));
				pi cur = *it;
				bridge[0].erase(it);
				bridge[0].insert(make_pair(mmsi[v[0]], cur.second + 1)); //add one since probability increases

			}
		}
		if (i == v.size()){
			if (bridge[mmsi[v[i]]].empty() || bridge[mmsi[v[i]]].lower_bound(make_pair(1, -1)) -> first != 1){
				//create new bridge
				bridge[mmsi[v[i]]].insert(make_pair(1, 1));
			} else {
				set<pi>::iterator it = bridge[mmsi[v[i]]].lower_bound(make_pair(1, -1));
				pi cur = *it;
				bridge[mmsi[v[i]]].erase(it);
				bridge[mmsi[v[i]]].insert(make_pair(cur.first, cur.second + 1)); //add one since probability increases
			}
			
			continue;
		}
		if (mmsi.find(v[i + 1]) == mmsi.end()){
			mmsi[v[i + 1]] = counter;
			mmis[counter] = v[i + 1];
			counter++;
		}
		if (bridge[mmsi[v[i]]].empty() || bridge[mmsi[v[i]]].lower_bound(make_pair(mmsi[v[i + 1]], -1)) -> first != 1){
			//create new bridge
			bridge[mmsi[v[i]]].insert(make_pair(mmsi[v[i + 1]], 1));
		} else {
			set<pi>::iterator it = bridge[mmsi[v[i]]].lower_bound(make_pair(mmsi[v[i + 1]], -1));
			pi cur = *it;
			bridge[mmsi[v[i]]].erase(it);
			bridge[mmsi[v[i]]].insert(make_pair(cur.first, cur.second + 1)); //add one since probability increases
		}
		
	}
}

void decompose(string sentence){
	v.clear();
	while (sentence.length()>0 && !notempty(sentence)){
		int counter = sentence.length();
		for (int i = 0; i < sentence.length(); i++){
			if (sentence[i] == '.' || sentence[i] == '!' || sentence[i] == '?'){
				processv();
				v.clear();
				if (i != sentence.length()-1 && sentence[i + 1] == '"'){
					counter = i + 2;
					break;
				} else {
					counter = i + 1;
				}
			} 
		}
		string cur = "";
		for (int i = 0; i < counter; i++){
			cur = cur + sentence[i];
		}
		v.push_back(cur);
		for (int i = 0; i < counter; i++){
			sentence.erase(sentence.begin());
		}
	}
}

int main(){
	
	printf("Welcome to TrainerBot A.\n");
	printf("Make sure to save your previous bridges if you don't want them to be erased!\n");
	printf("Do you want to start training? (y/n):  ");
	scanf(" %c", &ct);
	if (ct != 'y'){
		printf("\n");
		printf("Training ABORTED\n");
		return 0;
	}
	
	printf("\n");
	printf("Training PROCEEDS\n");
	
	
	
	DIR* dir;
	struct dirent *ent;
	printf("Enter the file containing training sets: ");
	scanf("%s", dir_name);
	printf("\n");
	if ((dir = opendir (dir_name)) != NULL) {
	    /* print all the files and directories within directory */
	    while ((ent = readdir (dir)) != NULL) {
	        printf ("%s\n", ent->d_name);
	        if (strlen(ent->d_name) <= 2) continue;
	        FILE * fp;
			char filename[50];	
			filename[0] = '\0';        
	        strcat(filename, dir_name);
	        filename[strlen(dir_name)] = '/';
	        strcat(filename, ent->d_name);
	        printf("%s\n", filename);
	        fp = fopen(filename, "r");
	        printf("YES\n");
	        char line[100000];
		    while (fgets(line, sizeof(line), fp)){
		    	string cppstring = "";
		    	for (int i = 0; i < strlen(line); i++){
		    		cppstring = cppstring + line[i];
		    	}
		    	decompose(cppstring);
		    	//printf("%s", line);
		    }
		    
	        fclose(fp);
	    }
	    closedir (dir);
	} else {
	    /* could not open directory */
	    printf("Cannot open directory\n");
	    perror ("");
	    return EXIT_FAILURE;
	}
	
	printf("\n");
	printf("Enter file name to save bridges: ");
	scanf("%s", &cc);
	FILE * pFile;
	pFile = fopen(cc, "w");
	for (int i = 0; i < counter; i++){
		for (set<pi>::iterator it = bridge[i].begin(); it != bridge[i].end(); it++){
			fprintf(pFile, "%s %s %d", mmis[i].c_str(), mmis[it -> first].c_str(), it -> second);
		}
	}
	
	
	fclose(pFile);
}
