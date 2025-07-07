#include "assignmentscores.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include "ui_assignmentscores.h"
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QTextStream>
#include <QSqlError>
#include <QDebug>

assignmentscores::assignmentscores(QSqlDatabase db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::assignmentscores)
    , mainModel(nullptr)
    , proxyModel(nullptr)
{
    ui->setupUi(this);

    setWindowTitle("Mulyankan");

    mainModel=new QSqlTableModel(this,db);
    mainModel->setTable("students");

    mainModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    mainModel->setHeaderData(0,Qt::Horizontal,tr("Student Name"));
    mainModel->setHeaderData(1,Qt::Horizontal,tr("Assignment 1"));
    mainModel->setHeaderData(2,Qt::Horizontal,tr("Assignment 2"));
    mainModel->setHeaderData(3,Qt::Horizontal,tr("Assignment 3"));
    mainModel->setHeaderData(4,Qt::Horizontal,tr("MCQ"));
    mainModel->setHeaderData(5,Qt::Horizontal,tr("Total"));

    if(!mainModel->select()){
        QMessageBox::critical(this,"Database Error","Could not load student data:"+mainModel->lastError().text());
        return;
    }

    proxyModel=new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(mainModel);

    ui->assignmentTableView->setModel(proxyModel);
    ui->assignmentTableView->resizeColumnsToContents();
}

assignmentscores::~assignmentscores()
{
    delete ui;
}

void assignmentscores::on_backButton_clicked()
{
    if(mainModel->isDirty())
    {
        QMessageBox::StandardButton reply;
        reply=QMessageBox::question(this,"Unsaved Changes","Do you want to save the changes?",QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(reply==QMessageBox::Yes)
        {
            mainModel->submitAll();
        }
        else if(reply==QMessageBox::Cancel)
        {
            return;
        }
    }
    emit backToLandingPage();
    close();
}

void assignmentscores::on_saveButton_clicked()
{
    if(mainModel->submitAll())
    {
        statusBar()->showMessage("Changes saved successfully",500);
    }
    else
    {
        statusBar()->showMessage("Could not save changes:"+mainModel->lastError().text(),500);
    }
}

void assignmentscores::on_addStudentButton_clicked()
{
    mainModel->insertRow(mainModel->rowCount());
    ui->assignmentTableView->scrollToBottom();
}

void assignmentscores::on_DeleteStudentButton_clicked()
{
    QItemSelectionModel *selectionModel = ui->assignmentTableView->selectionModel();
    if (!selectionModel->hasSelection()) {
        statusBar()->showMessage("Please select students to delete.");
        return;
    }

    QModelIndexList selectedRows = selectionModel->selectedRows();

    std::sort(selectedRows.rbegin(), selectedRows.rend());

    for (const QModelIndex &viewIndex : selectedRows) {
        QModelIndex sourceIndex = proxyModel->mapToSource(viewIndex);
        mainModel->removeRow(sourceIndex.row());
    }
    statusBar()->showMessage("Rows Removed");
}

