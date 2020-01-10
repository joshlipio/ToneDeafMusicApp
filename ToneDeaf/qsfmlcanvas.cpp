#include "qsfmlcanvas.h"
#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
#endif
#include <iostream>
#include <QResizeEvent>
#include <QDebug>

QSFMLCanvas::QSFMLCanvas(QWidget* Parent, unsigned int FrameTime) : QWidget(Parent),
myInitialized (false)

{
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    setFocusPolicy(Qt::StrongFocus);
    myTimer.setInterval(FrameTime);
}

QSFMLCanvas::~QSFMLCanvas() {}

void QSFMLCanvas::showEvent(QShowEvent*)
{
    if (!myInitialized)
    {
        #ifdef Q_WS_X11
        //XFlush(QX11Info::display());
        #endif
        RenderWindow::create(reinterpret_cast<sf::WindowHandle>(winId()));
        RenderWindow::setFramerateLimit(60);
        OnInit();
        connect(&myTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        myTimer.start();
        myInitialized = true;
    }
}

void QSFMLCanvas::resizeEvent(QResizeEvent* event)
{
    setView(sf::View(sf::FloatRect(0, 0, event->size().width(), event->size().height())));
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
    return 0;
}

void QSFMLCanvas::paintEvent(QPaintEvent*)
{
    OnUpdate();
    RenderWindow::display();
}

void QSFMLCanvas::OnInit() {}
void QSFMLCanvas::OnUpdate() {}
