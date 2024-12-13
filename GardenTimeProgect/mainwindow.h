#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QCalendarWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow( QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDateClicked(const QDate &date);
    void showTasks();
    void showEvents();
    void showCatalog();
    void showHelp();

private:
    void setupDatabase();
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QCalendarWidget *calendar;
    QPushButton *tasksButton;
    QPushButton *eventsButton;
    QPushButton *catalogButton;
    QPushButton *helpButton;
    QString loggedInUser;
};

#endif // MAINWINDOW_H

