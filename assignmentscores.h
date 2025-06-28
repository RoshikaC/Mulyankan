#ifndef ASSIGNMENTSCORES_H
#define ASSIGNMENTSCORES_H
#include "qdialog.h"
//#include <QMainWindow>
#include <QDialog>

namespace Ui {
class assignmentscores;
}

class assignmentscores : public QDialog
{
    Q_OBJECT

public:
    explicit assignmentscores(QWidget *parent = nullptr);
    ~assignmentscores();

signals:
    void backToLandingPage();

private slots:
    void on_backButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::assignmentscores *ui;
    //QString currentFile;
};

#endif // ASSIGNMENTSCORES_H
