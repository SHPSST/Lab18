#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<iomanip>

using namespace std;

struct student{
    string name;
    int id;
    char gender;
    float gpa;
};

struct course{
    string name;
    int id;
    vector<string> lecture_list;
    vector<student*> student_list;
};

student * findstudent(vector<student>& allstudents, int key) { // Change the type of 'allstudents' parameter to reference
    for(unsigned int i = 0; i < allstudents.size(); i++){
        if(allstudents[i].id  == key) return &allstudents[i];
    }
    return nullptr;
} 

void printreport(vector<course> allcourses){
    for(unsigned int i = 0; i < allcourses.size(); i++){
        cout << "-----------------------------------------------------------------------------\n";
        cout << left << setw(20) << "Course:" << allcourses[i].name << " ("<< allcourses[i].id << ")\n\n";
        cout << left << setw(20) << "Lecturers:";
        for(unsigned int j = 0; j < allcourses[i].lecture_list.size(); j++){
            if(j != 0) cout << ", ";
            cout << allcourses[i].lecture_list[j];
        }
        cout << "\n\n";
        cout << left << setw(20) << "Students:";
        for(unsigned int j = 0; j < allcourses[i].student_list.size(); j++){
            if(j != 0) cout << left << setw(20) << " ";
            cout << left << setw(20) << allcourses[i].student_list[j]->name;
            cout << left << setw(10) << allcourses[i].student_list[j]->id;
            cout << left << setw(3) << allcourses[i].student_list[j]->gender;
            cout << left << setw(5) << setprecision(2) << fixed << allcourses[i].student_list[j]->gpa << "\n";
        } 
    }
    cout << "-----------------------------------------------------------------------------\n";
}

int main(){
    ifstream student_file("students.txt");
    ifstream course_file("courses.txt");
    vector<student> allstudents;
    vector<course> allcourses;
    
    string textline;
    
    while(getline(student_file, textline)){
        student s; 
        char B[100];
        sscanf(textline.c_str(), "%[^,],%d,%c,%f", B, &s.id, &s.gender, &s.gpa);
        s.name=B;
        allstudents.push_back(s);        
    }
    
    int state = 1;
    while(getline(course_file, textline)){
        if(state == 1){
            course c;
            int loc = textline.find_first_of('(');
            c.name = textline.substr(0, loc-1);
            c.id = atoi(textline.substr(loc+1, 5).c_str());
            getline(course_file, textline);
            allcourses.push_back(c);
            state = 2;            
        }else if(state == 2){
            if(textline == "> Students"){
                state = 3;
            }else{
            
                // Append (push_back) textline to lecture_list[] of the recently added course in allcourses[];
                allcourses[allcourses.size() - 1].lecture_list.push_back(textline);
            }            
        }else{
            if(textline == "---------------------------------------"){
                state = 1;
            }else{
                student *p = findstudent(allstudents, atoi(textline.c_str()));
                
                // Append (push_back) p to student_list of the recently added course in allcourses[];
                allcourses[allcourses.size() - 1].student_list.push_back(p);
            }
        }
    }
    printreport(allcourses);
}
