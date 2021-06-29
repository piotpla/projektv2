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
#include <exception>
#include <cstdlib>
#include <stdio.h>
QString fileName = ""; //zmienna globalna z nazwa pliku
bool zapisano = 0; //zmienna z informacja, czy plik juz byl uprzednio zapisany do pliku
MainWindow::MainWindow(QWidget* parent) //konstruktor klasy
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow() //dekonstruktor klasy
{
	delete ui;
}

InData data_from_file; //wywolanie obiektu klasy indata z danymi z plikow
OutData data_results; //wywolanie obiektu klasy z outdata z danymi do zapisania do pliku
Controler control; //wywoalanie obiektu klasy controler do obslugi wszystkich algorytmow



void MainWindow::on_otworz_triggered()
{
	ui->tableWidget->setRowCount(0);
	ui->progressBar->setValue(0); //zerowanie pasku postepu

	QString fileName = QFileDialog::getOpenFileName(this, "Otwórz plik"); //otwarcie okna do wybrania pliku


	QFile file(fileName); // Obiekt do otwarcia pliku




	 //Proba otwarcia pliku w trybie odczytu, jesli nie uda sie, wyswietla komunikat o bledzie
	if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, QTime::currentTime().toString("hh:mm:ss") + " " + "Uwaga!", "Nie można otworzyć pliku: " + file.errorString());
		ui->textBrowser->append(QTime::currentTime().toString("hh:mm:ss") + " BŁĄD! Nie można otworzyć pliku: " + file.errorString());

		return;
	}

	//ustawienie nazwy okna
	setWindowTitle(fileName);

	// Interfejs do zczytywania pliku 
	QTextStream in(&file);


	QString text = in.readAll();



	std::string file_name = fileName.toStdString();
	std::string enl = file_name.substr((file_name.size() - 3), 3);

	if (enl == "csv")
	{
		try
		{
			data_from_file = control.read_file(file_name);
			ui->textBrowser->append(QTime::currentTime().toString("hh:mm:ss") + " " + "Plik otwarto poprawnie"); // wyswietlenie w logu informacji o tym, ze wszystko poszlo sprawnie
		}
		catch (...)
		{
			ui->textBrowser->append(QTime::currentTime().toString("hh:mm:ss") + " " + "Błąd otwarcia pliku - plik zawiera niekompletne dane");
			return;
		}
	}
	else
	{
		ui->textBrowser->append(QTime::currentTime().toString("hh:mm:ss") + " " + "Błąd otwarcia pliku - plik musi być w rozszerzenie CSV");
		return;
	}


	const int size_tab = data_from_file.data[0].size(); //zmienna przetrzymujaca liczbe kolumn

	ui->tableWidget->setColumnCount(size_tab); //ustalenie liczby kolumn
	QStringList labels; //utworzenie obiektu typu QStringList
	int wereheaders = 0; //utworzenie zmiennej przetrzymujacej informacje, czy w pierwszym wierszu byly naglowki
	ui->progressBar->setValue(10); //zwiekszenie pasku postepu do 10%
	for (int i = 0; i < data_from_file.data.size(); ++i) //petle do tworzenia pustej tabeli
	{
		for (int j = 0; j < data_from_file.data[i].size(); ++j)
		{
			if (i == 0) //w przypadku  pierwszego wiersza
			{
				if (std::isdigit(data_from_file.data[0][0]))//jesli w pierwszym wierszu sa stringi z nazwami kolumnamn
				{
					QString s = QString::number(data_from_file.data[i][j]); //string z danymi z pierwszego wiersza
					labels << s;
					ui->tableWidget->setHorizontalHeaderLabels(labels); //ustawienie nazwy kolumny daną z wiersza
					wereheaders = 1; //zmiana flagi naglowkow 
				}
				else //jesli nie ma nazw kolumn
				{
					QString temp = QString::number(j); //konwersja zmiennej j na zmienaa qstring                  
					QString ps = "Kolumna "; // tworzenie qstring do nazywania kolumn
					ps.append(temp); //laczenie napisy kolumna z jej numerem
					labels << ps;
					ui->tableWidget->setHorizontalHeaderLabels(labels); //usawienie nazwy kolumny
				}
			}

		}
		ui->tableWidget->insertRow(i); //dodanie kolejnego wiersza


	}
	ui->progressBar->setValue(60); //zwiekszenie pasku postepu do 60%

	if (wereheaders == 1)//petla wypelniajaca tabele, jesli naglowki byly w pliku
	{
		for (int i = 0; i < data_from_file.data.size() - 1; ++i)
		{
			for (int j = 0; j < data_from_file.data[i].size(); ++j)
			{
				QTableWidgetItem* elementwiersza = new QTableWidgetItem; //tworzenie elementu wiersza
				elementwiersza->setText(QString::number(data_from_file.data[i + 1][j])); // ustawienie elementu wiersza na dana z pliku
				ui->tableWidget->setItem(i, j, elementwiersza);  //wpisanie danej  do wiersza
			}
		}
	}
	else //petla wypelniajaca tabele, jesli naglowkow nie bylo w pliku
	{
		for (int i = 0; i < data_from_file.data.size(); ++i)
		{
			for (int j = 0; j < data_from_file.data[i].size(); ++j)
			{
				QTableWidgetItem* elementwiersza = new QTableWidgetItem; //tworzenie elementu wiersza
				elementwiersza->setText(QString::number(data_from_file.data[i][j])); // ustawienie elementu wiersza na dana z pliku
				ui->tableWidget->setItem(i, j, elementwiersza);  //wpisanie danej  do wiersza
			}
		}

	}



	ui->progressBar->setValue(90); // ustawienie pasku postepu na 90%


	file.close(); // zamkniecie pliku
	ui->progressBar->setValue(100); //ustawienie pasku postepu na 100%

}

//========================================================================================================================================
void MainWindow::on_action_Otw_rz_triggered()
{
	on_otworz_triggered();  //wywolanie funkcji w przypadku klikniecia w opcje "Otworz" w menu
}

//========================================================================================================================================
void MainWindow::on_analiza_triggered()
{
	ui->tableWidget_2->setRowCount(0);   //wyzerowanie zawartosci tabeli
	ui->progressBar->setValue(0);         //wyzerowanie pasku progress 
	data_results = control.analyze(data_from_file); //uruchomienie funkcji analizy danych
	int size_min = data_results.min.size();  //przypisanie wielkosci wektora w celu uzyskania koniecznej ilosci kolumn tabeli
	ui->tableWidget_2->setColumnCount(size_min); //ustawienie ilosci kolumn
	QStringList labels;


	for (int i = 0; i < 4; ++i)
	{

		for (int j = 0; j < data_results.min.size(); ++j) //pętle tworzące nagłówki dla tabeli
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
		ui->tableWidget_2->insertRow(i); //wstawienie wiersza

	}
	ui->progressBar->setValue(60); // zwiekszenie wartosci paska postępu

	for (int i = 0; i < data_results.min.size(); ++i) //wypisanie vektora minow
	{
		QTableWidgetItem* elementwiersza = new QTableWidgetItem;
		elementwiersza->setText(QString::number(data_results.min[i]));
		ui->tableWidget_2->setItem(0, i, elementwiersza);

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


void MainWindow::on_Zapis_triggered()   //funkcja zapis dziala jak zapisz jako jezeli wczesniej nie zapisano pliku,a  przy pustej nazwie pliku zapis nie jest dokonywany
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
	on_Zapis_triggered();      //wywolanie funckji zapisu w przypadku klikniecia w opcje zapisu w menu
}
//========================================================================================================================================
void MainWindow::on_Zapiszjako_triggered()
{

	fileName = QFileDialog::getSaveFileName(this,
		tr("Zapisz jako"), "",
		tr("Analiza (*.hgw);;Wszystkie pliki (*)"));//otwarcie okna z wyborem sciezki




	setWindowTitle(fileName);


	if (fileName.toStdString() == "")
	{
		ui->textBrowser->append(QTime::currentTime().toString("hh:mm:ss") + " BŁĄD! Nie można zapisać pliku bez nazwy.");
	}
	else {
		std::string file_name = fileName.toStdString();
		control.save_file(data_results, file_name);
		zapisano = 1; //zmiana flagi na 1, teraz mozna kliknac zapis i zapisze w podanym poprzednio pliku 
		ui->textBrowser->append(QTime::currentTime().toString("hh:mm:ss") + " " + "Zapisano plik w lokalizacji: " + fileName); // wypisanie w logu 
	}

}

//========================================================================================================================================

void MainWindow::on_action_Zapisz_jako_triggered() //wywolanie funckji zapisu w przypadku klikniecia w opcje zapisu w menu
{
	on_Zapiszjako_triggered();
}

//=========================================================================================================================================

void MainWindow::on_Wykres_triggered()
{
	//chart = new Chart(this);     
	QMessageBox::information(this, tr("Komunikat"), tr("Tu wyświetli się wykres"));

}

void MainWindow::on_Histogram_triggered()
{
	QMessageBox::information(this, tr("Komunikat"), tr("Tu wyświetli się histogram"));

}
