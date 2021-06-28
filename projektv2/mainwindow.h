#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include "Chart.h"
//#include <QPrinter>
//#include <QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

   

    void on_otworz_triggered();

    void on_action_Otw_rz_triggered();

    void on_analiza_triggered();

    void on_Zapis_triggered();

    void on_Zapiszjako_triggered();

    void on_action_Zapisz_triggered();

    void on_action_Zapisz_jako_triggered();

    void on_Wykres_triggered();

private:
    Ui::MainWindow *ui;
    QString currentFile = "";
	Chart *chart;
};
#endif // MAINWINDOW_H
