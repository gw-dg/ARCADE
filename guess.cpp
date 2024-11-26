#include <bits/stdc++.h>
using namespace std;

// Binary Tree of Questions
struct Ques
{
    string data; // Stores the question or answer
    Ques *yes;   // Pointer for "yes" responses
    Ques *no;    // Pointer for "no" responses

    Ques(string value) : data(value), yes(nullptr), no(nullptr) {}
};

bool askYesNo(string question)
{
    char response;
    while (true)
    {
        cout << question << " (y/n): ";
        cin >> response;
        if (response == 'y' || response == 'Y')
            return true;
        if (response == 'n' || response == 'N')
            return false;
        cout << "Please respond with 'y' or 'n'.\n";
    }
}

void playGame(Ques *curr)
{
    while (curr->yes && curr->no)
    {
        if (askYesNo(curr->data))
        {
            curr = curr->yes;
        }
        else
        {
            curr = curr->no;
        }
    }

    // We're at a leaf Ques
    if (askYesNo("Is it " + curr->data + "?"))
    {
        cout << "I guessed it! Yay!\n";
    }
    else
    {
        cout << "I give up! What were you thinking of? ";
        string newAnswer;
        cin.ignore(); // To consume the leftover newline character
        getline(cin, newAnswer);

        cout << "What question would distinguish " << newAnswer << " from " << curr->data << "?\n";
        string newQuestion;
        getline(cin, newQuestion);

        bool isYesForNew = askYesNo("For " + newAnswer + ", what is the answer to \"" + newQuestion + "\"?");

        // new question and answer
        Ques *oldAnswer = new Ques(curr->data);
        Ques *newAnswerQues = new Ques(newAnswer);

        curr->data = newQuestion;
        if (isYesForNew)
        {
            curr->yes = newAnswerQues;
            curr->no = oldAnswer;
        }
        else
        {
            curr->yes = oldAnswer;
            curr->no = newAnswerQues;
        }

        cout << "Thanks! I'll be smarter next time!\n";
    }
}

// In-order traversal
void printTree(Ques *root, string prefix = "")
{
    if (!root)
        return;
    cout << prefix << root->data << "\n";
    printTree(root->yes, prefix + "  Yes-> ");
    printTree(root->no, prefix + "  No-> ");
}

void gameStartGuess()
{
    // Initialize the BT
    Ques *root = new Ques("Is it an animal?");
    root->yes = new Ques("Is it a mammal?");
    root->no = new Ques("Is it a machine?");

    // Animal questions
    root->yes->yes = new Ques("Is it a dog?");
    root->yes->no = new Ques("Is it a cat?");

    // Machine questions
    root->no->yes = new Ques("Is it a car?");
    root->no->no = new Ques("Is it a computer?");

    cout << "Welcome to 20 Questions!\n";
    while (true)
    {
        playGame(root);

        if (!askYesNo("Do you want to play again?"))
            break;
    }

    cout << "Thanks for playing! Goodbye!\n";
}
