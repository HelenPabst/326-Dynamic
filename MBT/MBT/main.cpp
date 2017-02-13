//Helen Pabst
//CECS 326 Sec 5
//Assignment 1
//02-14-17
#include <iostream> 
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <queue>        // std::queue
using namespace std;

int main()
{
	/* initialize random seed: */
	srand(time(NULL));

	//create memory block table (MBT) data structure
	//integer and boolean array

	struct mbt
	{
		int space = 128;//keeps track of how many spaces are open in the struct
		bool arr[128] = { true };
	};

	mbt table;

	//PCB
	struct pcb
	{
		int pid[10];
		int pageTable;
	};

	pcb PCB;

	int ptrPT;

	//ready queue
	queue<pcb> ready;

	//set all elements equal to "true" to represent empty space
	for (int i = 0; i < 128; i++)
	{
		table.arr[i] = true;
	}

	//set the first 10 equal to "false" to reserve them for the operating system
	for (int i = 0; i < 10; i++)
	{
		table.arr[i] = false;
	}

	table.space -= 10;//should represent amount of mem left in the table

	//pointer for bool arr
	bool * ptr;
	ptr = table.arr; //equals beginning of arr
	*(ptr + (128 - table.space));//equals the next avail space
	cout << *(ptr + (128 - table.space)) << endl;

	//check amount of space left
	cout << "Space left: "<< table.space<<"\n";

	//intialize PID so user can obtain unique one within menu
	int PIDarr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int locPID = 0;

	int pageTable[118];
	int ptCounter=0;

	//create menu
	bool menu = true;
	while (menu)
	{
		cout << "Please pick an option: \n1. Initiate a process\n2. Print all processes in ready queue\n3. Terminate process with a specific PID\n4. Exit\n";
		int response;
		cin >> response;

		//1. Initiate a process
		if (response == 1)
		{
			//allocate dynamic memory for a process control block
			/*queue<int> PCB;	*/		

			//obtain a unique process ID(PID) and save it in the PCB
			int PID = PIDarr[locPID]; //get PID from PID array
			PCB.pid[locPID] = PID; //store PID in PCB (struct)
			locPID++; //increment PID array

			/*PCB.push(PID);
			cout << "PID: " << PCB.front()<<"\n";*/

			//generate a random number for required memory blocks
			int num = rand() % 100 + 1; //num in the range 1 to 100

			//search MBT for free blocks, if insufficient free blocks are available then display error message and return to menu
			cout << "Blocks you wish to allocate: " << num << "\n";
			cout << "Blocks left: " << table.space << "\n";

			if (num > table.space)
			{
				cout << "There is not enough space left. Sorry.\n";
			}

			else
			{
				//allocate memory blocks (only a simulation by designating required number of blocks in MBT as "allocated")
				for (int k = (128-table.space); k < (128-table.space)+num; k++)
				{
					table.arr[k] = false;
				}

				//allocate dynamic memory for a page table and store allocated blocks in it
				for (int j=0; j < num; j++)
				{
					pageTable[ptCounter] = ptCounter+10;
					ptCounter++;
				}

				//save the pointer to page table in PCB
				ptrPT = (128 - table.space) + num;
				PCB.pageTable = ptrPT;

				//Insert PCB in ready queue
				ready.push(PCB);

				//output page table and MBT to enable varification, and return to menu
				cout << "Page Table:" << endl;
				for (int l = 0; l < 118; l++)
				{
					cout << pageTable[l] << endl;
				}

				cout << "MBT:" << endl;
				table.space -= num;
				cout << "Blocks left after allocation: " << table.space<<"\n";
			}			
		}

		//2. Print all processes in ready queue
		if (response == 2)
		{
			//output PID for each process in ready queue and return to menu (print the queue)
			cout << ready.front().pid[1];
		}

		//3. Terminate process with a specific PID
		if (response == 3)
		{
			//search through ready queue for the given PID, output error message if not found
			//Deallocate memory blocks allocated for the process (only a simulation by designating those assigned blocks to this process as "free")
			//delete page table for the process
			//delete PCB for the process and return to menu
		}

		//4. Exit
		if (response == 4)
		{
			cout << "Goodbye\n";
			menu = false;
		}
	}

	return 0;
}