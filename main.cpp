#include <QApplication>
#include <QPushButton>
#include "Domain.h"
#include "Repository.h"
#include "RepositoryFile.h"
#include "Service.h"
#include "GUI.h"
#include "CartGUI.h"
void tests()
{
    testeDomain();
    testeRepo();
    testeRepoFile();
    testeValidator();
    testeSrv();
}
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    tests();
    RepositoryFile repo("../films.csv");
    Service srv(repo);
    GUI gui(srv);
    gui.show();
    return QApplication::exec();
}
