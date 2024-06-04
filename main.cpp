#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

fstream file, filevotes, filecans, ftemp;
string vname, vage, cname, cparty;
int vote, vid;


class Voting {
public:
	void addVoters();
	void addCandidates();
	void displayVoters();
	void displayCandidates();
	void voteNow();
	void viewResult();
	
};

void Voting::addVoters() {
	system("cls");
	cout << "ADD VOTER" << endl;
	cout << "Enter Voter's ID: ";
	cin >> vid;
	cout << "Enter Voter's Name: ";
	cin >> vname;
	cout << "Enter Voter's Age: ";
	cin >> vage;
	file.open("voters.txt", ios::out | ios::app);
	file << vid << " " << vname << " " << vage << endl; 
	file.close();
}


void Voting::addCandidates() {
	system("cls");
	cout << "ADD CANDIDATE" << endl;
	cout << "Enter Candidate's Name: ";
	cin >> cname;
	cout << "Enter Candidate's Party: ";
	cin >> cparty;
	file.open("candidates.txt", ios::out | ios::app);
	filecans.open("votes.txt", ios::out | ios::app);
	file << cname << " " << cparty << endl; 
	filecans << cname << " "  << cparty << " " << vote << endl; 
	file.close();
	filecans.close();
}

void Voting::displayVoters() {
	system("cls");
	cout << "All VOTERS" << endl;
	file.open("voters.txt", ios::in);
	if (!file)
	{
		cout << "Database Failed To Open!" << endl;
	} else {
		cout << "Voter's ID\t\tVoter's Name\t\tVoter's Age" << endl;
		file >> vid >> vname >> vage; 
		while(!file.eof()) {
			cout << vid << "\t\t\t" << vname << "\t\t\t" << vage << endl; 
			file >> vid >> vname >> vage; 
		}
		system("pause");
		file.close();
	}
}

void Voting::displayCandidates() {
	system("cls");
	cout << "All CANDIDATES" << endl;
	file.open("candidates.txt", ios::in);
	if (!file)
	{
		cout << "Database Failed To Open!" << endl;
	} else {
		cout << "Candidate's Name\t\tCandidate's Party" << endl;
		file >> cname >> cparty; 
		while(!file.eof()) {
			cout << cname << "\t\t\t" << cparty << endl; 
			file >> cname >> cparty; 
		}
		system("pause");
		file.close();
	}
}


void Voting::voteNow() {
	int count(0), nbal, amt, vid2;
	string cparty2;
	system("cls");
	cout << "All CANDIDATES" << endl;
	filecans.open("candidates.txt", ios::in);
	filevotes.open("votes.txt", ios::in);
	file.open("voters.txt", ios::in);
	ftemp.open("temp.txt", ios::out | ios::app);
	if (!file) {
		cout << "Database Failed To Open!" << endl;
	} else {
		cout << "Enter Voter's ID: ";
		cin >> vid2;
		file >> vid >> vname >> vage; 
		while(!file.eof()) {
			if (vid == vid2) {
                //system("cls");
				cout << "Voter's Name: " << vname << endl;
				count = 1;
				cout << endl;
				cout << "Candidate's Name\t\tCandidate's Party" << endl;
				filecans >> cname >> cparty; 
				while(!filecans.eof()) {
					cout << cname << "\t\t\t" << cparty << endl; 
					filecans >> cname >> cparty; 
				}
				cout << "Enter Candidate's Party To Vote [IN UPPERCASE]: ";
				cin >> cparty2;
				filevotes >> cname >> cparty >> vote; 
				while(!filevotes.eof()) {
					if (cparty == cparty2) {
						int output = vote + 1;
						count = 1;
						ftemp << cname << " " << cparty2 << " " << output << endl; 
						cout << "Vote Casted" <<endl;
					} 
					else 
						ftemp << cname << " " << cparty << " " << vote << endl; 
						filevotes >> cname >> cparty >> vote; 
						count = 1;
					
				}
				if (count == 0) {
					cout << "No Record Found!" << endl;
				}
			}
			system("pause");
			filevotes.close();
			filecans.close();
			file.close();
			ftemp.close();
			remove("votes.txt");
			rename("temp.txt", "votes.txt");
				break; 
		} 
		if (count == 0) {
			cout << "No Record Found!" << endl;
		}


	}
}

void Voting::viewResult() {
	system("cls");
	cout << "All RESULTS" << endl;
	file.open("votes.txt", ios::in);
	if (!file)
	{
		cout << "Database Failed To Open!" << endl;
	} else {
		cout << "Candidate's Name\tCandidate's Party\tVotes" << endl;
		file >> cname >> cparty >> vote; 
		while(!file.eof()) {
			cout << cname << "\t\t\t" << cparty << "\t\t\t" << vote << endl; 
			file >> cname >> cparty >> vote; 
		}
		system("pause");
		file.close();
	}
}


Voting voting;


int main() {
	system("color f3");
	int xopt;
	char opt;
	cout << "WELCOME TO MY VOTING SYSTEM" << endl;
	cout << endl;
	while(1) {
		system("cls");
		cout << "MAIN MENU" << endl;
		cout << "1 = ADD VOTER" << endl;
		cout << "2 = VIEW VOTERS" << endl;
		cout << "3 = ADD CANDIDATE" << endl;
		cout << "4 = VIEW CANDIDATES" << endl;
		cout << "5 = VOTE NOW" << endl;
		cout << "6 = VIEW RESULT" << endl;
		cout << "Enter Option: ";
		cin >> xopt;
		if (xopt == 1) {
			do {
				voting.addVoters();
				cout << "" << endl;
				cout << "Add Another Voter [y/n]:";
				cin >> opt ;
			} while(opt == 'y');
		} else if (xopt == 2) {
			voting.displayVoters();
		} else if (xopt == 3) {
			do {
				voting.addCandidates();
				cout << "" << endl;
				cout << "Add Another Candidate [y/n]:";
				cin >> opt ;
			} while(opt == 'y');
		} else if (xopt == 4) {
			voting.displayCandidates();
		} else if (xopt == 5) {
			voting.voteNow();
		} else if (xopt == 6) {
			voting.viewResult();
		} 
	}
	return 0;
}