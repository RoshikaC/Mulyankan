#ifndef ASSIGNMENTSCORES_H
#define ASSIGNMENTSCORES_H
//#include "qdialog.h"
#include "qdialog.h"
#include <QMainWindow>
#include <QSqlDatabase>

class QSqlTableModel;
class QSortFilterProxyModel;
class QAbstractItemModel;

namespace Ui {
class assignmentscores;
}

class assignmentscores : public QMainWindow
{
    Q_OBJECT

public:
    explicit assignmentscores(QSqlDatabase db, QWidget *parent = nullptr);
    ~assignmentscores();

signals:
    void backToLandingPage();

private slots:
    void on_backButton_clicked();

    void on_saveButton_clicked();

    void on_addStudentButton_clicked();

    void on_DeleteStudentButton_clicked();

private:
    Ui::assignmentscores *ui;
    QSqlTableModel *mainModel;
    QSortFilterProxyModel *proxyModel;
};

#endif // ASSIGNMENTSCORES_H
