#include "registerdialog.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlQuery>
#include <QCryptographicHash>

RegisterDialog::RegisterDialog(QSqlDatabase db, QWidget *parent)
    : QDialog(parent), db(db),
    usernameEdit(new QLineEdit(this)),
    passwordEdit(new QLineEdit(this)),
    confirmPasswordEdit(new QLineEdit(this)),
    registerButton(new QPushButton("Зарегистрироваться", this)) {

    passwordEdit->setEchoMode(QLineEdit::Password);
    confirmPasswordEdit->setEchoMode(QLineEdit::Password);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(usernameEdit);
    layout->addWidget(passwordEdit);
    layout->addWidget(confirmPasswordEdit);
    layout->addWidget(registerButton);

    connect(registerButton, &QPushButton::clicked, this, &RegisterDialog::onRegisterButtonClicked);

    setWindowTitle("Регистрация");
}

RegisterDialog::~RegisterDialog() {}

void RegisterDialog::onRegisterButtonClicked() {
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text().trimmed();
    QString confirmPassword = confirmPasswordEdit->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Логин и пароль не могут быть пустыми.");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Ошибка", "Пароли не совпадают.");
        return;
    }

    if (!db.isOpen()) {
        QMessageBox::critical(this, "Ошибка", "База данных пользователей не подключена.");
        return;
    }

    // Создаем таблицу users, если её нет
    QSqlQuery createTableQuery(db);
    if (!createTableQuery.exec(
            "CREATE TABLE IF NOT EXISTS users ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "username TEXT UNIQUE, "
            "password TEXT)")) {
        QMessageBox::critical(this, "Ошибка", "Не удалось создать таблицу пользователей.");
        return;
    }

    // Проверяем существование пользователя
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT COUNT(*) FROM users WHERE username = :username");
    checkQuery.bindValue(":username", username);
    if (!checkQuery.exec() || !checkQuery.next()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось проверить существование пользователя.");
        return;
    }

    if (checkQuery.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Ошибка", "Пользователь с таким логином уже существует.");
        return;
    }

    // Хешируем пароль и добавляем пользователя
    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
    QSqlQuery query(db);
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPassword);

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось зарегистрировать пользователя.");
        return;
    }

    QMessageBox::information(this, "Успех", "Пользователь успешно зарегистрирован.");
    accept();
}
