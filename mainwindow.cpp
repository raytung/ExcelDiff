#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 * TODO:
 * - enter path, if not exists or error, background tint red. FIN
 * - enter path, if exists, no error, background tint green. FIN
 * -
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   ui->setupUi(this);
    configure();
}


MainWindow::~MainWindow()
{
   delete ui;
    /*
    delete line;
    delete line_2;
    delete line_3;
    delete browse;
    delete browse_2;
    delete browse_3;
    delete compare;
    delete directories;
    delete mainWindow;
    delete progressBar;
    */
}

//Very organized. I like.
void MainWindow::configure()
{
    configureMainWindow();
    configureFileDialogs();
    configureQLineEdit();
    configureCheckBoxes();
    configureQPushButton();
    configureProgressBar();
    SignalsAndSlots();
    configureLayouts();
}

void MainWindow::configureCheckBoxes()
{
    ignoreCase = new QCheckBox("Ignore Case");
    checkTextStyle = new QCheckBox("Check Text Style");
    checkCellStyle = new QCheckBox("Check Cell Style");

//    ignoreCase->setText("Ignore Case");
//    checkTextStyle->setText("Check Text Style");
//    checkCellStyle->setText("Check Cell Style");
}

void MainWindow::configureMainWindow()
{
    mainWindow = new QWidget;
    mainWindow->setWindowTitle("ExcelDiff");
    mainWindow->setFixedSize(400, 280);
}

void MainWindow::configureFileDialogs()
{
    fileDiag   = new QFileDialog;
    fileDiag_2 = new QFileDialog;
    fileDiag_3 = new QFileDialog;

    fileDiag->setFileMode(QFileDialog::DirectoryOnly);
    fileDiag->setViewMode(QFileDialog::Detail);

    fileDiag_2->setFileMode(QFileDialog::DirectoryOnly);
    fileDiag_2->setViewMode(QFileDialog::Detail);

    fileDiag_3->setFileMode(QFileDialog::DirectoryOnly);
    fileDiag_3->setViewMode(QFileDialog::Detail);
}

void MainWindow::configureQLineEdit()
{
    line   = new QLineEdit(mainWindow);
    line_2 = new QLineEdit(mainWindow);
    line_3 = new QLineEdit(mainWindow);
    line->setPlaceholderText("1st Directory");
    line_2->setPlaceholderText("2nd Directory");
    line_3->setPlaceholderText("Report Directory");

    whenLineEditHasText(line);
}

void MainWindow::configureQPushButton()
{
    browse   = new QPushButton;
    browse_2 = new QPushButton;
    browse_3 = new QPushButton;
    compare  = new QPushButton;

    QString browse_text = "Browse";
    browse->setText(browse_text);
    browse_2->setText(browse_text);
    browse_3->setText(browse_text);
    compare->setText("Compare");
}

void MainWindow::configureProgressBar()
{
    progressBar = new QProgressBar;
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);
}

void MainWindow::SignalsAndSlots()
{
    connectBrowseWithFileDialog(browse, fileDiag);
    connectBrowseWithFileDialog(browse_2, fileDiag_2);
    connectBrowseWithFileDialog(browse_3, fileDiag_3);

    connectFileDiagWithLineEdit(fileDiag, line);
    connectFileDiagWithLineEdit(fileDiag_2, line_2);
    connectFileDiagWithLineEdit(fileDiag_3, line_3);

    whenLineEditHasText(line);
    whenLineEditHasText(line_2);
    whenLineEditHasText(line_3);
}


void MainWindow::configureLayouts()
{
    directories = new QGridLayout;
    options     = new QHBoxLayout;
    frame       = new QVBoxLayout;

    // GRID
    directories->addWidget(line,     0, 0); // addWidget(QWidget, row, column)
    directories->addWidget(line_2,   1, 0);
    directories->addWidget(line_3,   2, 0);
    directories->addWidget(browse,   0, 1);
    directories->addWidget(browse_2, 1, 1);
    directories->addWidget(browse_3, 2, 1);

    // Horizontal |||
    options->addWidget(ignoreCase);
    options->addWidget(checkTextStyle);
    options->addWidget(checkCellStyle);

    // Vertical =
    frame->addLayout(directories);
    frame->addLayout(options);
    frame->addWidget(compare);
    frame->addWidget(progressBar);

    mainWindow->setLayout(frame);
}

void MainWindow::connectBrowseWithFileDialog(QPushButton* button, QFileDialog* fileDialog)
{
    QObject::connect(button, SIGNAL(released()), fileDialog, SLOT(exec()));
}

void MainWindow::connectFileDiagWithLineEdit(QFileDialog* fileDiag, QLineEdit* lineEdit)
{
    QObject::connect(fileDiag, SIGNAL(fileSelected(QString)), lineEdit, SLOT(setText(QString)));
}

void MainWindow::whenLineEditHasText(QLineEdit* lineEdit)
{
    QSignalMapper* sigMap = new QSignalMapper(this);
    QObject::connect(lineEdit, SIGNAL(textChanged(QString)), sigMap,  SLOT(map()));
    sigMap->setMapping(lineEdit, lineEdit);

    QObject::connect(sigMap, SIGNAL(mapped(QWidget*)), this,  SLOT(checkDir(QWidget*)));
}

void MainWindow::checkDir(QWidget* widget)
{
    QLineEdit* lineEdit = (QLineEdit*) widget;
    QString str = lineEdit->text();
    QDir d(str);

    // size > 0, incase of empty string
    if(d.exists() && str.size() > 0)
        lineEdit->setStyleSheet("QLineEdit{background: rgba(103,199,62, 1);}");
    else
        lineEdit->setStyleSheet("QLineEdit{background: rgba(208,49, 41, 1); color: white }");
}
