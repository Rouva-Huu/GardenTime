#ifndef EVENTDIALOG_H
#define EVENTDIALOG_H

#include <QDialog>
#include <QDate>
#include <QComboBox>
#include <QTextEdit>
#include <QPushButton>

class QDateEdit;
class QLineEdit;

class EventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EventDialog(const QDate &date, QWidget *parent = nullptr);

private slots:
    void saveEvent();

private:
    void setupUI();

    int currentUserId;
    QDate eventDate;
    QComboBox *typeComboBox;
    QTextEdit *descriptionEdit;
    QPushButton *saveButton;
    QPushButton *cancelButton;
};

#endif // EVENTDIALOG_H
