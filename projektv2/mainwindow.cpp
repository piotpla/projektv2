#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtWidgets"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QTextBrowser>
#include <QApplication>
#include <QMessageBox>
#include <QTableWidget>


int ukryte = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}








void MainWindow::on_otworz_triggered()
{
    // Opens a dialog that allows you to select a file to open
        QString fileName = QFileDialog::getOpenFileName(this, "Otwórz plik");

        // An object for reading and writing files
        QFile file(fileName);

        // Store the currentFile name
        currentFile = fileName;

        // Try to open the file as a read only file if possible or display a
        // warning dialog box
        if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "Uwaga!", "Nie można otworzyć pliku: " + file.errorString());
            return;
        }

        // Set the title for the window to the file name
        setWindowTitle(fileName);

        // Interface for reading text
        QTextStream in(&file);

        // Copy text in the string
        QString text = in.readAll();

        // Put the text in the textEdit widget, tak zpliku wchodzic beda tabele i wykresy i wyniki
       // ui->textEdit->setText(text);


        QTextStream in(&file);

        // Copy text in the string
        QString text = in.readAll();

        // Put the text in the textEdit widget, tak zpliku wchodzic beda tabele i wykresy i wyniki
        ui->textBrowser->setText(text);







        // Close the file
        file.close();
}


void MainWindow::on_Zapis_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Zapisz");
        QFile file(fileName);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Uwaga!", "Nie można zapisać pliku: " + file.errorString());
            return;
        }
        currentFile = fileName;
        setWindowTitle(fileName);
        QTextStream out(&file);
        //QString text = ui->textEdit->toPlainText(); na zapis danych
        //out << text;
        file.close();
}


void MainWindow::on_Zapiszjako_triggered()
{
    // Opens a dialog for saving a file
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Zapisz jako"), "",
            tr("Analiza (*.hgw);;Wszystkie pliki (*)"));

        // An object for reading and writing files
        QFile file(fileName);

        // Try to open a file with write only options
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Uwaga!", "Nie można zapisać pliku: " + file.errorString());
            return;
        }

        // Store the currentFile name
        currentFile = fileName;

        // Set the title for the window to the file name
        setWindowTitle(fileName);

        // Interface for writing text
        QTextStream out(&file);

        // Copy text in the textEdit widget and convert to plain text, zapis naszych danych
        //QString text = ui->textEdit->toPlainText();

        // Output to file, cd zapis danych
       // out << text;

        // Close the file
        file.close();
}

