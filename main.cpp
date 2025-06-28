// #include <QApplication>
// #include <QScreen>
// #include <QSplashScreen>
// #include <QTimer>
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

#include "landingpage.h"       // Your landing page window
#include "assignmentscores.h"  // Your scores window
//#include "ui_landingpage.h"
#include <QApplication>
#include <QObject>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 1. Create instances of BOTH windows. They exist in memory but are not visible yet.
    landingpage landingPage;
    assignmentscores scoresDialog;

    // 2. Connect the "back" signal from the scores dialog.
    // When scoresDialog emits "backButtonPressed", we want to show the landing page.
    QObject::connect(&scoresDialog, &assignmentscores::backToLandingPage, &landingPage, &landingpage::show);

    // 3. Connect the button on your landing page to show the scores dialog.
    //    (Assuming your button on landingpage is named 'goToScoresButton')
    // When the button is clicked, hide the landing page and show the scores dialog.
    QObject::connect(&landingPage, &landingpage::goToScoresClicked, [&](){
        landingPage.hide();
        scoresDialog.show();
    });

    // ======================================================================
    // === CHOOSE WHICH WINDOW TO SHOW FIRST FOR TESTING ====================
    // ======================================================================

    // --- To test the assignmentscores dialog, show it first: ---
    scoresDialog.show();

    /*
    // --- For normal application flow, show the landing page first: ---
    landingPage.show();
    */


    return a.exec();
}
