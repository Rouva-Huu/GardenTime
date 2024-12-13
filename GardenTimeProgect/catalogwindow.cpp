#include "catalogwindow.h"
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QLineEdit>

CatalogWindow::CatalogWindow(QWidget *parent)
    : QDialog(parent), plantList(new QListWidget(this)), plantInfo(new QTextBrowser(this)) {
    setWindowTitle("Каталог растений");

    resize(400, 340);
    plantList->setMinimumSize(240, 110);

    // Строка поиска
    QLineEdit *searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Поиск...");

    // Добавление элементов с иконками
    addPlant("Роза", ":/img/img/rose.png");
    addPlant("Подсолнух", ":/img/img/sunflower.png");
    addPlant("Лотос", ":/img/img/lotus.png");
    addPlant("Кактус", ":/img/img/cactus.png");
    addPlant("Вишня", ":/img/img/cherry.png");
    addPlant("Малина", ":/img/img/raspberry.png");
    addPlant("Клубника", ":/img/img/strawberry.png");
    addPlant("Виноград", ":/img/img/grapes.png");
    addPlant("Персик", ":/img/img/peach.png");
    addPlant("Яблоко", ":/img/img/apple.png");
    addPlant("Киви", ":/img/img/kiwi.png");
    addPlant("Груша", ":/img/img/pear.png");
    addPlant("Ананас", ":/img/img/pineapple.png");
    addPlant("Банан", ":/img/img/banana.png");
    addPlant("Апельсин", ":/img/img/orange.png");
    addPlant("Слива", ":/img/img/plum.png");
    addPlant("Кукуруза", ":/img/img/corn.png");
    addPlant("Редис", ":/img/img/radish.png");
    addPlant("Свекла", ":/img/img/beet.png");
    addPlant("Морковь", ":/img/img/carrot.png");
    addPlant("Томат", ":/img/img/tomato.png");
    addPlant("Авокадо", ":/img/img/avocado.png");
    addPlant("Капуста", ":/img/img/cabbage.png");
    addPlant("Чеснок", ":/img/img/garlic.png");
    addPlant("Брокколи", ":/img/img/broccoli.png");
    addPlant("Лук", ":/img/img/onion.png");
    addPlant("Баклажан", ":/img/img/eggplant.png");
    addPlant("Болгарский перец", ":/img/img/paprika.png");
    addPlant("Огурец", ":/img/img/cucumber.png");
    addPlant("Картошка", ":/img/img/potato.png");
    addPlant("Тыква", ":/img/img/pumpkin.png");

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

    if (plantName == "Роза") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Роза — это многолетний кустарник, символ красоты и любви. Цветы имеют разнообразные оттенки и приятный аромат.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Нуждается в хорошем освещении, но требует защиты от палящего солнца.</li>
                    <li>Предпочитает плодородную, слегка кислую почву с хорошим дренажем.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Регулярный полив, но без застоя воды.</li>
                    <li>Обрезка для формирования куста и удаления увядших цветов.</li>
                    <li>Подкормка весной и летом удобрениями для цветущих растений.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Лотос") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Лотос — водное растение с крупными листьями и нежными цветами, символизирующее чистоту и духовность.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Растет в водоемах или искусственных прудах.</li>
                    <li>Образует подводное корневище.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Поддержание температуры воды на уровне 22–30°C.</li>
                    <li>Хорошее освещение и мягкий, богатый питательными веществами грунт.</li>
                    <li>Удаление отмерших листьев и цветов.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Томат") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Томат — однолетнее растение семейства пасленовых, широко культивируемое ради сочных плодов.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Любит солнечные участки и тепло.</li>
                    <li>Требует регулярного полива и опоры для стеблей.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Полив каждые 2–3 дня, особенно в период плодоношения.</li>
                    <li>Пасынкование для формирования куста.</li>
                    <li>Подкормка органическими и минеральными удобрениями.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Яблоко") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Яблоня — плодовое дерево, дающее вкусные и полезные яблоки, одно из самых популярных садовых растений.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Дерево может достигать высоты до 10 м.</li>
                    <li>Цветение происходит весной, плоды созревают летом или осенью.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Регулярный полив в засушливое время.</li>
                    <li>Обрезка ветвей весной для омоложения дерева.</li>
                    <li>Защита от вредителей и болезней, таких как парша и тля.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Кактус") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Кактус — суккулент, способный накапливать воду в стебле. Он известен своей выносливостью и часто встречается в пустынях.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Любит яркий свет, многие виды предпочитают прямое солнце.</li>
                    <li>Устойчив к засухе, но чувствителен к переувлажнению.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Полив раз в 1–2 недели летом, зимой — минимальный.</li>
                    <li>Легкая, хорошо дренированная почва.</li>
                    <li>Пересадка каждые несколько лет для обновления почвы.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Авокадо") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Авокадо — вечнозеленое дерево, плоды которого богаты маслами и полезными веществами.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Предпочитает теплый климат без заморозков.</li>
                    <li>Растение любит влажность и рыхлую почву.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Полив, чтобы почва оставалась влажной, но не переувлажненной.</li>
                    <li>Посадка в хорошо дренированную почву.</li>
                    <li>Регулярная обрезка для формирования кроны.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Персик") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Персик — плодовое дерево, известное своими сладкими и ароматными плодами.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Предпочитает теплый климат и солнечные участки.</li>
                    <li>Плоды созревают летом.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Регулярный полив, особенно в жаркую погоду.</li>
                    <li>Обрезка для формирования кроны и увеличения урожайности.</li>
                    <li>Подкормка удобрениями в период цветения и плодоношения.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Слива") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Слива — плодовое дерево, дающее сочные и сладкие плоды, которые используют в свежем виде или для переработки.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Предпочитает солнечные места и плодородную почву.</li>
                    <li>Может расти как куст или дерево в зависимости от сорта.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Полив каждые 7–10 дней, особенно в период засухи.</li>
                    <li>Обрезка сухих и поврежденных ветвей весной.</li>
                    <li>Подкормка органическими удобрениями раз в год.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Клубника") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Клубника — многолетняя ягодная культура с ароматными и сладкими плодами.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Предпочитает солнечные участки и легкую, плодородную почву.</li>
                    <li>Чувствительна к избытку влаги.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Регулярный полив, особенно в засуху.</li>
                    <li>Удаление усов для стимуляции роста ягод.</li>
                    <li>Подкормка органическими удобрениями после сбора урожая.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Малина") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Малина — многолетний кустарник, дающий вкусные и полезные ягоды.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Растет на легких почвах, хорошо дренированных.</li>
                    <li>Требует ежегодной обрезки старых побегов.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Полив в период плодоношения и засухи.</li>
                    <li>Обрезка отмерших и больных побегов весной.</li>
                    <li>Подкормка минеральными удобрениями после цветения.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Виноград") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Виноград — многолетняя культура, выращиваемая ради плодов для изготовления вина, сока и других продуктов.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Требует солнечных участков и защиту от ветра.</li>
                    <li>Любит теплый климат с умеренными осадками.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Полив каждые 10–14 дней, особенно в жаркую погоду.</li>
                    <li>Обрезка старых и лишних побегов весной.</li>
                    <li>Подкормка минеральными удобрениями в начале весны и перед цветением.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Картошка") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Картофель — многолетнее клубневое растение, выращиваемое в основном как однолетник ради клубней.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Предпочитает солнечные участки и хорошо дренированную почву.</li>
                    <li>Чувствителен к засухе и избытку влаги.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Регулярный полив, особенно в период роста и цветения.</li>
                    <li>Пропалывание сорняков и рыхление почвы.</li>
                    <li>Подкормка минеральными удобрениями во время роста клубней.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Капуста") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Капуста — овощное растение, распространенное в разных сортах: белокочанная, цветная, брокколи и другие.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Требует охлажденной и влажной почвы, солнечного места.</li>
                    <li>Чувствительна к нехватке влаги и перепадам температуры.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Полив каждые 2–3 дня в сухую погоду.</li>
                    <li>Обрезка внешних листьев для предотвращения гниения.</li>
                    <li>Подкормка азотными удобрениями в начале роста.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Баклажан") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Баклажан — теплолюбивое овощное растение, выращиваемое заради вкусных плодов с характерной бархатистой кожицей.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Предпочитает солнечные участки и умеренно влажную почву.</li>
                    <li>Чувствителен к холодам и избытку влаги.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Полив каждые 2–3 дня, особенно в жаркую погоду.</li>
                    <li>Пасынкование для формирования куста.</li>
                    <li>Подкормка фосфорно-калийными удобрениями для улучшения урожайности.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Редис") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Редис — скороспелый корнеплод, используемый в свежем виде для салатов и закусок.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Растет быстро, требует рыхлой, плодородной почвы.</li>
                    <li>Чувствителен к перепадам температуры и избытку влаги.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Полив каждые 1–2 дня, особенно при засухе.</li>
                    <li>Удобрение органическими удобрениями в начале роста.</li>
                    <li>Прореживание для предотвращения загущенности посева.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Свекла") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Свекла — корнеплодное растение, используемое для приготовления салатов, супов и сока.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Предпочитает влажную, хорошо дренированную почву.</li>
                    <li>Требует защиты от жары и избытка влаги.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Полив каждые 3–4 дня, особенно в период роста корнеплодов.</li>
                    <li>Подкормка фосфорно-калийными удобрениями после прорастания семян.</li>
                    <li>Прореживание для правильного формирования клубней.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Подсолнух") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Подсолнух — крупное травянистое растение с яркими желтыми цветками, которое поворачивается к солнцу.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Быстрорастущее однолетнее растение.</li>
                    <li>Цветки содержат семена, которые используют в кулинарии.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Посадка в солнечном месте.</li>
                    <li>Регулярный полив, особенно в период цветения.</li>
                    <li>Легкий суглинистый грунт с добавлением органики.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Болгарский перец") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Болгарский перец — теплолюбивый овощ, ценящийся за свои сочные плоды различных цветов и вкусов.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Требует солнечных участков и защищенных от ветра мест.</li>
                    <li>Чувствителен к низким температурам.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Полив каждые 2–3 дня, особенно в жаркую погоду.</li>
                    <li>Обрезка лишних побегов и формирование куста.</li>
                    <li>Подкормка органическими и минеральными удобрениями в период вегетации.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Лук") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Лук — популярный овощ, используемый как в свежем, так и в переработанном виде.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Растет на солнечных и хорошо дренированных участках.</li>
                    <li>Чувствителен к избытку влаги.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Полив по мере необходимости, в зависимости от влажности почвы.</li>
                    <li>Удаление сорняков и рыхление почвы.</li>
                    <li>Подкормка минеральными удобрениями во время роста пера.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Кукуруза") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Кукуруза — однолетняя культура, выращиваемая ради зерна и початков для свежего употребления и переработки.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Предпочитает солнечные участки и плодородные почвы.</li>
                    <li>Требует регулярного полива и защиты от ветра.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Полив каждые 2–3 дня в жаркую погоду.</li>
                    <li>Удаление сорняков и рыхление почвы.</li>
                    <li>Подкормка азотными удобрениями в период активного роста стебля.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Вишня") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Вишня — плодовое дерево или кустарник с кисловатыми и сочными плодами, которые используются в кулинарии и консервировании.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Требует солнечных участков и умеренной влажности почвы.</li>
                    <li>Чувствительна к заморозкам весной.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Полив каждые 2 недели, особенно во время плодоношения.</li>
                    <li>Удаление старых и поврежденных веток осенью или весной.</li>
                    <li>Подкормка азотными удобрениями весной для стимулирования роста.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Груша") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Груша — плодовое дерево, известное своими сочными и сладкими плодами.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Предпочитает солнечные места и плодородные, хорошо дренированные почвы.</li>
                    <li>Чувствительна к переувлажнению.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Регулярный полив в сухую погоду.</li>
                    <li>Обрезка старых и больных ветвей для поддержания кроны.</li>
                    <li>Подкормка минеральными удобрениями после цветения и перед сбором урожая.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Киви") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Киви — вечнозеленая лиана, известная своими сладкими плодами с характерной внешностью.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Требует теплого климата, защищенного от ветра.</li>
                    <li>Чувствительна к заморозкам и недостатку влаги.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Полив каждые 2–3 дня, особенно в жаркую погоду.</li>
                    <li>Обрезка побегов для формирования кроны.</li>
                    <li>Подкормка органическими удобрениями в период активного роста.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Морковь") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Морковь — корнеплодное растение, ценимое за питательные свойства и сладкий вкус.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Предпочитает рыхлую, богатую питательными веществами почву.</li>
                    <li>Чувствительна к избытку влаги и тяжелым почвам.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Полив каждую неделю, регулируя влажность почвы.</li>
                    <li>Прореживание для формирования ровных корнеплодов.</li>
                    <li>Подкормка фосфорно-калийными удобрениями во время роста.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Тыква") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
            <p>Тыква — растение семейства тыквенных, известное своими большими плодами и универсальностью использования.</p>
            <p><b>Особенности:</b></p>
            <ul>
                <li>Требует солнечных мест и богатой, дренированной почвы.</li>
                <li>Чувствительна к холодам и избытку влаги.</li>
            </ul>
            <p><b>Уход:</b></p>
            <ul>
                <li>Регулярный полив каждые 4–5 дней, особенно в период роста плодов.</li>
                <li>Удаление лишних побегов и подсыпание почвы к стеблю.</li>
                <li>Подкормка органическими удобрениями каждые 2 недели.</li>
            </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Чеснок") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Чеснок — пряное растение, используемое в кулинарии и в народной медицине.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Требует солнечных участков с легкой, воздухопроницаемой почвой.</li>
                    <li>Чувствителен к избытку влаги и загниванию.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Полив умеренный, чтобы почва оставалась слегка влажной.</li>
                    <li>Удаление сорняков для предотвращения конкуренции за питание.</li>
                    <li>Подкормка фосфорно-калийными удобрениями после появления зеленых всходов.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Огурец") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Огурец — популярный овощ, выращиваемый как в открытом грунте, так и в теплицах.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Требует теплых солнечных мест и обильного полива.</li>
                    <li>Чувствителен к перепадам температуры и засухе.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Регулярный полив, особенно в фазе роста плодов.</li>
                    <li>Подкормка азотными и органическими удобрениями каждые 10–14 дней.</li>
                    <li>Прореживание для улучшения формирования огурцов.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Банан") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Банан — тропическое растение с съедобными плодами, ценимыми за сладкий вкус и питательные свойства.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Требует теплого климата без заморозков.</li>
                    <li>Любит влажную почву и регулярное опрыскивание.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Регулярный полив каждые 2–3 дня, поддерживая влажность почвы.</li>
                    <li>Обрезка сухих листьев для предотвращения загнивания.</li>
                    <li>Подкормка жидкими удобрениями каждые 2 недели.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Ананас") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Ананас — тропическое растение, известное своими сладкими плодами, которые выращиваются из отростков.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Требует теплого климата и защищенных от ветра мест.</li>
                    <li>Чувствителен к избытку влаги и резким температурным колебаниям.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Полив каждые 2–3 дня в зависимости от влажности почвы.</li>
                    <li>Использование органических удобрений для поддержания питательной почвы.</li>
                    <li>Обрезка лишних листьев для формирования компактного куста.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Брокколи") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Брокколи — питательное растение, выращиваемое ради съедобных стеблей и соцветий.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Требует прохладного климата и влажной почвы.</li>
                    <li>Чувствительна к жаре и недостатку влаги.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Полив каждые 2–3 дня, поддерживая почву влажной.</li>
                    <li>Подкормка азотно-калийными удобрениями для стимуляции роста.</li>
                    <li>Обрезка отцветших соцветий для стимуляции новых боковых побегов.</li>
                </ul>
            </body>
            </html>
            )";
    } else if (plantName == "Апельсин") {
        info = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <style>
                    body { font-family: Fixedsys;}
                    p {font-size: 14px;}
                    li {font-size: 14px;}
                </style>
            </head>
            <body>
                <p>Апельсин — популярное цитрусовое дерево, выращиваемое ради своих вкусных плодов.</p>
                <p><b>Особенности:</b></p>
                <ul>
                    <li>Предпочитает солнечные участки и защищенные от ветра места.</li>
                    <li>Чувствителен к перепадам температуры и чрезмерной влаге.</li>
                </ul>
                <p><b>Уход:</b></p>
                <ul>
                    <li>Полив каждую неделю, регулируя влажность почвы.</li>
                    <li>Подкормка азотно-калийными удобрениями для стимулирования роста плодов.</li>
                    <li>Обрезка сухих веток и поддержание кроны.</li>
                </ul>
            </body>
            </html>
            )";
    }

    plantInfo->setText(info);
}
