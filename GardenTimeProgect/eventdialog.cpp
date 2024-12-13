#include "eventdialog.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlQuery>

EventDialog::EventDialog(const QDate &date, QWidget *parent)
    : QDialog(parent), eventDate(date) {
    setupUI();
    resize(280, 240);
}

void EventDialog::setupUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    typeComboBox = new QComboBox(this);
    typeComboBox->addItems({"Задача", "Событие"});

    descriptionEdit = new QTextEdit(this);

    saveButton = new QPushButton("Сохранить", this);
    cancelButton = new QPushButton("Отмена", this);

    layout->addWidget(typeComboBox);
    layout->addWidget(descriptionEdit);
    layout->addWidget(saveButton);
    layout->addWidget(cancelButton);

    connect(saveButton, &QPushButton::clicked, this, &EventDialog::saveEvent);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void EventDialog::saveEvent() {
    QString type = typeComboBox->currentText();
    QString description = descriptionEdit->toPlainText().trimmed();
    QString dateString = eventDate.toString("yyyy-MM-dd");

    // Проверка: описание не должно быть пустым
    if (description.isEmpty()) {
        if (type == "Задача")
            QMessageBox::warning(this, "Ошибка", "Описание задачи не может быть пустым.");
        else
            QMessageBox::warning(this, "Ошибка", "Описание события не может быть пустым.");
        return;
    }

    // (Дополнительно) Проверка: длина описания
    if (description.length() < 3) {
        QMessageBox::warning(this, "Ошибка", "Описание должно содержать не менее 3 символов.");
        return;
    }

    // (Опционально) Проверка: дата не должна быть в прошлом
    if (eventDate < QDate::currentDate()) {
        if (type == "Задача")
            QMessageBox::warning(this, "Ошибка", "Дата задачи не может быть в прошлом.");
        else
            QMessageBox::warning(this, "Ошибка", "Дата события не может быть в прошлом.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO tasks (date, type, description) "
                  "VALUES (:date, :type, :description)");
    query.bindValue(":date", dateString);
    query.bindValue(":type", type);
    query.bindValue(":description", description);

    if (query.exec()) {
        accept();
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить данные в базу.");
        reject();
    }
}
