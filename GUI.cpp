//
// Created by galal on 02.05.2024.
//

#include "GUI.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <qbrush.h>
#include <string>
#include <algorithm>
#include "CartGUI.h"
#include "CartPainter.h"
void GUI::initWindow() {
    setLayout(mainLayout);
    listAndButtons->setLayout(listAndButtonsLayout);
    //listAndButtonsLayout->addWidget(filmList);
    main_view_table->setModel(main_model);
    listAndButtonsLayout->addWidget(main_view_table);
    leftButtons->setLayout(leftButtonsLayout);
    leftButtonsLayout->addWidget(deleteFilmButton);
    leftButtonsLayout->addWidget(addCartButton);
    leftButtonsLayout->addWidget(undoButton);
    leftButtonsLayout->addWidget(rapportButton);
    listAndButtonsLayout->addWidget(leftButtons);
    sortButtons->setLayout(sortButtonsLayout);
    sortButtonsLayout->addWidget(sortButtonTitle);
    sortButtonsLayout->addWidget(sortButtonActor);
    sortButtonsLayout->addWidget(sortButtonYearGenre);
    listAndButtonsLayout->addWidget(sortButtons);
    mainLayout->addWidget(listAndButtons);
    mainLayout->addWidget(inputWidget);
    inputWidget->setLayout(inputLayout);
    inputLayout->addRow(new QLabel("Title:"), titleInput);
    inputLayout->addRow(new QLabel("Genre:"), genreInput);
    inputLayout->addRow(new QLabel("Year:"),yearInput);
    inputLayout->addRow(new QLabel("Actor:"),actorInput);
    addUpdateButtons->setLayout(addUpdateButtonsLayout);
    addUpdateButtonsLayout->addWidget(addFilmButton);
    addUpdateButtonsLayout->addWidget(updateFilmButton);
    addUpdateButtonsLayout->addWidget(findFilmButton);
    inputLayout->addWidget(addUpdateButtons);
    filterButtons->setLayout(filterButtonsLayout);
    filterButtonsLayout->addWidget(filterButtonTitle);
    filterButtonsLayout->addWidget(filterButtonYear);
    inputLayout->addWidget(filterButtons);
    deleteFilmButton->setDisabled(true);
    addCartButton->setDisabled(true);
    mainLayout->addWidget(RapportButtons);
    RapportButtons->setLayout(RapportButtonsLayout);

    auto* generateRow = new QWidget;
    auto* generateLayout = new QHBoxLayout;
    generateRow->setLayout(generateLayout);
    generateLayout->addWidget(generateButton);
    generateLayout->addWidget(generateInput);
    auto* cart = new QWidget;
    auto* cartLayout = new QVBoxLayout;
    cart->setLayout(cartLayout);
    inputLayout->addWidget(cart);
    cartLayout->addWidget(generateRow);
    auto* exportRow = new QWidget;
    auto* exportLayout = new QHBoxLayout;
    exportRow->setLayout(exportLayout);
    exportLayout->addWidget(exportButton);
    exportLayout->addWidget(exportInput);
    cartLayout->addWidget(exportRow);
    cartLayout->addWidget(emptyButton);

    auto* cartWindow = new QWidget;
    auto* cartWindowLayout = new QHBoxLayout;
    cartWindow->setLayout(cartWindowLayout);
    cartWindowLayout->addWidget(cartButton);
    cartWindowLayout->addWidget(cartPainterButton);
    inputLayout->addWidget(cartWindow);
    rapportButtonsGUIinit();
}

void GUI::reloadList(const vector<Film>& films) {
    filmList->clear();
    for(const auto& film: films)
    {
        auto* item = new QListWidgetItem(QString::fromStdString(film.getTitle()));
        filmList->addItem(item);
    }
    main_model->reload(srv.getAll());
}

void GUI::connectSignalsSlots() {
    QObject::connect(filmList, &QListWidget::itemSelectionChanged, [&](){
        auto selection = filmList->selectedItems();
        if(selection.isEmpty())
        {
            titleInput->setText("");
            genreInput->setText("");
            yearInput->setText("");
            actorInput->setText("");
            deleteFilmButton->setDisabled(true);
            addCartButton->setDisabled(true);
        }
        else
        {
            auto selectionItem = selection.at(0);
            auto film = srv.findSrv(selectionItem->text().toStdString());
            titleInput->setText(QString::fromStdString(film.getTitle()));
            genreInput->setText(QString::fromStdString(film.getGenre()));
            yearInput->setText(QString::fromStdString(std::to_string(film.getYear())));
            actorInput->setText(QString::fromStdString(film.getActor()));
            deleteFilmButton->setDisabled(false);
            addCartButton->setDisabled(false);
        }
    });
    QObject::connect(addFilmButton, &QPushButton::clicked, this, &GUI::addGUI);
    QObject::connect(updateFilmButton, &QPushButton::clicked, this, &GUI::updateGUI);
    QObject::connect(deleteFilmButton,&QPushButton::clicked,this,&GUI::deleteGUI);
    QObject::connect(findFilmButton, &QPushButton::clicked,this, &GUI::findGUI);
    QObject::connect(undoButton, &QPushButton::clicked, this, &GUI::undoGUI);
    QObject::connect(sortButtonTitle, &QPushButton::clicked, [&](){
        reloadList(srv.sort(1));
        main_model->reload(srv.sort(1));
    });
    QObject::connect(sortButtonActor, &QPushButton::clicked, [&](){
        reloadList(srv.sort(2));
        main_model->reload(srv.sort(2));
    });
    QObject::connect(sortButtonYearGenre, &QPushButton::clicked, [&](){
        reloadList(srv.sort(3));
        main_model->reload(srv.sort(3));
    });
    QObject::connect(filterButtonTitle, &QPushButton::clicked, [this](){
        filterGUI(1);
    });
    QObject::connect(filterButtonYear, &QPushButton::clicked, [this](){
        filterGUI(2);
    });
    QObject::connect(addCartButton, &QPushButton::clicked,this, &GUI::addToCartGUI);
    QObject::connect(rapportButton, &QPushButton::clicked,this,&GUI::rapportGUI);
    QObject::connect(generateButton, &QPushButton::clicked,this,&GUI::generateGUI);
    QObject::connect(emptyButton, &QPushButton::clicked,this, &GUI::emptyCartGUI);
    QObject::connect(exportButton, &QPushButton::clicked, this, &GUI::exportCartGUI);
    QObject::connect(cartButton, &QPushButton::clicked,[&](){
            auto cart = new CartGUI(srv);
            cart->show();
    });
    QObject::connect(cartPainterButton, &QPushButton::clicked,[&](){
        auto cart = new CartPainter(srv);
        cart->show();
    });
    QObject::connect(main_view_table->selectionModel(), &QItemSelectionModel::selectionChanged, [&]{
        if(main_view_table->selectionModel()->selectedIndexes().isEmpty())
        {
            titleInput->setText("");
            genreInput->setText("");
            yearInput->setText("");
            actorInput->setText("");
        }
        else
        {
            int row = main_view_table->selectionModel()->selectedIndexes().at(0).row();
            auto const &list = srv.getAll();
            for (auto i{1};i<(int)list.size();++i)
                if (list[i].getTitle() == main_model->data(main_view_table->model()->index(row, 0)).toString().toStdString())
                {
                    titleInput->setText(QString::fromStdString(list[i].getTitle()));
                    genreInput->setText(QString::fromStdString(list[i].getGenre()));
                    yearInput->setText(QString::number(list[i].getYear()));
                    actorInput->setText(QString::fromStdString(list[i].getActor()));
                    break;
                }
        }
    });
}

void GUI::addGUI() {
    try{
        srv.addSrv(titleInput->text().toStdString(),
                   genreInput->text().toStdString(),
                   yearInput->text().toInt(),
                   actorInput->text().toStdString());
        reloadList(srv.getAll());
    }
    catch(ValidatorException& ex){
        for(const auto& msg : ex.getMessages())
        {
            QMessageBox::warning(this, "Warning", QString::fromStdString(msg));
        }
    }
    catch(RepositoryException& ex){
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
    }
    auto rez = srv.getRapport();
    if(rez[genreInput->text().toStdString()] == 1)
    {
        auto genre = genreInput->text().toStdString();
        auto number = rez[genreInput->text().toStdString()];
        auto* rapBtn = new QPushButton(QString::fromStdString(genre));
        RapportButtonsLayout->addWidget(rapBtn);
        QObject::connect(rapBtn,&QPushButton::clicked,[genre, this](){
            auto rez = srv.getRapport();
            auto* rapportWindow = new QWidget;
            auto* rapportWindowLayout = new QVBoxLayout(rapportWindow);
            auto nr = std::to_string(rez[genre]);
            auto* rapportLabel = new QLabel(QString::fromStdString("Sunt " + nr + " filme de genul " + genre));
            rapportWindowLayout->addWidget(rapportLabel);
            rapportWindow->show();
        });
    }
}

void GUI::updateGUI() {
    try{
        srv.updateSrv(titleInput->text().toStdString(),
                   genreInput->text().toStdString(),
                   yearInput->text().toInt(),
                   actorInput->text().toStdString());
        reloadList(srv.getAll());
    }
    catch(ValidatorException& ex){
        for(const auto& msg : ex.getMessages())
        {
            QMessageBox::warning(this, "Warning", QString::fromStdString(msg));
        }
    }
    catch(RepositoryException& ex){
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
    }
}

void GUI::deleteGUI() {
    string genre;
    try{
        genre = srv.findSrv(filmList->selectedItems().at(0)->text().toStdString()).getGenre();
        srv.deleteSrv(filmList->selectedItems().at(0)->text().toStdString());
        reloadList(srv.getAll());
    }
    catch(ValidatorException& ex){
        for(const auto& msg : ex.getMessages())
        {
            QMessageBox::warning(this, "Warning", QString::fromStdString(msg));
        }
    }
    catch(RepositoryException& ex){
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
    }
    auto rez = srv.getRapport();
    if(rez[genre] == 0) {
        for (int i = 0; i < RapportButtonsLayout->count(); i++)
        {
            auto* RapBtn = qobject_cast<QPushButton*>(RapportButtonsLayout->itemAt(i)->widget());
            if(RapBtn->text() == QString::fromStdString(genre)) RapBtn->deleteLater();
        }
    }
}

void GUI::findGUI() {

    try{
        auto title = titleInput->text().toStdString();
        Validator::validateString(title);
        auto item = filmList->findItems(QString::fromStdString(title),Qt::MatchExactly);
        if(!item.isEmpty())filmList->setCurrentItem(item.at(0));
        else QMessageBox::warning(this, "Warning", "Film not found!");
    }
    catch(ValidatorException& ex){
        for(const auto& msg : ex.getMessages())
        {
            QMessageBox::warning(this, "Warning", QString::fromStdString(msg));
        }
    }
    catch(RepositoryException& ex){
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
    }
}

void GUI::undoGUI() {
    srv.undo();
    reloadList(srv.getAll());
}

void GUI::filterGUI(int option) {
    try{
        vector<Film> rez;
        if(option == 1)rez = srv.filter(option, titleInput->text().toStdString());
        else rez = srv.filter(option, yearInput->text().toStdString());
        reloadList(rez);
        main_model->reload(rez);
    }
    catch(ValidatorException& ex){
        for(const auto& msg : ex.getMessages())
        {
            QMessageBox::warning(this, "Warning", QString::fromStdString(msg));
        }
    }
    catch(RepositoryException& ex){
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
    }
}

void GUI::addToCartGUI() {
    try{
        srv.addCart(filmList->selectedItems().at(0)->text().toStdString());
    }
    catch(ValidatorException& ex){
        for(const auto& msg : ex.getMessages())
        {
            QMessageBox::warning(this, "Warning", QString::fromStdString(msg));
        }
    }
    catch(RepositoryException& ex) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
    }
}

void GUI::rapportGUI() {
    auto rez = srv.getRapport();
    auto* rapportWindow = new QWidget;
    auto* rapportLayout = new QVBoxLayout;
    auto* rapportList = new QListWidget;
    rapportWindow->setLayout(rapportLayout);
    rapportLayout->addWidget(rapportList);
    for(const auto& el : rez)
    {
        auto* item = new QListWidgetItem(QString::fromStdString(el.first + ": " + std::to_string(el.second)));
        rapportList->addItem(item);
    }
    rapportWindow->show();
}

void GUI::rapportButtonsGUIinit() {
    auto rez = srv.getRapport();
    for(const auto& rapport : rez)
    {
        auto* rapBtn = new QPushButton(QString::fromStdString(rapport.first));
        RapportButtonsLayout->addWidget(rapBtn);
        QObject::connect(rapBtn,&QPushButton::clicked,[rapport, this](){
            auto rez = srv.getRapport();
            auto* rapportWindow = new QWidget;
            auto* rapportWindowLayout = new QVBoxLayout(rapportWindow);
            auto nr = std::to_string(rez[rapport.first]);
            auto* rapportLabel = new QLabel(QString::fromStdString("Sunt " + nr + " filme de genul " + rapport.first));
            rapportWindowLayout->addWidget(rapportLabel);
            rapportWindow->show();
        });
    }
}

void GUI::generateGUI() {
    try{
        srv.generateCart(generateInput->text().toInt());
    }
    catch(ValidatorException& ex){
        for(const auto& msg : ex.getMessages())
        {
            QMessageBox::warning(this, "Warning", QString::fromStdString(msg));
        }
    }
}

void GUI::emptyCartGUI() {
    srv.emptyCart();
}

void GUI::exportCartGUI() {
    try{
        srv.exportCVS(exportInput->text().toStdString());
    }
    catch(ValidatorException& ex){
        for(const auto& msg : ex.getMessages())
        {
            QMessageBox::warning(this, "Warning", QString::fromStdString(msg));
        }
    }
}
