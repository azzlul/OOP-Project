#pragma once
#include <QFormLayout>
#include "qwidget.h"
#include "qlistwidget.h"
#include "qpushbutton.h"
#include "qlineedit.h"
#include "qboxlayout.h"
#include "qdebug.h"
#include "Domain.h"
#include "Service.h"
#include "qlabel.h"

class CartGUI: public QWidget, public Observer{
private:
    Service& srv;
    QListWidget* cartList = new QListWidget;
    QVBoxLayout* cartLayout = new QVBoxLayout;
    QLineEdit* generateInput = new QLineEdit;
    QWidget* generateRow = new QWidget;
    QHBoxLayout* generateLayout = new QHBoxLayout;
    QPushButton* generateButton = new QPushButton("Generate");
    QPushButton* emptyButton = new QPushButton("Empty cart");
    QWidget* exportRow = new QWidget;
    QHBoxLayout* exportLayout = new QHBoxLayout;
    QPushButton* exportButton = new QPushButton("Export");
    QLineEdit* exportInput = new QLineEdit;
    void initializeWindow();
    void connectSignalsSlots();
    void generateGUI();
    void emptyCartGUI();
    void exportCartGUI();
    void reloadList(const vector<Film>& films);
public:
    explicit CartGUI(Service& srv):srv{srv} {
        initializeWindow();
        connectSignalsSlots();
        reloadList(srv.getAllCart());
        srv.attachObserver(this);
    }
    void update_cart() override
    {
        reloadList(srv.getAllCart());
    }
    ~CartGUI()
    {
        srv.detachObserver(this);
    }
};