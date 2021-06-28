#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Controler.h"
#include "QtWidgets"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QTextBrowser>
#include <QApplication>
#include <QMessageBox>
#include <QTableWidget>
#include <QDateTime>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QDialog>
#include "Chart.h"
QString fileName = "";
bool zapisano = 0;
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

InData data_from_file;
OutData data_results;
Controler control;



void MainWindow::on_otworz_triggered()
{
    ui->tableWidget->setRowCount(0);
	ui->progressBar->setValue(0);
	
    // Opens a dialog that allows you to select a file to open
        QString fileName = QFileDialog::getOpenFileName(this, "Otwórz plik");

        // An object for reading and writing files
        QFile file(fileName);

        // Store the currentFile name
        currentFile = fileName;

        // Try to open the file as a read only file if possible or display a
        // warning dialog box
        if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, QTime::currentTime().toString("hh:mm:ss") + " " + "Uwaga!", "Nie można otworzyć pliku: " + file.errorString());
			ui->textBrowser->append(QTime::currentTime().toString("hh:mm:ss") + " BŁĄD! Nie można otworzyć pliku: " + file.errorString());

            return;
        }

        // Set the title for the window to the file name
        setWindowTitle(fileName);

        // Interface for reading text
        QTextStream in(&file);

    
        QString text = in.readAll();

    

       std::string file_name = fileName.toStdString();
       data_from_file = control.read_file(file_name);
   

       const int size_tab = data_from_file.data[0].size();
      
           ui->tableWidget->setColumnCount(size_tab);
           QStringList labels;
		   int wereheaders=0;
		   ui->progressBar->setValue(10);
       for (int i = 0; i < data_from_file.data.size(); ++i)
       {
           for (int j = 0; j < data_from_file.data[i].size(); ++j)
           {
               if(i==0)
               {
				   if (std::isdigit(data_from_file.data[0][0]))
				   {
					   QString s = QString::number(data_from_file.data[i][j]);
					   labels << s;
					   ui->tableWidget->setHorizontalHeaderLabels(labels);
					   wereheaders = 1;
				   }
				   else
				   {
					   QString temp = QString::number(j);                    
					   QString ps = "Kolumna ";
					   ps.append(temp);
					   labels << ps;
					   ui->tableWidget->setHorizontalHeaderLabels(labels);
				   }
               }
     
           }
           ui->tableWidget->insertRow(i);
          

       }
	   ui->progressBar->setValue(60);

       if (wereheaders == 1)
       {
			for (int i = 0; i < data_from_file.data.size()-1; ++i)
            {
                for (int j = 0; j < data_from_file.data[i].size(); ++j)
            {		  
				   QTableWidgetItem* elementwiersza = new QTableWidgetItem;
				   elementwiersza->setText(QString::number(data_from_file.data[i+1][j]));
				   ui->tableWidget->setItem(i, j, elementwiersza);
           }           
       } 
       }
       else
       {
       for (int i = 0; i < data_from_file.data.size(); ++i)
            {
                for (int j = 0; j < data_from_file.data[i].size(); ++j)
            {		  
				   QTableWidgetItem* elementwiersza = new QTableWidgetItem;
				   elementwiersza->setText(QString::number(data_from_file.data[i][j]));
				   ui->tableWidget->setItem(i, j, elementwiersza);
           }
       }
      
       }

       

	   ui->progressBar->setValue(90);

        
        file.close();
		ui->progressBar->setValue(100);
		ui->textBrowser->append(QTime::currentTime().toString("hh:mm:ss") + " " + "Plik otwarto poprawnie");

}

//========================================================================================================================================
void MainWindow::on_action_Otw_rz_triggered()
{
   on_otworz_triggered();
}

//========================================================================================================================================
void MainWindow::on_analiza_triggered()
{
     ui->tableWidget_2->setRowCount(0);
	ui->progressBar->setValue(0);
    data_results = control.analyze(data_from_file);
    int size_min = data_results.min.size();
    ui->tableWidget_2->setColumnCount(size_min);
    QStringList labels;
    

    for (int i = 0; i < 4; ++i)
    {

        for (int j = 0; j < data_results.min.size(); ++j)
        {
            if (i == 0)
            {
                    QString temp = QString::number(j);                     //cyfra kolumny
                    QString ps = "Kolumna ";
                    ps.append(temp);
                    labels << ps;
                    ui->tableWidget_2->setHorizontalHeaderLabels(labels);
                
            }

        }
        ui->tableWidget_2->insertRow(i);

    }
	ui->progressBar->setValue(60);
   
    for (int i = 0; i < data_results.min.size(); ++i) //wypisanie vektora minow
    {
            QTableWidgetItem* elementwiersza = new QTableWidgetItem;
            elementwiersza->setText(QString::number(data_results.min[i]));
            ui->tableWidget_2->setItem(0,i, elementwiersza);
        
    }
	ui->progressBar->setValue(70);
    for (int i = 0; i < data_results.max.size(); ++i) //wypisanie vektora maxow
    {
        QTableWidgetItem* elementwiersza = new QTableWidgetItem;
        elementwiersza->setText(QString::number(data_results.max[i]));
        ui->tableWidget_2->setItem(1, i, elementwiersza);

    }
	ui->progressBar->setValue(80);
    for (int i = 0; i < data_results.med.size(); ++i) //wypisanie vektora medow
    {
        QTableWidgetItem* elementwiersza = new QTableWidgetItem;
        elementwiersza->setText(QString::number(data_results.med[i]));
        ui->tableWidget_2->setItem(2, i, elementwiersza);

    }
	ui->progressBar->setValue(90);
    for (int i = 0; i < data_results.avg.size(); ++i) //wypisanie vektora avg
    {
        QTableWidgetItem* elementwiersza = new QTableWidgetItem;
        elementwiersza->setText(QString::number(data_results.avg[i]));
        ui->tableWidget_2->setItem(3, i, elementwiersza);

    }
    QStringList labels2;
    labels2 << "MIN" << "MAX" << "MED" << "AVG";
    ui->tableWidget_2->setVerticalHeaderLabels(labels2);
	ui->progressBar->setValue(100);
	ui->textBrowser->append(QTime::currentTime().toString("hh:mm:ss") + " " + "Analiza wykonana poprawnie");

}
//========================================================================================================================================


void MainWindow::on_Zapis_triggered()
{
    if (fileName.toStdString() == "")
    {
        zapisano = 0;
    }

    if (zapisano == 0) { on_Zapiszjako_triggered(); }
    else {
        ui->progressBar->setValue(0);
      
        std::string file_name = fileName.toStdString();
        control.save_file(data_results, file_name);
        ui->progressBar->setValue(100);

        zapisano = 1;
		ui->textBrowser->append(QTime::currentTime().toString("hh:mm:ss") + " " + "Zapisano plik");
    }
}
//========================================================================================================================================
void MainWindow::on_action_Zapisz_triggered()
{
    on_Zapis_triggered();
}
//========================================================================================================================================
void MainWindow::on_Zapiszjako_triggered()
{
    
     fileName = QFileDialog::getSaveFileName(this,
            tr("Zapisz jako"), "",
            tr("Analiza (*.hgw);;Wszystkie pliki (*)"));

        

       
        setWindowTitle(fileName);
        std::string file_name = fileName.toStdString();
        control.save_file(data_results, file_name);
     
        
		zapisano = 1;
        ui->textBrowser->append(QTime::currentTime().toString("hh:mm:ss") + " " + "Zapisano plik w lokalizacji: " + fileName);
       
}

//========================================================================================================================================

void MainWindow::on_action_Zapisz_jako_triggered()
{
    on_Zapiszjako_triggered();
}

//=========================================================================================================================================

void MainWindow::on_Wykres_triggered() 
{
	//chart = new Chart(this);

    chart = new Chart(this);
    chart->show();
}