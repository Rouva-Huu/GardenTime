#ifndef CATALOGWINDOW_H
#define CATALOGWINDOW_H

#include <QDialog>
#include <QListWidget>
#include <QTextBrowser>

class CatalogWindow : public QDialog {
    Q_OBJECT

public:
    CatalogWindow(QWidget *parent = nullptr);

private slots:
    void addPlant(const QString &name, const QString &iconPath);
    void displayPlantInfo();
    void filterPlants(const QString &text);

private:
    QListWidget *plantList;
    QTextBrowser *plantInfo;
};

#endif // CATALOGWINDOW_H
