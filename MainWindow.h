#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "lib/WorldScene.h"
#include "lib/WorldBody.h"
#include "lib/WorldFixture.h"
#include "lib/WorldCircleFixture.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    WorldScene scene_;
    std::unique_ptr<WorldBody> body;
    std::unique_ptr<WorldFixture> fixture;
    std::unique_ptr<WorldBody> body2;
    std::unique_ptr<WorldFixture> fixture2;
    std::unique_ptr<WorldBody> body3;
    std::unique_ptr<WorldFixture> fixture3;
};

#endif // MAINWINDOW_H
