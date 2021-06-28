#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDir>
#include <QFileSystemModel>
#include <QListView>
#include <QTreeView>

QT_BEGIN_NAMESPACE
namespace uui {class Dialog;}
QT_END_NAMESPACE

class Dialog : public QDialog
{
  Q_OBJECT

  public:
  Dialog(QWidget *parent =nullptr);
  ~Dialog();


private:
  uui::Dialog  *ui;
  QDir dir;

  QFileSystemModel model;
  void init();
};

#endif // DIALOG_H
