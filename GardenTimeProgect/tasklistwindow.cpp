#include "tasklistwindow.h"
#include "eventdialog.h"
#include <QDateTimeEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlQuery>
#include <QHeaderView>
#include <QMenu>
#include <QToolBar>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

TaskListWindow::TaskListWindow(const QString &type, const QString &username, QWidget *parent)
    : QDialog(parent), taskType(type), currentUser(username), taskTable(new QTableWidget(this)),
    editButton(new QPushButton("Редактировать", this)),
    deleteButton(new QPushButton("Удалить", this)),
    closeButton(new QPushButton("Закрыть", this)) {

    setWindowTitle(type == "tasks" ? "Список задач" : "Список событий");

    // Инициализация QToolBar
    toolBar = new QToolBar(this);
    saveToFileAction = new QAction("Сохранить в файл", this);

    saveToFileAction->setShortcut(QKeySequence("Ctrl+S"));
    saveToFileAction->setToolTip("Сохранить список задач или событий в файл");

    // Добавляем QAction в QToolBar
    toolBar->addAction(saveToFileAction);

    // Связываем QAction с обработчиком
    connect(saveToFileAction, &QAction::triggered, this, &TaskListWindow::saveToFile);

    // Layout для окна
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Настройка таблицы
    taskTable->setColumnCount(3);
    taskTable->setHorizontalHeaderLabels({"ID", "Дата", "Описание"});
    taskTable->horizontalHeader()->setStretchLastSection(true);
    taskTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    taskTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    taskTable->setSelectionMode(QAbstractItemView::SingleSelection);
    taskTable->hideColumn(0); // Скрываем колонку с ID

    // Кнопки управления
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(closeButton);

    // Добавление элементов в layout
    layout->addWidget(toolBar); // Добавляем QToolBar
    layout->addWidget(taskTable);
    layout->addLayout(buttonLayout);

    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(deleteButton, &QPushButton::clicked, this, &TaskListWindow::deleteTask);
    connect(editButton, &QPushButton::clicked, this, &TaskListWindow::editTask);

    loadTasks();
}

void TaskListWindow::loadTasks() {
    QSqlQuery query;
    query.prepare("SELECT id, date, description FROM tasks WHERE type = :type AND username = :username ORDER BY date ASC");
    query.bindValue(":type", taskType == "tasks" ? "Задача" : "Событие");
    query.bindValue(":username", currentUser);

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить данные из базы данных.");
        return;
    }

    taskTable->setRowCount(0);
    int row = 0;

    while (query.next()) {
        taskTable->insertRow(row);

        QTableWidgetItem *idItem = new QTableWidgetItem(query.value("id").toString());
        QTableWidgetItem *dateItem = new QTableWidgetItem(query.value("date").toString());
        QTableWidgetItem *descriptionItem = new QTableWidgetItem(query.value("description").toString());

        taskTable->setItem(row, 0, idItem);
        taskTable->setItem(row, 1, dateItem);
        taskTable->setItem(row, 2, descriptionItem);

        row++;
    }
}

int TaskListWindow::getSelectedTaskId() {
    QString taskTypeString = taskType == "tasks" ? "Задача" : "Событие";
    int row = taskTable->currentRow();
    if (row < 0) {
        if (taskTypeString == "Задача")
            QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите задачу.");
        else
            QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите событие.");
        return -1;
    }

    QTableWidgetItem *idItem = taskTable->item(row, 0);
    return idItem ? idItem->text().toInt() : -1;
}

void TaskListWindow::deleteTask() {
    int taskId = getSelectedTaskId();
    if (taskId == -1)
        return;

    // Определяем тип задачи (задача или событие)
    QString taskTypeString = taskType == "tasks" ? "Задача" : "Событие";

    // Запрашиваем удаление
    QSqlQuery query;
    query.prepare("DELETE FROM tasks WHERE id = :id");
    query.bindValue(":id", taskId);

    if (!query.exec()) {
        if (taskTypeString == "Задача")
            QMessageBox::critical(this, "Ошибка", "Не удалось удалить задачу.");
        else
            QMessageBox::critical(this, "Ошибка", "Не удалось удалить событие.");
        return;
    }

    loadTasks();
    if (taskTypeString == "Задача")
        QMessageBox::information(this, "Успех", taskTypeString + " успешно удалена.");
    else
        QMessageBox::information(this, "Успех", taskTypeString + " успешно удалено.");
}

void TaskListWindow::editTask() {
    int taskId = getSelectedTaskId(); // Получение ID выбранной задачи/события
    QString taskTypeString = taskType == "tasks" ? "Задача" : "Событие";
    if (taskId == -1) {
        if (taskTypeString == "Задача")
            QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите задачу для редактирования.");
        else
            QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите событие для редактирования.");
        return;
    }

    // Загружаем данные выбранной записи из базы
    QSqlQuery query;
    query.prepare("SELECT date, type, description FROM tasks WHERE id = :id");
    query.bindValue(":id", taskId);

    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить данные для редактирования.");
        return;
    }

    // Извлекаем текущие данные из базы
    QDate date = QDate::fromString(query.value("date").toString(), "yyyy-MM-dd");
    QString type = query.value("type").toString();
    QString description = query.value("description").toString();

    // Открываем диалог редактирования
    EventDialog dialog(date, currentUser,this);
    if (taskTypeString == "Задача")
        dialog.setWindowTitle("Редактировать задачу");
    else
        dialog.setWindowTitle("Редактировать событие");

    // Заполняем диалог текущими данными
    dialog.findChild<QComboBox *>()->setCurrentText(type);
    dialog.findChild<QTextEdit *>()->setText(description);

    // Если пользователь подтвердил изменения
    if (dialog.exec() == QDialog::Accepted) {
        // Извлекаем новые значения
        QString newType = dialog.findChild<QComboBox *>()->currentText();
        QString newDescription = dialog.findChild<QTextEdit *>()->toPlainText();

        if (newDescription.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Описание задачи/события не может быть пустым.");
            return;
        }

        if (newDescription.length() < 3) {
            QMessageBox::warning(this, "Ошибка", "Описание должно содержать не менее 3 символов.");
            return;
        }

        // Выполняем обновление записи в базе данных
        QSqlQuery updateQuery;
        updateQuery.prepare(
            "UPDATE tasks SET date = :date, type = :type, description = :description WHERE id = :id");
        updateQuery.bindValue(":id", taskId);
        updateQuery.bindValue(":date", date);
        updateQuery.bindValue(":type", newType);
        updateQuery.bindValue(":description", newDescription);

        // Проверка выполнения запроса
        if (!updateQuery.exec()) {
            QMessageBox::critical(this, "Ошибка", "Не удалось обновить данные.");
            return;
        }

        QSqlQuery deleteQuery;
        deleteQuery.prepare("DELETE FROM tasks WHERE id = :id");
        deleteQuery.bindValue(":id", taskId);

        if (!deleteQuery.exec()) {
            QMessageBox::critical(this, "Ошибка", "Не удалось удалить старую запись.");
            return;
        }

        // Перезагружаем список задач/событий
        loadTasks();
        if (taskTypeString == "Задача")
            QMessageBox::information(this, "Успех", taskTypeString + " успешно обновлена.");
        else
            QMessageBox::information(this, "Успех", taskTypeString + " успешно обновлено.");
    }
}

void TaskListWindow::saveToFile() {
    // Открываем диалог сохранения файла
    QString defaultFileName = (taskType == "tasks") ? "tasks.txt" : "events.txt";
    QString fileName = QFileDialog::getSaveFileName(
        this, "Сохранить файл", defaultFileName, "Text Files (*.txt);;All Files (*)");

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }

    QTextStream out(&file);
    out << (taskType == "tasks" ? "Список задач" : "Список событий") << "\n\n";

    for (int row = 0; row < taskTable->rowCount(); ++row) {
        QString date = taskTable->item(row, 1)->text();
        QString description = taskTable->item(row, 2)->text();
        out << "Дата: " << date << "\n";
        out << "Описание: " << description << "\n";
        out << "----------------------\n";
    }

    file.close();
    QMessageBox::information(this, "Успех", "Данные успешно сохранены в файл:\n" + fileName);
}
