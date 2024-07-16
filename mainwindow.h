#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void keyboardButtonClicked();
    void updateKeyboardLayout();

private:
    QGridLayout *keyboardLayout;
    QLineEdit *lineEdit;
    QListWidget *listWidget;
    bool capsLockEnabled; 
    QStringList keysNoCaps;
    QStringList keysCaps;
    void setupUI();
    void setupKeyboard();
};
#endif // MAINWINDOW_H
