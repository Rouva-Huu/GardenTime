#include "mainwindow.h"
#include "eventdialog.h"
#include "tasklistwindow.h"
#include "catalogwindow.h"

#include <QHBoxLayout>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), calendar(new QCalendarWidget(this)),
    tasksButton(new QPushButton("Задачи", this)),
    eventsButton(new QPushButton("События", this)),
    catalogButton(new QPushButton("Каталог", this)) {

    // Настройка базы данных
    setupDatabase();

    // Настройка интерфейса
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Вертикальный layout для кнопок
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->addWidget(tasksButton);
    buttonLayout->addWidget(eventsButton);
    buttonLayout->addStretch(); // Отступ снизу для выравнивания кнопок
    buttonLayout->addWidget(catalogButton); // Добавление кнопки "Каталог"

    // Добавляем кнопки слева, календарь справа
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(calendar);

    connect(calendar, &QCalendarWidget::clicked, this, &MainWindow::onDateClicked);
    connect(tasksButton, &QPushButton::clicked, this, &MainWindow::showTasks);
    connect(eventsButton, &QPushButton::clicked, this, &MainWindow::showEvents);
    connect(catalogButton, &QPushButton::clicked, this, &MainWindow::showCatalog);

    resize(540, 340);
    setCentralWidget(centralWidget);
    setWindowTitle("Garden Time");
    setWindowIcon(QIcon(":/img/img/icon2.png"));
    QToolButton* left = centralWidget->findChild<QToolButton*>("qt_calendar_prevmonth");
    QToolButton* right = centralWidget->findChild<QToolButton*>("qt_calendar_nextmonth");
    QToolButton* bottom = centralWidget->findChild<QToolButton*>("qt_calendar_monthbutton");
    left->setIcon(QIcon(":/img/img/arrow_left.png"));
    right->setIcon(QIcon(":/img/img/arrow_right.png"));
    bottom->setIcon(QIcon());
}

MainWindow::~MainWindow() {}

void MainWindow::setupDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("gardener_calendar.db");

    if (!db.open()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть базу данных.");
        return;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS tasks ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "date TEXT, "
               "type TEXT, "
               "description TEXT)");
}

void MainWindow::onDateClicked(const QDate &date) {
    EventDialog dialog(date, this);
    dialog.exec();
}

void MainWindow::showTasks() {
    TaskListWindow taskWindow("tasks", this);
    taskWindow.exec();
}

void MainWindow::showEvents() {
    TaskListWindow eventWindow("events", this);
    eventWindow.exec();
}

void MainWindow::showCatalog() {
    CatalogWindow catalogWindow(this); // Открытие окна каталога
    catalogWindow.exec();
}
