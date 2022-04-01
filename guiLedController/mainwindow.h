#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Serial;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_redButton_clicked();

    void on_greenButton_clicked();

    void on_blueButton_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<Serial> device;
    char ledStatus;
};
#endif // MAINWINDOW_H
