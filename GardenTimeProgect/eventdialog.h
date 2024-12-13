#ifndef EVENTDIALOG_H
#define EVENTDIALOG_H

#include <QDialog>
#include <QDate>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>

class EventDialog : public QDialog {
    Q_OBJECT

public:
    EventDialog(const QDate &date, const QString &username, QWidget *parent = nullptr);

private:
    void setupUI();
    void saveEvent();

    QDate eventDate;
    QString currentUser; // Поле для хранения имени пользователя

    QComboBox *typeComboBox;
    QTextEdit *descriptionEdit;
    QPushButton *saveButton;
    QPushButton *cancelButton;
};

#endif // EVENTDIALOG_H
