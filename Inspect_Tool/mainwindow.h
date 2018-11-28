#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDir>
#include <vector>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QColorDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void test_func(QTreeWidgetItem *item, QString path);

    void optimized_func(QTreeWidgetItem *item, QString path);

    bool check_repeats(QTreeWidgetItem *item, QString new_name);



private slots:

    void on_treeWidget_itemExpanded(QTreeWidgetItem *item);

    void on_comboBox_activated(const QString &arg1);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_Highlight_button_clicked();

    void on_AddGroup_button_clicked();

    void on_AddControl_button_clicked();

    void on_RemoveGroupControl_button_clicked();

    void on_treeWidget_itemCollapsed(QTreeWidgetItem *item);

    void on_actionAdd_Group_triggered();

    void on_actionAdd_Control_triggered();

    void on_actionRemove_Group_Control_triggered();

    void on_actionHiglight_triggered();

    void on_actionCreator_s_Info_triggered();

    void on_actionChange_Highlight_Color_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;

    int count_groups = 1;
    int count_control = 1;

    QColor color;

    void keyPressEvent(QKeyEvent *event);

    void mousePressEvent (QMouseEvent *av);
};

#endif // MAINWINDOW_H
