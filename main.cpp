// #include <QApplication>
// #include <QScreen>
// #include <QSplashScreen>
// #include <QTimer>
// #include <QObject>
// #include <QPushButton>
// #include <QSqlDatabase>
// #include <QMessageBox>
// #include <QDebug>
// #include "mainwindow.h"
// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);
//     MainWindow w;

//     QSplashScreen *splash = new QSplashScreen;
//     splash->setPixmap(QPixmap(":/image/img/ChatGPT Image Jun 11, 2025, 05_45_04 PM.png"));
//     splash->show();

//     QTimer::singleShot(1500, splash, SLOT(close()));
//     QTimer::singleShot(1500, &w, SLOT(show()));
//     // w.show();

// LandingPage landingPage;
// AssignmentScores scoresDialog;

// QObject::connect(&landingPage, &LandingPage::goToScoresClicked, [&]() {
//     landingPage.hide();
//     scoresDialog.show();
// });

// QObject::connect(&scoresDialog, &AssignmentScores::backToLandingPage, [&]() {
//     landingPage.show();
// });

// landingPage.show();

//     return a.exec();
// }

#include "assignmentscores.h" // Your scores window
#include "landingpage.h"      // Your landing page window
//#include "ui_landingpage.h"
#include <QApplication>
#include <QObject>
#include <QPushButton>
#include <QSqlDatabase> // Make sure to include this
#include <QMessageBox>  // Good for error reporting
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 1. Create instances of BOTH windows. They exist in memory but are not visible yet.
    landingpage landingPage;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("your_database_file.db"); // Make sure this path is correct

    if (!db.open()) {
        QMessageBox::critical(nullptr, "Database Error", "Could not open the database!");
        return -1; // Exit if the database can't be opened
    }

    // --- Step 2: Create the dialog and pass the database ---
    assignmentscores w(db); // Pass the 'db' object here
    w.show();

    return a.exec();
}
