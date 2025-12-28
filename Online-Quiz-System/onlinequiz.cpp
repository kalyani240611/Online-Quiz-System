//Author: Dungala Kalyani
//Discription: A console-based Online-Quiz-System using C++ and OOP
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
using namespace std;

class Question {
private:
    string question;
    map<char, string> options;
    char correctOption;

public:
    // Set question and options
    void setQuestion() {
        cout << "Enter the question: ";
        cin.ignore();
        getline(cin, question);

        char optionChar = 'A';
        for (int i = 0; i < 4; i++) {
            string opt;
            cout << "Enter option " << optionChar << ": ";
            getline(cin, opt);
            options[optionChar++] = opt;
        }

        cout << "Enter correct option (A/B/C/D): ";
        cin >> correctOption;
        correctOption = toupper(correctOption);
    }

    // Display question and options
    void displayQuestion() const {
        cout << "\n" << question << endl;
        for (auto &opt : options) {
            cout << opt.first << ". " << opt.second << endl;
        }
    }

    // Check answer
    bool checkAnswer(char answer) const {
        return toupper(answer) == correctOption;
    }

    // Save question to file
    void saveToFile(ofstream &outFile) const {
        outFile << question << endl;
        for (auto &opt : options) {
            outFile << opt.first << ":" << opt.second << endl;
        }
        outFile << correctOption << endl;
    }

    // Load question from file
    void loadFromFile(ifstream &inFile) {
        getline(inFile, question);
        options.clear();
        for (int i = 0; i < 4; i++) {
            string line;
            getline(inFile, line);
            if(line.size() > 2) options[line[0]] = line.substr(2);
        }
        inFile >> correctOption;
        inFile.ignore(); // Ignore newline after reading correctOption
    }
};

class Quiz {
private:
    vector<Question> questions;
    int score = 0;

public:
    // Add new question
    void addQuestion() {
        Question q;
        q.setQuestion();
        questions.push_back(q);
        cout << "Question added successfully!\n";
    }

    // Start the quiz
    void startQuiz() {
        if (questions.empty()) {
            cout << "No questions available. Please load or add questions first.\n";
            return;
        }

        score = 0;
        char answer;
        for (auto &q : questions) {
            q.displayQuestion();
            cout << "Your answer: ";
            cin >> answer;
            if (q.checkAnswer(answer)) {
                cout << "Correct!\n";
                score++;
            } else {
                cout << "Wrong!\n";
            }
        }
        cout << "\nQuiz finished. Your score: " << score << "/" << questions.size() << endl;
    }

    // Save all questions to file
    void saveQuestionsToFile() {
        ofstream outFile("questions.txt");
        if (!outFile) {
            cout << "Error opening file to save questions!\n";
            return;
        }
        for (auto &q : questions) {
            q.saveToFile(outFile);
        }
        outFile.close();
        cout << "Questions saved to file successfully.\n";
    }

    // Load questions from file
    void loadQuestionsFromFile() {
        ifstream inFile("questions.txt");
        if (!inFile) {
            cout << "No saved questions found!\n";
            return;
        }
        questions.clear();
        while (inFile.peek() != EOF) {
            Question q;
            q.loadFromFile(inFile);
            questions.push_back(q);
        }
        inFile.close();
        cout << "Questions loaded from file successfully.\n";
    }
};

int main() {
    Quiz quiz;
    int choice;

    do {
        cout << "\n=== Online Quiz/Test System ===\n";
        cout << "1. Add Question\n";
        cout << "2. Take Quiz\n";
        cout << "3. Load Questions from File\n";
        cout << "4. Save Questions to File\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: quiz.addQuestion(); break;
            case 2: quiz.startQuiz(); break;
            case 3: quiz.loadQuestionsFromFile(); break;
            case 4: quiz.saveQuestionsToFile(); break;
            case 5: cout << "Exiting... Thank you!\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while(choice != 5);

    return 0;
}



