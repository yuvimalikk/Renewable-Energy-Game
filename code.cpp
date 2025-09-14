#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<cstring>

using namespace std;

const int maxQuestion = 30;
const int OPTIONS = 4;

struct Question {
    char text[200];
    char options[OPTIONS][100];
    int correctAnswer;
};

void readQuestions(Question q[], int &count) {
    ifstream file("question.txt");
    if (!file) {
        cout << "Unable to open questions.txt\n";
        exit(1);
    }

    count = 0;
    while (file.getline(q[count].text, 200)) {
        for (int i = 0; i < OPTIONS; i++) {
            file.getline(q[count].options[i], 100);
        }
        file >> q[count].correctAnswer;
        file.ignore(); // Skip newline after number
        count++;
    }

    file.close();
}

void shuffleQuestions(Question q[], int count) {
    srand(time(0));
    for (int i = 0; i < count; i++) {
        int j = rand() % count;
        // Swap q[i] and q[j]
        Question temp = q[i];
        q[i] = q[j];
        q[j] = temp;
    }
}

void writeScore(int score, int total) {
    ofstream out("score.txt");
    out << "Your final score : " << score << "/" << total << endl;
    out.close();
}

int main() {
    Question questions[maxQuestion];
    int totalQuestion;
    readQuestions(questions, totalQuestion);

    shuffleQuestions(questions, totalQuestion);

    int score = 0;
    int questionsToAsk = 30; // You can change this according to our needs

    for (int i = 0; i < questionsToAsk && i < totalQuestion; i++) {
        cout << "\nQ" << (i + 1) << ": " << questions[i].text << endl;
        for (int j = 0; j < OPTIONS; j++) {
            cout << j + 1 << ". " << questions[i].options[j] << endl;
        }

        int userAnswer;
        cout << "Your answer (1-4): ";
        cin >> userAnswer;

        if (userAnswer == questions[i].correctAnswer) {
            cout << "Correct!\n";
            score += 10;
        } else {
            cout << "Wrong! Correct answer was: " << questions[i].correctAnswer << "\n";
        }
    }

    cout << "\nTotal Score: " << score << " out of " << (questionsToAsk * 10) << endl;
    writeScore(score, questionsToAsk * 10);

    return 0;
}
