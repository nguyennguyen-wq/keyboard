#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    setupKeyboard();
}

MainWindow::~MainWindow()
{
}

void MainWindow::keyboardButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());   
    if (button) {
        QString buttonText = button->text();
        if (buttonText == "Caps") {
            capsLockEnabled = !capsLockEnabled;
            updateKeyboardLayout();
            return;
        }
        if (buttonText == "Backspace") {
            QString currentText = lineEdit->text();
            if (!currentText.isEmpty()) {
                currentText.chop(1); 
                lineEdit->setText(currentText);
                listWidget->addItem("Backspace");
            }
            return;
        }
        if (buttonText == "spa") {
            buttonText = " ";  
        }
        if (capsLockEnabled) {
            buttonText = buttonText.toUpper();
        }

        lineEdit->insert(buttonText);
        listWidget->addItem(buttonText);
    }
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    lineEdit = new QLineEdit();
    lineEdit->setFixedWidth(300);
    lineEdit->setFixedHeight(40); 
    QFont font("Arial", 12); 
    lineEdit->setFont(font);
    mainLayout->addWidget(lineEdit);
    listWidget = new QListWidget();
    keyboardLayout = new QGridLayout();
    mainLayout->addLayout(keyboardLayout);
}

void MainWindow::setupKeyboard()
{
    keysCaps = {
        "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
        "Å", "A", "S", "D", "F", "G", "H", "J", "K", "L",
        "Ø", "Z", "X", "C", "V", "B", "N", "M", "Æ",
        "spa"
    };

    keysNoCaps = {
        "q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
        "å", "a", "s", "d", "f", "g", "h", "j", "k", "l",
        "ø", "z", "x", "c", "v", "b", "n", "m", "æ",
        "spa"
    };

    capsLockEnabled = false; 
    updateKeyboardLayout();
}


void MainWindow::updateKeyboardLayout()
{
    QLayoutItem *child;
    while ((child = keyboardLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    QStringList keys = capsLockEnabled ? keysCaps : keysNoCaps;
    int row = 0;
    int col = 0;
    int buttonWidth = 60; 
    int buttonHeight = 40;  

    foreach (QString key, keys) {
        QPushButton *button = new QPushButton(key);
        button->setFixedSize(buttonWidth, buttonHeight); 
        button->setStyleSheet("font: bold;background-color: navy; color: white;font-size: 25px;height: 48px;width: 120px;");
        connect(button, &QPushButton::clicked, this, &MainWindow::keyboardButtonClicked);
        keyboardLayout->addWidget(button, row, col);
        col++;
        if (col > 9) {
            col = 0;
            row++;
        }
    }

    QPushButton *capsButton = new QPushButton("Caps");	
    capsButton->setStyleSheet("font: bold;background-color: teal; color: white;font-size: 25px;height: 48px;width: 120px;");
    capsButton->setFixedSize(buttonWidth * 2, buttonHeight); 
    connect(capsButton, &QPushButton::clicked, this, &MainWindow::keyboardButtonClicked);
    keyboardLayout->addWidget(capsButton, row, 8, 1, 2); 
    QPushButton *backspaceButton = new QPushButton("Backspace");
    backspaceButton->setFixedSize(buttonWidth * 2, buttonHeight);
    backspaceButton->setStyleSheet("font: bold;background-color: teal; color: white;font-size: 25px;height: 48px;width: 120px;");
	connect(backspaceButton, &QPushButton::clicked, this, &MainWindow::keyboardButtonClicked);
    keyboardLayout->addWidget(backspaceButton, row, 6, 1, 2); 
}

