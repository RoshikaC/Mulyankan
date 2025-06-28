#ifndef LANDINGPAGE_H
#define LANDINGPAGE_H

#include <QMainWindow>

namespace Ui {
class landingpage;
}

class landingpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit landingpage(QWidget *parent = nullptr);
    ~landingpage();

signals:
    void goToScoresClicked();

private:
    Ui::landingpage *ui;
};

#endif // LANDINGPAGE_H
