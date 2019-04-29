#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct process{
	vector<int> holdResources;
	vector<int> needResources;
	bool processCompleted = false;
};

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

//Deadlock avoidance
void deadlockMethod(process procs[], int totalResAvailable, int numProcess, int numResources, int arrResAvailable[]){
	int totalResNeeded, totalResHeld;

	//get process with max held resources to release all
	//call the orderOfProcess function again
	for(int i = 0; i < numProcess; i++){

	}
	//totalResHeld = totalResourcesHeld(procs[], numResources);

    cout << "Deadlock problem solved!" << endl;
}

//Arithmethic part to find out if deadlock or not
int orderOfProcess(process procs[], int totalResAvailable, int numProcess, int numResources, int arrResAvailable[]){
	int totalResNeeded, totalResHeld;
	int counter = 0;
	int roundCounter = 0;
	int allDone = 0;

	totalResNeeded = totalResourcesNeeded(procs[counter], numResources);
	totalResHeld = totalResourcesHeld(procs[counter], numResources);

	cout << "The order is: ";

	while(allDone == 0){

		//resets the counter
		if(counter == numProcess){
			roundCounter++;
			counter = 0;
		}
		
		if(processCanGetResources(procs[counter], numResources, totalResAvailable, arrResAvailable) && !procs[counter].processCompleted){ //if true then process can get res
			cout << counter + 1 << " ";
			//update available resource count as if the process has released its resources
			for(int i = 0; i < numResources; i++){
				arrResAvailable[i] += procs[counter].holdResources.at(i);
			}
			totalResAvailable = totalResourcesAvailable(arrResAvailable, numResources);
			//set process completed to true so it doesn't repeat
			procs[counter].processCompleted = true;
		}

		//update counter
		counter++;
		
		//checks if all processes are done
		allDone = 1;
		for(int i = 0; i < numProcess; i++){
			if(!procs[i].processCompleted){
				allDone = 0;
				break;
			}
		}
		if(allDone == 1){
			cout << endl;
		}

		if(roundCounter == numProcess - 1){
			allDone = 2;
			cout << "NA" << endl;
			break;
		}
	}
    
    return allDone;
}

int main(){
	int numTestCase, numProcess, numResources, totalResAvailable, intBool;
	
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
			arrResAvailable[i] = num;
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
		intBool = orderOfProcess(procs, totalResAvailable, numProcess, numResources, arrResAvailable);
    	if(intBool == 1){
    		cout << "No deadlock avoidance needed." << endl;
    	}
    	else{ //intBool == 2
    		cout << "Deadlock avoidance needed" << endl;
    		deadlockMethod();
    	}

	}
	
	
	
	return 0;
	
}