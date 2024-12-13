#include "mainwindow.h"
#include "eventdialog.h"
#include "tasklistwindow.h"
#include "catalogwindow.h"
#include "logindialog.h"

#include <QHBoxLayout>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QToolButton>
#include <QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), calendar(new QCalendarWidget(this)),
    tasksButton(new QPushButton("Задачи", this)),
    eventsButton(new QPushButton("События", this)),
    catalogButton(new QPushButton("Каталог", this)),
    helpButton(new QPushButton("Справка", this))  {
    QTextCharFormat format1 = calendar->weekdayTextFormat(Qt::Saturday);
    format1.setForeground(QBrush(Qt::white, Qt::SolidPattern));
    QTextCharFormat format2 = calendar->weekdayTextFormat(Qt::Sunday);
    format2.setForeground(QBrush(Qt::white, Qt::SolidPattern));

    calendar->setWeekdayTextFormat(Qt::Saturday, format1);
    calendar->setWeekdayTextFormat(Qt::Sunday, format2);

    setupDatabase();

    LoginDialog loginDialog(this);
    if (loginDialog.exec() == QDialog::Accepted) {
        loggedInUser = loginDialog.getUsername();
    } else {
        close();
        return;
    }
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->addWidget(tasksButton);
    buttonLayout->addWidget(eventsButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(catalogButton);
    buttonLayout->addWidget(helpButton);

    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(calendar);

    connect(calendar, &QCalendarWidget::clicked, this, &MainWindow::onDateClicked);
    connect(tasksButton, &QPushButton::clicked, this, &MainWindow::showTasks);
    connect(eventsButton, &QPushButton::clicked, this, &MainWindow::showEvents);
    connect(catalogButton, &QPushButton::clicked, this, &MainWindow::showCatalog);
    connect(helpButton, &QPushButton::clicked, this, &MainWindow::showHelp);

    resize(560, 360);
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
    query.exec("CREATE TABLE IF NOT EXISTS users ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "username TEXT UNIQUE, "
               "password TEXT)");

    query.exec("CREATE TABLE IF NOT EXISTS tasks ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "date TEXT, "
               "type TEXT, "
               "description TEXT, "
               "username TEXT)");
}
void MainWindow::onDateClicked(const QDate &date) {
    EventDialog dialog(date, loggedInUser, this);
    dialog.exec();
}

void MainWindow::showTasks() {
    TaskListWindow taskWindow("tasks", loggedInUser, this);
    taskWindow.exec();
}

void MainWindow::showEvents() {
    TaskListWindow eventWindow("events", loggedInUser, this);
    eventWindow.exec();
}

void MainWindow::showCatalog() {
    CatalogWindow catalogWindow(this);
    catalogWindow.exec();
}

void MainWindow::showHelp() {
    QDialog *helpDialog = new QDialog(this);
    helpDialog->setWindowTitle("Справка");
    helpDialog->resize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(helpDialog);

    QTextBrowser *textBrowser = new QTextBrowser(helpDialog);
    textBrowser->setHtml(R"(
        <style>
            body { padding: 6px; }
        </style>
        <h1>Справка</h1>
        <p>Добро пожаловать в приложение "Garden Time"! Здесь вы найдете руководство по основным функциям приложения и взаимодействию с его интерфейсом.</p>
        <hr style="border: 1px solid white;">
        <p><b>Содержание:</b></p>
        <ol>
            <li><a href="main_window">Главное окно</a></li>
            <li><a href="calendar">Календарь</a></li>
            <li><a href="tasks">Управление задачами</a></li>
            <li><a href="events">Управление событиями</a></li>
            <li><a href="catalog">Каталог</a></li>
            <li><a href="login">Вход и регистрация</a></li>
            <li><a href="export">Экспорт данных</a></li>
            <li><a href="errors">Общие ошибки и их решение</a></li>
        </ol>
    )");

    textBrowser->setOpenExternalLinks(false);  // Отключаем переход по внешним ссылкам
    connect(textBrowser, &QTextBrowser::anchorClicked, this, [textBrowser](const QUrl &url) {
        if (url.toString() == "main_window") {
            textBrowser->setHtml(R"(
                <h2>Главное окно</h2>
                <p><b>Главное окно состоит из следующих элементов:</b></p>
                <ul>
                    <li><b>Календарь:<b> отображает текущий месяц с возможностью переключения между месяцами.</li>
                    <li><b>Кнопки навигации:</b><ul>
                        <li>"Задачи": открыть список задач.</li>
                        <li>"События": открыть список событий.</li>
                        <li>"Каталог": открыть раздел с дополнительной информацией.</li>
                    </ul>
                </ul>
                <p>Для изменения месяца используйте кнопки со стрелками в верхней части календаря.</p>
                <p><a href="#">Назад</a></p>
            )");
        } else if (url.toString() == "calendar") {
            textBrowser->setHtml(R"(
                <h2>Календарь</h2>
                <p><b>Календарь позволяет:</b></p>
                <ul>
                    <li>Нажимать на дату, чтобы добавить новую задачу или событие.</li>
                    <li>Переключать месяцы с помощью кнопок со стрелками.</li>
                    <li>Просматривать задачи и события, связанные с определенной датой (при нажатии откроется диалоговое окно).</li>
                </ul>
                <p><a href="#">Назад</a></p>
            )");
        } else if (url.toString() == "tasks") {
            textBrowser->setHtml(R"(
                <h2>Управление задачами</h2>
                <p><b>Чтобы управлять задачами:</b></p>
                <ol>
                    <li>Нажмите кнопку "Задачи" в главном окне.</li>
                    <li>Откроется список задач, где вы можете:<ul>
                        <li>Редактировать задачу: выберите строку и нажмите кнопку "Редактировать".</li>
                        <li>Удалить задачу: выберите строку и нажмите кнопку "Удалить".</li>
                        <li>Сохранить список в файл: нажмите Ctrl+S или выберите соответствующий пункт в панели инструментов.</li>
                    </ul>
                </ol>
                <p><b>Каждая задача имеет следующие параметры:<b></p>
                <ul>
                    <li>Дата: дата выполнения задачи.</li>
                    <li>Описание: текстовое описание задачи.</li>
                </ul>
                <p><a href="#">Назад</a></p>
            )");
        } else if (url.toString() == "events") {
            textBrowser->setHtml(R"(
                <h2>Управление событиями</h2>
                <p><b>Список событий работает аналогично списку задач:</b></p>
                <ol>
                    <li>Нажмите кнопку "События" в главном окне.</li>
                    <li>В окне списка событий вы можете:</ul>
                        <li>Редактировать или удалять события.</li>
                        <li>Сохранить список событий в файл.</li>
                    </ul>
                </ol>
                <p><a href="#">Назад</a></p>
            )");
        } else if (url.toString() == "catalog") {
            textBrowser->setHtml(R"(
                <h2>Каталог растений</h2>
                <p>Каталог доступен через кнопку "Каталог". Он содержит дополнительную информацию о растениях и подсказки по уходу. Каталог откроется в отдельном диалоговом окне.</p>
                <p><a href="#">Назад</a></p>
            )");
        } else if (url.toString() == "login") {
            textBrowser->setHtml(R"(
                <h2>Вход и регистрация</h2>
                <p><b>Вход в систему</b></p>
                <ol>
                    <li>При первом запуске откроется окно авторизации.</li>
                    <li>Введите ваше имя пользователя и пароль.</li>
                    <li>Если учетные данные верны, вы будете авторизованы.</li>
                </ol>
                <p><b>Регистрация нового пользователя</b></p>
                <ol>
                    <li>Нажмите кнопку "Регистрация" в окне авторизации.</li>
                    <li>Введите имя пользователя и пароль.</li>
                    <li>После успешной регистрации вы сможете войти в систему.</li>
                </ol>
                <p><a href="#">Назад</a></p>
            )");
        } else if (url.toString() == "export") {
            textBrowser->setHtml(R"(
                <h2>Экспорт данных</h2>
                <p><b>Для экспорта задач или событий в файл:</b></p>
                <ol>
                    <li>Откройте окно задач или событий.</li>
                    <li>Нажмите Ctrl+S или выберите пункт "Сохранить в файл" в панели инструментов.</li>
                    <li>Укажите путь и имя файла для сохранения.</li>
                </ol>
                <p>Файл будет содержать список задач или событий с датами и описаниями.</p>
                <p><a href="#">Назад</a></p>
            )");
        } else if (url.toString() == "errors") {
            textBrowser->setHtml(R"(
                <h2>Общие ошибки и их решение</h2>
                <ol>
                    <li>Не удается войти в систему:<ul>
                        <li>Проверьте правильность введенных имени пользователя и пароля.</li>
                        <li>Убедитесь, что база данных доступна.</li>
                    </ul>
                    <li>Не удается сохранить задачу или событие:<ul>
                        <li>Убедитесь, что описание задачи/события заполнено и содержит не менее 3 символов.</li>
                        <li>Проверьте, что дата не находится в прошлом.</li>
                    </ul>
                    <li>Ошибка при экспорте файла:<ul>
                        <>Проверьте, что указанный путь доступен для записи.</li>
                    </ul>
                </ol>
                <p><a href="#">Назад</a></p>
            )");
        } else {
            textBrowser->setHtml(R"(
                <h1>Справка</h1>
                <p>Добро пожаловать в приложение "Garden Time"! Здесь вы найдете руководство по основным функциям приложения и взаимодействию с его интерфейсом.</p>
                <hr style="border: 1px solid white;">
                <p><b>Содержание:<b></p>
                <ul>
                    <li><a href="main_window">1. Главное окно</a></li>
                    <li><a href="calendar">2. Календарь</a></li>
                    <li><a href="tasks">3. Управление задачами</a></li>
                    <li><a href="events">4. Управление событиями</a></li>
                    <li><a href="catalog">5. Каталог</a></li>
                    <li><a href="login">6. Вход и регистрация</a></li>
                    <li><a href="export">7. Экспорт данных</a></li>
                    <li><a href="errors">8. Общие ошибки и их решение</a></li>
                </ul>
            )");
        }
    });

    layout->addWidget(textBrowser);
    helpDialog->setLayout(layout);
    helpDialog->exec();
}

