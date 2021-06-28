#pragma once
#ifndef CHARTWINDOW_H
#define CHARTWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDialog>
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
QT_BEGIN_NAMESPACE
namespace Ui2 { class ChartWindow; }
QT_END_NAMESPACE

class ChartWindow : public QMainWindow
{
    Q_OBJECT

public:
    ChartWindow(QWidget* parent = nullptr);
    ~ChartWindow();

private slots:


private:
    Ui2::ChartWindow* ui;
    QString currentFile = "";
};
#endif // MAINWINDOW_H
