#include "logindialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QFile>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent), newUser(false) {
    setWindowTitle("Вход в систему");
    setWindowIcon(QIcon(":/img/img/user.png"));

    QFile file(":/qss/styles.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        setStyleSheet(styleSheet);
        file.close();
    }

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *usernameLabel = new QLabel("Имя пользователя:", this);
    usernameEdit = new QLineEdit(this);

    QLabel *passwordLabel = new QLabel("Пароль:", this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Войти", this);
    registerButton = new QPushButton("Регистрация", this);

    layout->addWidget(usernameLabel);
    layout->addWidget(usernameEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordEdit);
    layout->addWidget(loginButton);
    layout->addWidget(registerButton);

    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
    connect(registerButton, &QPushButton::clicked, this, &LoginDialog::onRegisterClicked);
}

QString LoginDialog::getUsername() const {
    return username;
}

bool LoginDialog::isNewUser() const {
    return newUser;
}

void LoginDialog::onLoginClicked() {
    QString inputUsername = usernameEdit->text().trimmed();
    QString inputPassword = passwordEdit->text();

    if (inputUsername.isEmpty() || inputPassword.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите имя пользователя и пароль.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE username = :username");
    query.bindValue(":username", inputUsername);

    if (query.exec() && query.next()) {
        QString storedPassword = query.value(0).toString();
        if (storedPassword == inputPassword) {
            username = inputUsername;
            accept();
        } else {
            QMessageBox::warning(this, "Ошибка", "Неверный пароль.");
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Пользователь не найден.");
    }
}

void LoginDialog::onRegisterClicked() {
    QString inputUsername = usernameEdit->text().trimmed();
    QString inputPassword = passwordEdit->text();

    if (inputUsername.isEmpty() || inputPassword.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите имя пользователя и пароль.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", inputUsername);
    query.bindValue(":password", inputPassword);

    if (query.exec()) {
        QMessageBox::information(this, "Успех", "Регистрация прошла успешно.");
        username = inputUsername;
        newUser = true;
        accept();
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось зарегистрировать пользователя.");
    }
}
