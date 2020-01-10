#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H

#include <QWidget>
#include <SFML/Graphics.hpp>
#include <QTimer>

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
//Q_OBJECT
public:
    explicit QSFMLCanvas(QWidget *parent, unsigned int FrameTime = 0);
    virtual void showEvent(QShowEvent*);
    virtual QPaintEngine* paintEngine() const;
    virtual void paintEvent(QPaintEvent*);
    virtual ~QSFMLCanvas();
    virtual void OnInit();
    virtual void OnUpdate();
    virtual void resizeEvent(QResizeEvent* event);

private:
    QTimer myTimer;
    bool myInitialized;
};
#endif // QSMLCANVAS_H
