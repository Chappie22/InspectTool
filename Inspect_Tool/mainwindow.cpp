#include "mainwindow.h"
#include "ui_mainwindow.h"


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDir dir;

    foreach (QFileInfo var, dir.drives())
    {
        ui->comboBox->addItem(var.absoluteFilePath());
    }

    this->color.setRgb(170,5,0);
}

void MainWindow::mousePressEvent(QMouseEvent *av)
{
    QCursor cursor;
    cursor.setShape(Qt::CursorShape::ArrowCursor);
    setCursor(cursor);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        QCursor cursor;
        cursor.setShape(Qt::CursorShape::ArrowCursor);
        setCursor(cursor);
    }
}

bool MainWindow::check_repeats (QTreeWidgetItem *item, QString new_name)
{
    QDir dir(item->text(1));

    foreach (QFileInfo var, dir.entryInfoList(QDir::AllEntries, QDir::DirsFirst))
    {
        if (var.fileName() == new_name) return true;
    }
    return  false;
}

void MainWindow::optimized_func(QTreeWidgetItem *item, QString path)
{
    QDir dir(path);
    int a = 0;

    if (item->childCount() != 0)
         foreach(auto i, item->takeChildren()) delete i;

    foreach (QFileInfo var, dir.entryInfoList(QDir::AllEntries, QDir::DirsFirst))
    {
        if (a == 0) a++;
        else if (a == 1) a++;
        else
        {
            QTreeWidgetItem *n_itm = new QTreeWidgetItem(item);
            n_itm ->setText(0, var.fileName());
            n_itm->setText(1, var.absoluteFilePath());
            n_itm->setIcon(0, QIcon(":/new/Icons/Icons/file.png"));
            if (var.isExecutable())
            {
                n_itm->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
                n_itm->setIcon(0, QIcon(":/new/Icons/Icons/closed folder.png"));
            }
        }
    }
}

void MainWindow::test_func(QTreeWidgetItem *parent_itm, QString path)
{
        QDir dir(path);
    foreach (QFileInfo var, dir.entryInfoList()) {
        if (!(var.isFile()))
        {
            //Folder
             if (QDir(var.absoluteFilePath()).count() == 0 || var.absoluteFilePath() == "/.." || var.absoluteFilePath() == "/")
             {
                 QMessageBox::warning(this, " ", "empty");
             }
             else
             {
                 QTreeWidgetItem *itm = new QTreeWidgetItem(parent_itm);
                 itm->setText(0, var.fileName());
                 this->test_func(itm,var.absoluteFilePath());
             }
        }
        else if (var.isFile())
        {
            //File
            QTreeWidgetItem *itm = new QTreeWidgetItem(parent_itm);
            itm->setText(0, var.fileName());
        }
        else break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeWidget_itemExpanded(QTreeWidgetItem *item)
{
    QString path = item->text(1);
    item->setIcon(0, QIcon(":/new/Icons/Icons/opn_folder.png"));
    this->optimized_func(item, path);
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
        item->setText(0, arg1);
        item->setText(1, arg1);
        item->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int a)
{
    //setCursor()
    ui->statusBar->showMessage(item->text(1));
}

void MainWindow::on_Highlight_button_clicked()
{

   QList <QTreeWidgetItem *> all = ui->treeWidget->selectedItems();

   for (auto iter = all.begin(); iter != all.end(); iter.operator++())
   {
      QTreeWidgetItem *wow = *iter;
      wow->setBackgroundColor(0, color);
   }
}

void MainWindow::on_AddGroup_button_clicked()
{
    if (ui->treeWidget->selectedItems().size() == 0)
    {
          QMessageBox::warning(this, " ", "Please, select the way, where you want to create a group..");
    }
    else
    {
        QList <QTreeWidgetItem *> all = ui->treeWidget->selectedItems();
        QTreeWidgetItem *parent;
        for (auto iter = all.begin(); iter != all.end(); iter.operator++())
        {
            parent = *iter;
        }
        if (QFileInfo(QFile(parent->text(1))).isFile())
        {
             QMessageBox::warning(this, " ", "Please, select the group, not a file");
        }
        else
        {
            QString num = QString::fromStdString(to_string(count_groups));

            while (this->check_repeats(parent,"Group "+ num))
            {
                count_groups++;
                num =  QString::fromStdString(to_string(count_groups));
            }


            QDir(parent->text(1)).mkdir("Group "+ num);
            QTreeWidgetItem *item = new QTreeWidgetItem(parent);
                item->setText(0, "Group "+ num);
                item->setText(1, parent->text(1) + "/Group "+ num);
                item->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
                count_groups++;
        }
    }


}

void MainWindow::on_AddControl_button_clicked()
{
    if (ui->treeWidget->selectedItems().size() == 0)
    {
          QMessageBox::warning(this, " ", "Please, select the way, where you want to create a control..");
    }
    else
    {
        QList <QTreeWidgetItem *> all = ui->treeWidget->selectedItems();
        QTreeWidgetItem *parent;
        for (auto iter = all.begin(); iter != all.end(); iter.operator++())
        {
            parent = *iter;
        }
        if (QFileInfo(QFile(parent->text(1))).isFile())
        {
             QMessageBox::warning(this, " ", "Please, select the group, not a file");
        }
        else
        {
            QString num = QString::fromStdString(to_string(count_control));
            while (this->check_repeats(parent,"Control "+ num))
            {
                count_control++;
                num =  QString::fromStdString(to_string(count_control));
            }

             QFile file (parent->text(1) + "/Control "+ num);
             file.open(QIODevice::ReadWrite);

             QTreeWidgetItem *item = new QTreeWidgetItem(parent);
                 item->setText(0, "Control "+ num);
                 item->setText(1, parent->text(1) + "/Control "+ num);
                 count_control++;
             file.close();

             QCursor cursor;
             cursor.setShape(Qt::CursorShape::CrossCursor);
             setCursor(cursor);
        }
    }
}

void MainWindow::on_RemoveGroupControl_button_clicked()
{
    if (ui->treeWidget->selectedItems().size() == 0)
    {
          QMessageBox::warning(this, " ", "Please, select the item, you wanr to delete..");
    }
    else
    {
        QList <QTreeWidgetItem *> all = ui->treeWidget->selectedItems();
        QTreeWidgetItem *parent;
        for (auto iter = all.begin(); iter != all.end(); iter.operator++())
        {
            parent = *iter;
        }

        if (QFileInfo(QFile(parent->text(1))).isFile())
        {
            QMessageBox::StandardButton reply = QMessageBox::question(this, " ",
                                                                      "Are you sure to delete " + parent->text(0) + "?"
                                                                      ,QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                QFile file(parent->text(1));
                int a = file.remove();
                if (a)
                {
                    QMessageBox::information(this, "", "Deleted");
                    this->on_treeWidget_itemExpanded(parent->parent());
                }
                else QMessageBox::information(this, "", "Error occurred");
            }
            else return;
        }
        else
        {
            QDir dir(parent->text(1));
               if (dir.isEmpty())
               {
                   QMessageBox::StandardButton reply = QMessageBox::question(this, " ",
                                                                             "This folder nothing contains\n"
                                                                             "Are you sure to delete " + parent->text(0) + "?"
                                                                             ,QMessageBox::Yes | QMessageBox::No);
                   if (reply == QMessageBox::Yes)
                   {
                       bool a = dir.removeRecursively();
                       if (a)
                       {
                           QMessageBox::information(this, "", "Deleted");
                           this->on_treeWidget_itemExpanded(parent->parent());
                       }
                       else QMessageBox::information(this, "", "Error occurred");
                   }
                   else return;

               }
               else
               {
                   QMessageBox::StandardButton reply = QMessageBox::question(this, " ",
                                                                             "This folder contains elements\n"
                                                                             "Are you sure to delete all?"
                                                                             ,QMessageBox::Yes | QMessageBox::No);
                   if (reply == QMessageBox::Yes)
                   {
                         bool a = dir.removeRecursively();
                         if (a)
                         {
                             QMessageBox::information(this, "", "Deleted");
                             this->on_treeWidget_itemExpanded(parent->parent());
                         }
                         else QMessageBox::information(this, "", "Error occurred");
                   }
                   else return;
               }
        }
    }

}

void MainWindow::on_treeWidget_itemCollapsed(QTreeWidgetItem *item)
{
   item->setIcon(0, QIcon(":/new/Icons/Icons/closed folder.png"));
}

void MainWindow::on_actionAdd_Group_triggered()
{
    this->on_AddGroup_button_clicked();
}

void MainWindow::on_actionAdd_Control_triggered()
{
    this->on_AddControl_button_clicked();
}

void MainWindow::on_actionRemove_Group_Control_triggered()
{
    this->on_RemoveGroupControl_button_clicked();
}

void MainWindow::on_actionHiglight_triggered()
{
    this->on_Highlight_button_clicked();
}

void MainWindow::on_actionCreator_s_Info_triggered()
{
    QMessageBox::information(this, "Creator`s info", "My name: Kirill Kryklyviy Ureyovich;"
                                                     "\nAge = 16 y.o;"
                                                     "\nSpended timme ~ 6 hours;"
                                                     "\nMy phone: +380985258193;"
                                                     "\nThanks for using it :)");
}

void MainWindow::on_actionChange_Highlight_Color_triggered()
{
    color = QColorDialog::getColor();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}
