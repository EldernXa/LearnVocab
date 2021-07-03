#include "quizvocab.h"
#include "ui_quizvocab.h"

using namespace std;

QuizVocab::QuizVocab(string nameVocabToQuiz, QuizType quizType, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuizVocab)
{
    ui->setupUi(this);
    nameVocab = nameVocabToQuiz;
}

QuizVocab::~QuizVocab()
{
    delete ui;
}
