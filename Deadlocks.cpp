#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct process{
	vector<int> holdResources;
	vector<int> needResources;
	bool processCompleted = false;
	bool victim = false;
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

//Arithmethic part to find out if deadlock or not
int orderOfProcess(process procs[], int totalResAvailable, int numProcess, int numResources, int arrResAvailable[]){
	int totalResNeeded, totalResHeld;
	int counter = 0;
	int roundCounter = 0;
	int allDone = 0;

	totalResNeeded = totalResourcesNeeded(procs[counter], numResources);

	cout << "The processes completed so far: ";

	while(allDone == 0){

		//resets the counter
		if(counter == numProcess){
			roundCounter++;
			counter = 0;
		}
		
		if(processCanGetResources(procs[counter], numResources, totalResAvailable, arrResAvailable) && !procs[counter].processCompleted && !procs[counter].victim){ //if true then process can get res
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
			cout << endl;
			break;
		}
	}
    
    return allDone;
}

//Deadlock Recovery
void deadlockMethod(process procs[], int totalResAvailable, int numProcess, int numResources, int arrResAvailable[]){
	int totalResNeeded, totalResHeld, tempResHeld, victimNumber;
	string victim = "NA";
	
	//Make a temporary array to store the highest resources available
	int temp[numResources];
	for(int h = 0; h < numResources; h++){
		temp[h] = 0;
	}
	tempResHeld = totalResourcesAvailable(temp,numResources);
	
	//For loop to know the process with the highest resources available and put it into temp[]
	for(int i = 0; i < numProcess; i++){
		if(!procs[i].processCompleted){
			totalResHeld = totalResourcesHeld(procs[i], numResources);
			if(totalResHeld > tempResHeld){
				for(int j = 0; j < numResources; j++){
					temp[j] = procs[i].holdResources.at(j);
					procs[i].victim = true;
					victimNumber = i;
					victim = to_string(i+1);
				}
				tempResHeld = totalResourcesAvailable(temp,numResources);
			}
		}
	}
	
	//Add the released resources to the available
	for(int k = 0; k < numResources; k++){
		arrResAvailable[k] += temp[k];
	}
	
	//Since we released the resoures the held resources of that process is 0
	for(int k = 0; k < numResources; k++){
		procs[victimNumber].holdResources.at(k) = 0;
	}
	totalResAvailable = totalResourcesAvailable(arrResAvailable, numResources);
	
	cout << "Process " << victim << " resources are released." << endl;
}

int main(){
	int numTestCase, numProcess, numResources, totalResAvailable, intBool;
	bool deadlockHappened = false;
	
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
		}
		
		//Puts what the processes needs
		for(int l = 0; l < numProcess; l++){
			for(int m = 0; m < numResources; m++){
				int num;
				cin >> num;
				procs[l].needResources.push_back(num);
			}
		}
		
		totalResAvailable = totalResourcesAvailable(arrResAvailable, numResources);
		intBool = orderOfProcess(procs, totalResAvailable, numProcess, numResources, arrResAvailable);
		while(intBool != 1){
			if(deadlockHappened == false){
				cout << "Deadlock Recovery in Progress..." << endl;
			}
    		deadlockMethod(procs, totalResAvailable, numProcess, numResources, arrResAvailable);
			intBool = orderOfProcess(procs, totalResAvailable, numProcess, numResources, arrResAvailable);
			deadlockHappened = true;
			for(int i = 0; i < numProcess; i++){
				procs[i].victim = false;
			}
		}
    	if(intBool == 1 && deadlockHappened == false){
    		cout << "No Deadlock Recovery Needed." << endl;
    	}
		else{
			cout << "Deadlock Resolved!" << endl;
		}
	}
	
	
	
	return 0;
	
}