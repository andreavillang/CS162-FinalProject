#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct process{
	vector<int> holdResources;
	vector<int> needResources;
};

int main(){
	int numTestCase, numProcess, numResources;
	
	cin >> numTestCase;
	
	//Number of test cases
	for(int h = 0; h < numTestCase; h++){
		cin >> numProcess >> numResources;
		int avail[numResources];
		process procs[numProcess];
		
		//This is for the Available Resources
		for(int i = 0; i < numResources; i++){
			int num;
			cin >> num;
			avail[i] = 0;
		}
		
		//Puts what the processes is holding
		for(int j = 0; j < numProcess; j++){
			for(int k = 0; k < numResources; k++){
				int num;
				cin >> num;
				procs[j].holdResources.push_back(num);
			}
			/* THIS IS JUST FOR TESTING WHAT IS INSIDE THE VECTOR!!!
			for(int l = 0; l < numResources; l++){
				cout << procs[j].holdResources.front() << endl;
				procs[j].holdResources.erase(procs[j].holdResources.begin());
			}
			*/
		}
		
		//Puts what the processes needs
		for(int l = 0; l < numProcess; l++){
			for(int m = 0; m < numResources; m++){
				int num;
				cin >> num;
				procs[l].needResources.push_back(num);
			}
			/* THIS IS JUST FOR TESTING WHAT IS INSIDE THE VECTOR!!!
			for(int l = 0; l < numResources; l++){
				cout << procs[j].needResources.front() << endl;
				procs[j].needResources.erase(procs[j].needResources.begin());
			}
			*/
		}
	}
}