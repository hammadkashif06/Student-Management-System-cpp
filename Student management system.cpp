#include<iostream>
#include<string>
#include<iomanip> //to beautify the output for displaying the arranged data of students;
using namespace std;
// class
class student{
	string name;
	int rollNo;
	int noOfSubjects;
	float *marks;
	float percentage;
	string grade;
	public:
		student(){};
		student(int);
		~student();
		void setArrays();
		void getData(int, string*);
		void calculatePercentage();
		void calculateGrade();
		friend void arrangeData(student **secA, int);
		friend void showData(student **secA, int);
		friend void search(student **secA, string* subjects,string nameToSearch, int noOfStudents,int noOfSubjects);
};
// constructor for assiging size to the array of subjects and marks
student :: student(int n){
	noOfSubjects = n;
	setArrays();
}

// destructor
student :: ~student(){
	delete[] marks;
}

//assigning size to the array of marks
void student :: setArrays(){
	marks = new float[noOfSubjects];
}

//taking data from the user
void student :: getData(int studentNumber, string* subjects){
	cout<<"Enter the name of the student "<<studentNumber<<" : ";
	getline(cin, name);
	cout<<"Enter the roll number: ";
	cin>>rollNo;
	cin.ignore();
	for (int i = 0;i<noOfSubjects;i++){
		cout<<"Enter the marks of "<<subjects[i]<<" : ";
		cin>>marks[i];
		cin.ignore();
	}
}

//calculating percentage
void student :: calculatePercentage(){
	int totalMarks = noOfSubjects*100;
	float marksObtained = 0;
	for (int i = 0;i<noOfSubjects;i++){
		marksObtained += marks[i];
	}
	percentage = marksObtained / totalMarks * 100.0;
}

//calculating grade
void student :: calculateGrade(){
	if (percentage >= 80 && percentage <=100) grade = "A1";
	else if (percentage >= 70) grade = "A";
	else if (percentage >= 60) grade = "B";
	else if (percentage >= 50) grade = "C";
	else if (percentage >= 40) grade = "D";
	else grade = "F";
}

// arranging students according to their percentage
void arrangeData(student **secA, int noOfStudents){
	for (int i = 0;i<noOfStudents-1;i++){
		for (int j = i+1;j<noOfStudents;j++){
			if (secA[i]->percentage < secA[j]->percentage){
				student *temp = secA[i];
				secA[i] = secA[j];
				secA[j] = temp;
			}
		}
	}
}

// printing arranged data
void showData(student **secA, int noOfStudents){
	cout<<"The arranged order of the students is with their percentages is: "<<endl;
	cout<<left;
	cout<<setw(20)<<"Name"<<
		  setw(15)<<"Roll NO"<<
		  setw(15)<<"Percentage"<<
		  setw(15)<<"Grade"<<endl;
	for (int i = 0;i<noOfStudents;i++){
		cout<<setw(20)<<secA[i]->name<<
			  setw(15)<<secA[i]->rollNo<<
		      setw(15)<< fixed << setprecision(2) << secA[i]->percentage<<
		      setw(15)<<secA[i]->grade<<endl;
	}
}

//searching
void search(student **secA, string* subjects,string nameToSearch, int noOfStudents,int noOfSubjects){
    int matchCount = 0;
    // Count matching names
    for(int i = 0; i < noOfStudents; i++){
        if(secA[i]->name == nameToSearch){
            matchCount++;
        }
    }
    if(matchCount == 0){
        cout<<"We don't have student ("<<nameToSearch<<") in the class"<<endl;
        return;
    }
    // Only one student with that name
    if(matchCount == 1){
        for(int i = 0; i < noOfStudents; i++){
            if(secA[i]->name == nameToSearch){
                cout<<"Name: "<<secA[i]->name<<endl;
                cout<<"Roll No: "<<secA[i]->rollNo<<endl;
                cout<<"Percentage: "<<secA[i]->percentage<<endl;
                cout<<"Grade: "<<secA[i]->grade<<endl;

                cout<<"Subjects & Marks:"<<endl;
                for(int j = 0; j < noOfSubjects; j++){
                    cout<<subjects[j]<<" : "<<secA[i]->marks[j]<<endl;
                }
                return;
            }
        }
    }
    // Multiple students with same name
    cout<<"Multiple students named "<<nameToSearch<<endl;
    cout<<"Enter roll number: ";
    int rollNoToSearch;
    cin>>rollNoToSearch;
    for(int i = 0; i < noOfStudents; i++){
        if(secA[i]->rollNo == rollNoToSearch){
            cout<<"Name: "<<secA[i]->name<<endl;
            cout<<"Roll No: "<<secA[i]->rollNo<<endl;
            cout<<"Percentage: "<<secA[i]->percentage<<endl;
            cout<<"Grade: "<<secA[i]->grade<<endl;

            cout<<"Subjects & Marks:"<<endl;
            for(int j = 0; j < noOfSubjects; j++){
                cout<<subjects[j]<<" : "<<secA[i]->marks[j]<<endl;
            }
            return;
        }
    }
    cout<<"Roll number not found."<<endl;
}

int main (){
	// taking number of students and subjects
	int noOfStudents;
	int noOfSubjects;
	cout<<"Enter the number of students: ";
	cin>>noOfStudents;
	cout<<"Enter the number of subjects: ";
	cin>>noOfSubjects;
	cin.ignore();		// to ignore the new line after taking input
	
	// taking subjects from the user for the whole of the class
	string* subjects = new string[noOfSubjects];
	for (int i = 0;i<noOfSubjects;i++){
		cout<<"Enter subject "<<i+1<<" : ";
		getline(cin, subjects[i]);
	}
	// assigning memory to students array
	student** secA = new student*[noOfStudents];
	for (int i = 0; i < noOfStudents; i++){
    	secA[i] = new student(noOfSubjects); //using pointer to assign size to the array of the marks
	}
	// calling functions
	for (int i = 0;i<noOfStudents;i++){
		secA[i]->getData(i+1, subjects);
		secA[i]->calculatePercentage();
		secA[i]->calculateGrade();
	}
	arrangeData(secA, noOfStudents);
	cout<<endl;
	showData(secA, noOfStudents);
	//working for searching
	char searching;
	cout<<"Do you want to search a student [y/n]: ";
	cin>>searching;
	cin.ignore();
	string nameToSearch;
	if (searching == 'y' || searching == 'Y'){
		cout<<"Enter the name you want to search: ";
		getline(cin, nameToSearch);
		cout<<endl;
		search(secA, subjects, nameToSearch, noOfStudents, noOfSubjects);
	}
	// clearing memory
	for (int i = 0; i < noOfStudents; i++){
    	delete secA[i];
	}
	delete[] subjects;
	delete[] secA;
	return 0;
}