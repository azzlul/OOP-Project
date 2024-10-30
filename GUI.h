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
#include "TableModel.h"
#include "QTableView"
class GUI: public QWidget{
private:
    Service& srv;
    QHBoxLayout* mainLayout = new QHBoxLayout;
    QWidget* listAndButtons = new QWidget;
    QVBoxLayout* listAndButtonsLayout = new QVBoxLayout;
    QWidget* leftButtons = new QWidget;
    QHBoxLayout* leftButtonsLayout = new QHBoxLayout;
    QWidget* sortButtons = new QWidget;
    QHBoxLayout* sortButtonsLayout = new QHBoxLayout;
    QListWidget* filmList = new QListWidget;
    QLineEdit* titleInput = new QLineEdit;
    QLineEdit* genreInput = new QLineEdit;
    QLineEdit* yearInput = new QLineEdit;
    QLineEdit* actorInput = new QLineEdit;
    QWidget* addUpdateButtons = new QWidget;
    QHBoxLayout* addUpdateButtonsLayout = new QHBoxLayout;
    QWidget* filterButtons = new QWidget;
    QHBoxLayout* filterButtonsLayout = new QHBoxLayout;
    QPushButton* addFilmButton = new QPushButton("Add");
    QPushButton* updateFilmButton = new QPushButton("Update");
    QPushButton* deleteFilmButton = new QPushButton("Delete");
    QPushButton* findFilmButton = new QPushButton("Find");
    QPushButton* undoButton = new QPushButton("Undo");
    QPushButton* sortButtonTitle = new QPushButton("Sort by title");
    QPushButton* sortButtonActor = new QPushButton("Sort by actor");
    QPushButton* sortButtonYearGenre = new QPushButton("Sort by year+genre");
    QPushButton* filterButtonTitle = new QPushButton("Filter by title");
    QPushButton* filterButtonYear = new QPushButton("Filter by year");
    QPushButton* addCartButton = new QPushButton("Add to cart");
    QPushButton* rapportButton = new QPushButton("Rapport");
    QPushButton* generateButton = new QPushButton("Generate");
    QPushButton* emptyButton = new QPushButton("Empty cart");
    QPushButton* exportButton = new QPushButton("Export");
    QLineEdit* exportInput = new QLineEdit;
    QLineEdit* generateInput = new QLineEdit;
    QFormLayout* inputLayout = new QFormLayout;
    QWidget* RapportButtons = new QWidget;
    QVBoxLayout* RapportButtonsLayout = new QVBoxLayout;
    QWidget* inputWidget = new QWidget;
    QPushButton* cartButton = new QPushButton("Cart");
    QPushButton* cartPainterButton = new QPushButton("Visualize Cart");
    QTableView* main_view_table = new QTableView;
    TableModel* main_model = new TableModel;
    void initWindow();
    void connectSignalsSlots();
    void addGUI();
    void updateGUI();
    void deleteGUI();
    void findGUI();
    void undoGUI();
    void filterGUI(int option);
    void addToCartGUI();
    void rapportGUI();
    void generateGUI();
    void emptyCartGUI();
    void exportCartGUI();
    void reloadList(const vector<Film>& films);
    void rapportButtonsGUIinit();
public:
    explicit GUI(Service& srv):srv{srv}{
        initWindow();
        connectSignalsSlots();
        reloadList(srv.getAll());
    }
};