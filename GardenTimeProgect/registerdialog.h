#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QSqlDatabase>

class QLineEdit;
class QPushButton;

class RegisterDialog : public QDialog {
    Q_OBJECT

public:
    explicit RegisterDialog(QSqlDatabase db, QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void onRegisterButtonClicked();

private:
    QSqlDatabase db;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QLineEdit *confirmPasswordEdit;
    QPushButton *registerButton;
};

#endif // REGISTERDIALOG_H
