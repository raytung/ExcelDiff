#ifndef MAINWINDOW_H
#   define MAINWINDOW_H
#   include <QMainWindow>
#   include <QLabel>
#   include <QHBoxLayout>
#   include <QGridLayout>
#   include <QLineEdit>
#   include <QPushButton>
#   include <QFileDialog>
#   include <QStringList>
#   include <QLineEdit>
#   include <iostream>
#   include <QCheckBox>
#   include <QVBoxLayout>
#   include <QProgressBar>
#   include <QDir>
#   include <QSignalMapper>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QWidget* mainWindow;



private slots:
    //void on_pushButton_clicked();
    void checkDir(QWidget* dir);




private:
    Ui::MainWindow *ui;
    QLineEdit* line;
    QLineEdit* line_2;
    QLineEdit* line_3;
    QPushButton* browse;
    QPushButton* browse_2;
    QPushButton* browse_3;
    QPushButton* compare;
    QFileDialog* fileDiag;
    QFileDialog* fileDiag_2;
    QFileDialog* fileDiag_3;
    QCheckBox* ignoreCase;
    QCheckBox* checkTextStyle;
    QCheckBox* checkCellStyle;

    QGridLayout* directories;
    QHBoxLayout* options;
    QVBoxLayout* frame;
    QProgressBar* progressBar;

    QDir* dir;

    void configure();
    void configureQLineEdit();
    void configureQPushButton();
    void configureFileDialogs();
    void connectBrowseWithFileDialog(QPushButton* button, QFileDialog* fileDialog);
    void connectFileDiagWithLineEdit(QFileDialog* fileDiag, QLineEdit* lineEdit);
    void SignalsAndSlots();
    void configureLayouts();
    void configureMainWindow();
    void configureCheckBoxes();
    void configureProgressBar();
    void whenLineEditHasText(QLineEdit* lineEdit);
};

#endif // MAINWINDOW_H
