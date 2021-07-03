#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Human {
public:
    Human(const string& name, const string& prof)
        : Name(name), Proffession(prof) {}

    virtual void Walk(const string& destination) const {
        cout << Proffession << ": " << Name << " walks to: " << destination << endl;
    }

    string GetName() const { return Name; }
    string GetProffession() const { return Proffession; }

protected:
    const string Name;
    const string Proffession;
};


class Student : public Human {
public:

    Student(const string& name, string favouriteSong)
        : Human(name, "Student"), FavouriteSong(favouriteSong) {}

    void Learn() const {
        cout << "Student: " << Name << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        Human::Walk(destination);
        SingSong();
    }

    void SingSong() const {
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

private:
    const string FavouriteSong;
};


class Teacher : public Human {
public:

    Teacher(const string& name, const string& subject)
        :Human(name, "Teacher"), Subject(subject) {}

    void Teach() const {
        cout << "Teacher: " << Name << " teaches: " << Subject << endl;
    }


private:
    const string Subject;
};


class Policeman : public Human {

public:
    Policeman(const string& name)
        : Human(name, "Policeman") {}


    void Check(const Human& h) const {
        cout << "Policeman: " << Name << " checks " << h.GetProffession()
            << ". " << h.GetProffession() << "'s name is: " << h.GetName() << endl;
    }

};

void VisitPlaces(const Human& h, const vector<string>& places) {
    for (const auto& p : places) {
        h.Walk(p);
    }
}




int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, { "Moscow", "London" });
    p.Check(s);
    VisitPlaces(s, { "Moscow", "London" });
    return 0;
}


/*Correct output:

Teacher: Jim walks to: Moscow
Teacher: Jim walks to: London
Policeman: Bob checks Student. Student's name is: Ann
Student: Ann walks to: Moscow
Student: Ann sings a song: We will rock you
Student: Ann walks to: London
Student: Ann sings a song: We will rock you
*/

/*My output:

Teacher: Jim walks to: Moscow
Teacher: Jim walks to: London
Policeman: Bob checks Student. Student's name is: Ann
Student: Ann walks to: Moscow
Student: Ann sings a song: We will rock you
Student: Ann walks to: London
Student: Ann sings a song: We will rock you

*/