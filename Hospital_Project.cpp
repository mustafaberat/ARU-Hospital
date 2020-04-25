#include <iostream>
#include <conio.h>
#include <unistd.h>//sleep function
#include <string.h>
using namespace std;


struct Person{
	//Data Members
	string name; //Person name
	string surname; //Person surname
	int TC; //Person ID number
	int birthDate; //Person BirtDate - Only year
	//Pointers
	Person *next; //Next person address
	Person *prev; //Previous person address
};

class Hospital{
	private:
		Person *head; //First person
		Person *tail; //Last person
		int count_patient; //How many people patient in queue
		int count_healed; //How many people healed
		int early_leaved; //Person leave when he were queue
		
	public:
		Hospital(){ //Default
			head = NULL;
			tail = NULL;
			count_patient= 0; //How many people patient in queue
			count_healed = 0; //How many people healed
			early_leaved = 0;
		}
		//Member functions
		Person* CreatePerson(); //Return address of person Node
		bool IsEmpty(); //Queue is empty or not
		void InsertFirst(); //Adding person the beginning of queue
		void InsertLast(); //Adding person the last of queue
		void DisplayAll(); //Showing all people - For doctors
		void RemoveLast(); // Coming and leaving in queue
		void RemoveFirst(); // Doctor take a person in queue
		void FindPerson(); //Doctor research someone or person does
		void CountsBrief(); // How many patient
		void OrderByDate(); //Looking at the birthdate then bigger is the one - Showing only
};

Person* Hospital::CreatePerson(){
	Person *newNode = new Person; //That one is object
	cout << "Enter the name: ";
	string set_name;
	cin>>set_name;
	newNode->name = set_name;
	cout << "Enter the surname: ";
	string set_surname;
	cin>>set_surname;
	newNode->surname = set_surname;
	cout << "Enter the TC identity number: ";
	int set_tc;
	cin>>set_tc;
	newNode->TC = set_tc;
	cout << "Enter the birthdate: ";
	int set_date;
	cin>>set_date;
	newNode->birthDate = set_date;
	
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

bool Hospital::IsEmpty(){
	return head == NULL;
}

void Hospital::InsertLast(){
	if(!IsEmpty()) //We have more than one person in queueu
	{
		Person *temp = CreatePerson();
		if((2019 - temp->birthDate) > 65){
			cout << "People older than 65 has priority in queue" <<endl;
			//InsertFirst
			temp->next = head; //Converting first one to head
			temp->prev = NULL; //because temp is first
			head->prev = temp; //Converting first to head-prev
			head = temp; //Head is temp from now on
			cout << "Successfully added first." << endl;
		}
		else{ //Not bigger than 65
			tail->next = temp; //Converting next to next one = temp
			temp->prev = tail; //Converting prev to previous one
			temp->next = NULL; //Because temp is last now
			tail = temp; //Tail in the last Node from now on
			cout << "Successfully added last." << endl;
		}
	}	
	else //No person in queue
	{
		tail = head = CreatePerson();
	}
	count_patient++; //Number of patient people in queue
	sleep(3);
}

void Hospital::InsertFirst(){
    
	if (IsEmpty()) //If empty - Creating only one node
	{
		tail = head = CreatePerson(); //tail head is the same and creating one person
	}
	else // If some nodes in queue
	{
		Person* temp = CreatePerson(); 		
		temp->next = head; //Converting first one to head
		temp->prev = NULL; //because temp is first
		head->prev = temp; //Converting first to head-prev
		head = temp; //Head is temp from now on
	}
        count_patient++; //Number of patient people in queue
		cout<<"Successfully added first. "<<endl;
		sleep(2);
}

void Hospital::DisplayAll(){
	if(!IsEmpty()){
		Person *temp = head;
		while(temp != NULL){ //Searching all
			cout << "Name: " << temp->name <<endl;
			cout << "Surname: " << temp->surname <<endl;
			cout << "TC: " << temp->TC <<endl;
			cout << "BirthDate: " << temp->birthDate <<endl;
			cout << "--------------" <<endl;
			temp = temp->next;
		}
	}
	else{ //Empty
		cout << "The Queue is empty!" <<endl;
	}
		sleep(3);
}

void Hospital::RemoveFirst(){
	if(IsEmpty()) // empty queue
	{
		cout << "The Queue is empty!" << endl;
		sleep(2);
	}
	else //We have some people in queue
	{
		if(head == tail){ //If onyl one person
			cout << head->name << " " << head->surname << " is leaved!" <<endl; //Who is gone showing
			sleep(2);
			head = tail = NULL; //Deleting one person in queue	
		}
		else //More than one person in queue
		{	
			cout << head->name << " " << head->surname << " is leaved!" <<endl; //Who is gone showing
			sleep(2);
			Person *temp = head; // Head also temp now
			head = head->next ; //Head is one front Node
			head->prev = NULL; //Making sure
			delete temp;
		}
	}
		count_patient--; // Person in gone!
		count_healed ++; //Person healed by doctor
}

void Hospital::RemoveLast(){
	if(IsEmpty()) // empty queue
	{
		cout << "The Queue is empty!" << endl;
		sleep(2);
	}
	else //We have some people in queue
	{
		if(head == tail){ //If onyl one person
			cout << head->name << " " << head->surname << " is leaved!" <<endl; //Who is gone showing
			sleep(2);
			head = tail = NULL; //Deleting one person in queue	
		}
		else //More than one person in queue
		{	
			cout << head->name << " " << head->surname << " is leaved!" <<endl; //Who is gone showing
			sleep(2);
			Person *temp = tail; // Tail also temp now
			tail = tail->prev ; //Tail is one back
			tail->next = NULL; // Making sure
			delete temp;
		}
	}
		count_patient--; // Person in gone!
		early_leaved ++; //Person leaved counter +1
}

void Hospital::FindPerson(){
	if(IsEmpty()){ //Empty queue
		cout << "The Queue is empty!" <<endl;
	}
	else{ //If someone in queue
		cout << "Enter the TC: ";
		int lookTc;
		cin>>lookTc;
		
		Person *temp = head;
		while(temp != NULL){ //Looking at all
			if(temp->TC == lookTc){
				cout << temp->name << " " << temp->surname << " in the queue!" <<endl; 
				cout << "TC: " << temp->TC << endl;
				sleep (2);
				break; //Dont look others
			}
			//ELSE PROBLEM: WRITING NOT NOT NOT FOR ALL PEOPLE THAT NOT THE SAME TC
			temp = temp->next; //Going next
		}
	}
}

void Hospital::CountsBrief(){
	cout << "How many patient in queue: " << count_patient <<endl;
	cout << "How many patient healed: " << count_healed <<endl;
	cout << "How many people leaved: " << early_leaved <<endl;
	sleep(2);
}

void Hospital::OrderByDate(){
	if(IsEmpty()){ //if empty queue
		cout << "The queue is empty!" <<endl;
		sleep(2);
	}
	
	else { //If someone in queue
	//Bubble Sorting
		for(int i=0 ; i< count_patient-1 ; i++){ //iteration
			Person *temp = head; //Temp is head AGAIN IN ITERATION!
			while(temp->next != NULL){ //searching all elemets
				if(temp->birthDate > temp->next->birthDate){
					int spare = temp->birthDate; //Swapping
					temp->birthDate = temp->next->birthDate;
					temp->next->birthDate = spare;
				}
				temp = temp->next;
			}
		} //End of for
		cout << "The new order by birthdate: " <<endl;
		DisplayAll();	
	} //End of else
}

void HospitalFunctions(){
	Hospital H1; //Creating Object
	int decision;
	
	do{
		system("cls"); //Delete screen
		cout << "1- Insert First" <<endl;
		cout << "2- Insert Last" <<endl;
		cout << "3- Display All" <<endl;
		cout << "4- Remove First" <<endl;
		cout << "5- Remove Last" <<endl;
		cout << "6- Find Person" <<endl;
		cout << "7- Brief of Day" <<endl;
		cout << "8- Short People By Age" <<endl;
		cout << "9- Exit" <<endl;
		cin >> decision;
		
		switch(decision){
			case 1:
				H1.InsertFirst();
				break;
			case 2:
				H1.InsertLast();
				break;
			case 3:
				H1.DisplayAll();
				break;
			case 4:
				H1.RemoveFirst();
				break;
			case 5:
				H1.RemoveLast();
				break;				
			case 6:
				H1.FindPerson();
				break;
			case 7:
				H1.CountsBrief();
				break;
			case 8:
				H1.OrderByDate();
				break;
			default:
				cout << "Not able option!" <<endl;
				sleep(2);
				break;
		}
	}while(decision != 9); // End of do
	
}

void ShowOptions(){
	//cout << "1- Hospital" << endl; 2-school..
	int decision = 1; //Default
	//cin >> decision;
	
	switch(decision){
		case 1:
			HospitalFunctions();
			break;
		//case 2:..
	}
}

int main(){
	ShowOptions();
	getch();
}
