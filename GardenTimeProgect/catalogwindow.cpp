#include "catalogwindow.h"
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QLineEdit>

CatalogWindow::CatalogWindow(QWidget *parent)
    : QDialog(parent), plantList(new QListWidget(this)), plantInfo(new QTextBrowser(this)) {
    setWindowTitle("Каталог растений");

    resize(300, 310);
    plantList->setMinimumSize(240, 110);

    // Строка поиска
    QLineEdit *searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Поиск...");

    // Добавление элементов с иконками
    addPlant("Роза", ":/img/img/rose.png");
    addPlant("Подсолнух", ":/img/img/sunflower.png");
    addPlant("Кактус", ":/img/img/cactus.png");
    addPlant("Вишня", ":/img/img/cherry.png");
    addPlant("Малина", ":/img/img/raspberry.png");
    addPlant("Клубника", ":/img/img/strawberry.png");
    addPlant("Виноград", ":/img/img/grapes.png");
    addPlant("Персик", ":/img/img/peach.png");
    addPlant("Яблоко", ":/img/img/apple.png");
    addPlant("Киви", ":/img/img/kiwi.png");
    addPlant("Груша", ":/img/img/pear.png");
    addPlant("Слива", ":/img/img/plum.png");
    addPlant("Кукуруза", ":/img/img/corn.png");
    addPlant("Редиска", ":/img/img/radish.png");
    addPlant("Свекла", ":/img/img/beet.png");
    addPlant("Морковь", ":/img/img/carrot.png");
    addPlant("Томат", ":/img/img/tomato.png");
    addPlant("Авокадо", ":/img/img/avocado.png");
    addPlant("Капуста", ":/img/img/cabbage.png");
    addPlant("Лук", ":/img/img/onion.png");
    addPlant("Баклажан", ":/img/img/eggplant.png");
    addPlant("Балгарский перец", ":/img/img/paprika.png");
    addPlant("Огурец", ":/img/img/cucumber.png");
    addPlant("Картошка", ":/img/img/potato.png");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(searchBar);
    layout->addWidget(plantList, 1);
    layout->addWidget(plantInfo, 2);

    connect(searchBar, &QLineEdit::textChanged, this, &CatalogWindow::filterPlants);
    connect(plantList, &QListWidget::itemClicked, this, &CatalogWindow::displayPlantInfo);
}

void CatalogWindow::addPlant(const QString &name, const QString &iconPath) {
    QListWidgetItem *item = new QListWidgetItem(QIcon(iconPath), name);
    plantList->addItem(item);
}

void CatalogWindow::filterPlants(const QString &text) {
    // Если текст пустой, показываем все элементы
    if (text.isEmpty()) {
        for (int i = 0; i < plantList->count(); ++i) {
            plantList->item(i)->setHidden(false);
        }
        return;
    }

    // Фильтруем элементы списка
    for (int i = 0; i < plantList->count(); ++i) {
        QListWidgetItem *item = plantList->item(i);
        // Проверяем, содержится ли текст как последовательность символов
        if (item->text().toLower().contains(text.toLower())) {
            item->setHidden(false); // Показываем подходящие элементы
        } else {
            item->setHidden(true); // Скрываем остальные
        }
    }
}

void CatalogWindow::displayPlantInfo() {
    QString plantName = plantList->currentItem()->text();
    QString info;

    if (plantName == "Томат") {
        info = "Томат: Требует много солнца и регулярного полива.\n"
               "Рекомендуется высаживать в защищенных от ветра местах.";
    } else if (plantName == "Огурец") {
        info = "Огурец: Предпочитает рыхлую, плодородную почву.\n"
               "Полив следует осуществлять теплой водой.";
    } else if (plantName == "Роза") {
        info = "Роза: Любит солнечные места и умеренный полив.\n"
               "Почву следует регулярно удобрять.";
    } else if (plantName == "Яблоко") {
        info = "Яблоня: Дерево, которое требует обрезки и регулярного ухода.\n"
               "Рекомендуется высаживать весной.";
    } else if (plantName == "Кактус") {
        info = "Кактус: Любит солнечные места и умеренный полив.\n"
               "Почву следует регулярно удобрять.";
    } else if (plantName == "Авокадо") {
        info = "Авокадо: Дерево, которое требует обрезки и регулярного ухода.\n"
               "Рекомендуется высаживать весной.";
    } else if (plantName == "Персик") {
        info = "Персик: Любит солнечные места и умеренный полив.\n"
               "Почву следует регулярно удобрять.";
    } else if (plantName == "Слива") {
        info = "Слива: Дерево, которое требует обрезки и регулярного ухода.\n"
               "Рекомендуется высаживать весной.";
    } else if (plantName == "Клубника") {
        info = "Клубника: Любит солнечные места и умеренный полив.\n"
               "Почву следует регулярно удобрять.";
    } else if (plantName == "Малина") {
        info = "Малина: Дерево, которое требует обрезки и регулярного ухода.\n"
               "Рекомендуется высаживать весной.";
    } else if (plantName == "Виноград") {
        info = "Виноград: Любит солнечные места и умеренный полив.\n"
               "Почву следует регулярно удобрять.";
    } else if (plantName == "Картошка") {
        info = "Картошка: Дерево, которое требует обрезки и регулярного ухода.\n"
               "Рекомендуется высаживать весной.";
    } else if (plantName == "Капуста") {
        info = "Капуста: Любит солнечные места и умеренный полив.\n"
               "Почву следует регулярно удобрять.";
    } else if (plantName == "Баклажан") {
        info = "Баклажан: Дерево, которое требует обрезки и регулярного ухода.\n"
               "Рекомендуется высаживать весной.";
    } else if (plantName == "Редиска") {
        info = "Редиска: Любит солнечные места и умеренный полив.\n"
               "Почву следует регулярно удобрять.";
    } else if (plantName == "Свекла") {
        info = "Свекла: Дерево, которое требует обрезки и регулярного ухода.\n"
               "Рекомендуется высаживать весной.";
    } else if (plantName == "Подсолнух") {
        info = "Подсолнух: Любит солнечные места и умеренный полив.\n"
               "Почву следует регулярно удобрять.";
    } else if (plantName == "Балгарский перец") {
        info = "Роза: Любит солнечные места и умеренный полив.\n"
               "Почву следует регулярно удобрять.";
    } else if (plantName == "Лук") {
        info = "Яблоня: Дерево, которое требует обрезки и регулярного ухода.\n"
               "Рекомендуется высаживать весной.";
    } else if (plantName == "Кукуруза") {
        info = "Роза: Любит солнечные места и умеренный полив.\n"
               "Почву следует регулярно удобрять.";
    } else if (plantName == "Слива") {
        info = "Яблоня: Дерево, которое требует обрезки и регулярного ухода.\n"
               "Рекомендуется высаживать весной.";
    } else if (plantName == "Вишня") {
        info = "Роза: Любит солнечные места и умеренный полив.\n"
               "Почву следует регулярно удобрять.";
    } else if (plantName == "Груша") {
        info = "Яблоня: Дерево, которое требует обрезки и регулярного ухода.\n"
               "Рекомендуется высаживать весной.";
    } else if (plantName == "Киви") {
        info = "Роза: Любит солнечные места и умеренный полив.\n"
               "Почву следует регулярно удобрять.";
    } else if (plantName == "Морковь") {
        info = "Яблоня: Дерево, которое требует обрезки и регулярного ухода.\n"
               "Рекомендуется высаживать весной.";
    }

    plantInfo->setText(info);
}
