#include <random>
#include "GUI.h"
#include "qpainter.h"
class CartPainter: public QWidget, public Observer{
private:
    Service &srv;
    void paintEvent(QPaintEvent *event) override{
        (void)event;
        QPainter painter {this};
        auto cart = srv.getAllCart();
        for( auto const& film:cart)
        {
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> x(50, this->width()-50), y(50, this->height()-50);
            int xx= x(rng), yy =  y(rng);
            painter.drawEllipse(xx,yy,100,100);
        }
    }
    void update_cart() override{
        repaint();
    }
public:
    explicit CartPainter(Service &srv): srv(srv)
    {
        srv.attachObserver(this);
    }
    ~CartPainter() override{
        srv.detachObserver(this);
    }
};
