//
// Created by galal on 02.05.2024.
//

#include "CartGUI.h"
#include "qtimer.h"
#include "qmessagebox.h"
void CartGUI::initializeWindow() {
    setLayout(cartLayout);
    cartLayout->addWidget(cartList);
    generateRow->setLayout(generateLayout);
    generateLayout->addWidget(generateButton);
    generateLayout->addWidget(generateInput);
    cartLayout->addWidget(generateRow);
    exportRow->setLayout(exportLayout);
    exportLayout->addWidget(exportButton);
    exportLayout->addWidget(exportInput);
    cartLayout->addWidget(exportRow);
    cartLayout->addWidget(emptyButton);
}

void CartGUI::connectSignalsSlots() {
    QObject::connect(generateButton, &QPushButton::clicked,this,&CartGUI::generateGUI);
    QObject::connect(emptyButton, &QPushButton::clicked,this, &CartGUI::emptyCartGUI);
    QObject::connect(exportButton, &QPushButton::clicked, this, &CartGUI::exportCartGUI);
}

void CartGUI::reloadList(const vector<Film>& films) {
    cartList->clear();
    for(const auto& film: films)
    {
        auto* item = new QListWidgetItem(QString::fromStdString(film.getTitle()));
        cartList->addItem(item);
    }
}

void CartGUI::generateGUI() {
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

void CartGUI::emptyCartGUI() {
    srv.emptyCart();
}

void CartGUI::exportCartGUI() {
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
