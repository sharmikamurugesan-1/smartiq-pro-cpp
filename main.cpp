#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
using namespace std;

// ---------------- Question Class ----------------
class Question {
public:
    string question;
    vector<string> options;
    int correctAnswer;
    string explanation;

    void display() {
        cout << "\n----------------------------------\n";
        cout << question << endl;
        for (int i = 0; i < options.size(); i++) {
            cout << i + 1 << ") " << options[i] << endl;
        }
    }

    bool checkAnswer(int choice) {
        if (choice == correctAnswer) {
            cout << "Correct!\n";
            return true;
        } else {
            cout << "Wrong!\n";
            cout << "Explanation: " << explanation << endl;
            return false;
        }
    }
};

// ---------------- User Class ----------------
class User {
public:
    string name;

    void getUser() {
        cout << "Enter your name: ";
        cin >> name;
    }
};

// ---------------- File Manager ----------------
class FileManager {
public:
    void saveScore(string name, int score, int total) {
        ofstream file("scores.txt", ios::app);
        file << name << " - " << score << "/" << total << endl;
        file.close();
    }

    void showHistory() {
        ifstream file("scores.txt");
        string line;
        cout << "\nScore History:\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
};

// ---------------- Quiz Class ----------------
class Quiz {
private:
    vector<Question> questions;
    int score = 0;

public:
    void loadQuestions() {
        questions = {
            {
                "What is the output?\nint a = 5; cout << a++ + ++a;",
                {"10", "11", "12", "13"},
                3,
                "a++ = 5, ++a = 7, result = 12"
            },
            {
                "Identify the error:\nif(x = 5)",
                {"Syntax Error", "Logical Error", "Runtime Error", "No Error"},
                2,
                "Assignment operator used instead of comparison operator"
            },
            {
                "Next number: 2, 4, 8, 16, ?",
                {"18", "24", "32", "30"},
                3,
                "Pattern is multiplication by 2"
            },
            {
                "What is the output?\nint x = 10; cout << x-- - --x;",
                {"0", "1", "2", "-1"},
                3,
                "x-- gives 10, then --x makes it 8, so 10 - 8 = 2"
            },
            {
                "Which loop executes at least once?",
                {"for", "while", "do-while", "none"},
                3,
                "do-while executes before checking condition"
            },
            {
                "Largest number among 5, 9, 2, 7?",
                {"5", "7", "9", "2"},
                3,
                "9 is the largest"
            },
            {
                "What is output?\nint i = 1; while(i < 5) i++; cout << i;",
                {"4", "5", "6", "Error"},
                2,
                "Loop runs until i becomes 5"
            }
        };
    }

    void shuffleQuestions() {
        srand(time(0));
        random_shuffle(questions.begin(), questions.end());
    }

    void start() {
        shuffleQuestions();
        int choice;

        for (auto &q : questions) {
            q.display();
            cout << "Your answer: ";
            cin >> choice;

            if (q.checkAnswer(choice)) {
                score++;
            }
        }
    }

    int getScore() {
        return score;
    }

    int getTotal() {
        return questions.size();
    }

    void showResult() {
        cout << "\n----------------------------------\n";
        cout << "Final Score: " << score << "/" << questions.size() << endl;

        if (score == questions.size())
            cout << "Performance: Excellent\n";
        else if (score >= questions.size() / 2)
            cout << "Performance: Good\n";
        else
            cout << "Performance: Needs Improvement\n";
    }
};

// ---------------- MAIN ----------------
int main() {
    User user;
    Quiz quiz;
    FileManager file;

    user.getUser();
    quiz.loadQuestions();
    quiz.start();
    quiz.showResult();

    file.saveScore(user.name, quiz.getScore(), quiz.getTotal());
    file.showHistory();

    return 0;
}