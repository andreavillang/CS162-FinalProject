#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct process{
	vector<int> holdResources;
	vector<int> needResources;
	bool processCompleted = false;
	bool processCanGoFirst = false;
};

//Deadlock prevention method of choice
//idk what it should return tbh ill set it to void for now
void deadlockMethod(){
    cout << "fuck this" << endl;
}

bool processCanGetResources(process procs, int numResources, int totalResAvailable, int arrResAvailable[]){
	bool processWillGo = true;
	for(int i = 0; i < numResources; i++){
		if(procs.needResources.at(i) > arrResAvailable[i]){
			processWillGo = false;
			break;
		}
	}
	return processWillGo;
}

//Returns total resources needed by a process
int totalResourcesNeeded(process procs, int numResources){
	int totalResNeeded = 0;
	for(int i = 0; i < numResources; i++){
		totalResNeeded += procs.needResources.at(i);
	}
	return totalResNeeded;
}

//Returns total held needed by a process
//idk if this one will actually be needed but lets keep it here for now
int totalResourcesHeld(process procs, int numResources){
	int totalResourcesHeld = 0;
	for(int i = 0; i < numResources; i++){
		totalResourcesHeld += procs.holdResources.at(i);
	}
	return totalResourcesHeld;
}

int totalResourcesAvailable(int arrResAvailable[], int numResources){
	int totalResAvailable = 0;
	for(int i = 0; i < numResources; i++){
		totalResAvailable += arrResAvailable[i];
	}
	return totalResAvailable;
}

/*void processCanGoFirstCheck(process[] procs, int procsSize, int totalResAvailable, int totalResNeeded){
	for(int i = 0; i < procsSize; i++){
		totalResNeeded = totalResourcesNeeded(procs[i], numResources);
		if(totalResNeeded <= totalResAvailable){
			procs[i].processCanGoFirst = true;
		}
	}
}*/

//Arithmethic part to find out if deadlock or not
bool orderOfProcess(process procs[], int totalResAvailable, int numProcess, int numResources, int arrResAvailable[]){
	int totalResNeeded, totalResHeld, originalResAvailable;
	int counter = 0;
	int order[numProcess];
	bool allDone = false;
	
	totalResAvailable = totalResourcesAvailable(arrResAvailable, numResources);
	originalResAvailable = totalResAvailable; 

	totalResNeeded = totalResourcesNeeded(procs[counter], numResources);
	
	//Will determine which of the processes have a totalResNeeded lower than the totalResAvailable
	//processCanGoFirstCheck(procs, procsSize, totalResAvailable, totalResNeeded);

	while(!allDone){
		if(processCanGetResources(procs[counter], numResources, totalResAvailable, arrResAvailable) && !procs[counter].processCompleted){ //if true then process can get res
			order[counter] = counter + 1;
			//update available resource count as if the process has released its resources
			for(int i = 0; i < numResources; i++){
				arrResAvailable[i] += procs[counter].holdResources.at(i);
			}
			totalResAvailable = totalResourcesAvailable(arrResAvailable, numResources);
			//set process completed to true so it doesn't repeat
			procs[counter].processCompleted = true;
		}
		
		//resets the counter
		if(counter == numProcess - 1){
			counter = 0;
		}
		
		//checks if all processes are done
		bool allDoneChecker = true;
		for(int i = 0; i < numProcess; i++){
			if(!procs[i].processCompleted){
				allDoneChecker = false;
				break;
			}
		}
		if(allDoneChecker){
			allDone = true;
		}
		
		//update counter
		counter++;
	}
    
    if(allDone){
        cout << "Order of processes: ";
		for(int i = 0; i < numProcess; i++){
			cout << order[i] << " ";
		}
		cout << endl;
    }
    
    return allDone;
}

int main(){
	int numTestCase, numProcess, numResources, totalResAvailable;
	
	cin >> numTestCase;
	
	//Number of test cases
	for(int h = 0; h < numTestCase; h++){
		cin >> numProcess >> numResources;
		int arrResAvailable[numResources];
		process procs[numProcess];
		
		//This is for the Available Resources
		for(int i = 0; i < numResources; i++){
			int num;
			cin >> num;
			arrResAvailable[i] = 0;
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
		
		totalResAvailable = totalResourcesAvailable(arrResAvailable, numResources);
    	cout << orderOfProcess(procs, totalResAvailable, numProcess, numResources, arrResAvailable);
	}
	
	
	
	return 0;
	
}