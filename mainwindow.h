#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "assignmentscores.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void loadStudentsAssignments(const QList<assignmentscores> &assignments);
};
#endif // MAINWINDOW_H
