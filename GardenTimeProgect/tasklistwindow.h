#ifndef TASKLISTWINDOW_H
#define TASKLISTWINDOW_H

#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include <QString>
#include <QToolBar>

class TaskListWindow : public QDialog {
    Q_OBJECT

public:
    explicit TaskListWindow(const QString &type, QWidget *parent = nullptr);

private slots:
    void loadTasks();
    void deleteTask();
    void editTask();
    void saveToFile();

private:
    int getSelectedTaskId();
    QToolBar *toolBar;
    QAction *saveToFileAction;
    QString taskType;
    QTableWidget *taskTable;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *closeButton;
};

#endif // TASKLISTWINDOW_H
