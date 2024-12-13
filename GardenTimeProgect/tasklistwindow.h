#ifndef TASKLISTWINDOW_H
#define TASKLISTWINDOW_H

#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include <QToolBar>
#include <QAction>

class TaskListWindow : public QDialog {
    Q_OBJECT

public:
    TaskListWindow(const QString &type, const QString &username, QWidget *parent = nullptr);

private slots:
    void loadTasks();
    void deleteTask();
    void editTask();
    void saveToFile();

private:
    int getSelectedTaskId();

    QString taskType;
    QString currentUser;
    QTableWidget *taskTable;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *closeButton;
    QToolBar *toolBar;
    QAction *saveToFileAction;
};

#endif // TASKLISTWINDOW_H
