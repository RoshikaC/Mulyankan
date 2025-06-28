#include "assignmentscores.h"
#include "ui_assignmentscores.h"
#include <QStandardItemModel>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextEdit>
//#include <QDialog>

assignmentscores::assignmentscores(QWidget *parent) : QDialog(parent), ui(new Ui::assignmentscores)
{
    ui->setupUi(this);

    setWindowTitle("Mulyankan");

    int numRows = 5;//have to be able to increase or decrease the rows and columns
    int numCols = 11;
    QStandardItemModel *model = new QStandardItemModel(numRows, numCols, this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Student Name")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Total Attendance_Score")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Assignment 1")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Assignment 2")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Assignment 3")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("MCQ")));
    model->setHorizontalHeaderItem(6, new QStandardItem(QString("Internal 1")));
    model->setHorizontalHeaderItem(7, new QStandardItem(QString("Internal 2")));
    model->setHorizontalHeaderItem(8, new QStandardItem(QString("Lab Exam")));
    model->setHorizontalHeaderItem(9, new QStandardItem(QString("Viva")));
    model->setHorizontalHeaderItem(10, new QStandardItem(QString("Total")));

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            QStandardItem *item = new QStandardItem(" ");
            model->setItem(row, col, item);
        }
    }

    ui->assignmentTableView->setModel(model);
    ui->assignmentTableView->resizeColumnsToContents();
}

assignmentscores::~assignmentscores()
{
    delete ui;
}

void assignmentscores::on_backButton_clicked()
{
    emit backToLandingPage();
    close();
}


void assignmentscores::on_saveButton_clicked()
{
    QString currentFile = QFileDialog::getSaveFileName(this, "Save As", "", "CSV File (*.csv);;Text File (*.txt)");

    if (currentFile.isEmpty()) {
        return;
    }
    QFile file(currentFile);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"WARNING","Cannot save file:"+file.errorString());
        return;
    }
    QTextStream out(&file);
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->assignmentTableView->model());
    if (!model) {
        QMessageBox::critical(this, "Error", "Could not get table model.");
        return;
    }
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QStandardItem *item = model->item(row, col);
            if (item) {
                out << item->text();
            }
        }
        out << "\n";
    }
    file.close();
    QMessageBox::information(this, "Success", "File saved successfully!");
}

