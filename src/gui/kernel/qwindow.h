/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QWINDOW_QPA_H
#define QWINDOW_QPA_H

#include <QtCore/QObject>
#include <QtCore/QEvent>
#include <QtCore/QMargins>
#include <QtCore/QRect>

#include <QtGui/qsurface.h>
#include <QtGui/qsurfaceformat.h>
#include <QtGui/qwindowdefs.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Gui)

class QWindowPrivate;

class QExposeEvent;
class QResizeEvent;
class QShowEvent;
class QHideEvent;
class QKeyEvent;
class QInputMethodEvent;
class QMouseEvent;
#ifndef QT_NO_WHEELEVENT
class QWheelEvent;
#endif

class QPlatformSurface;
class QPlatformWindow;
class QBackingStore;
class QScreen;

class Q_GUI_EXPORT QWindow : public QObject, public QSurface
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QWindow)

    Q_PROPERTY(QString windowTitle READ windowTitle WRITE setWindowTitle)

public:
    enum SurfaceType { RasterSurface, OpenGLSurface };

    QWindow(QScreen *screen = 0);
    QWindow(QWindow *parent);
    virtual ~QWindow();

    void setSurfaceType(SurfaceType surfaceType);
    SurfaceType surfaceType() const;

    void setVisible(bool visible);
    bool visible() const;

    void create();

    WId winId() const;

    QWindow *parent() const;
    void setParent(QWindow *parent);

    bool isTopLevel() const;

    bool isModal() const;
    Qt::WindowModality windowModality() const;
    void setWindowModality(Qt::WindowModality windowModality);

    void setFormat(const QSurfaceFormat &format);
    QSurfaceFormat format() const;

    void setWindowFlags(Qt::WindowFlags flags);
    Qt::WindowFlags windowFlags() const;
    Qt::WindowType windowType() const;

    QString windowTitle() const;

    void setOpacity(qreal level);
    void requestActivateWindow();

    Qt::WindowState windowState() const;
    void setWindowState(Qt::WindowState state);

    void setTransientParent(QWindow *parent);
    QWindow *transientParent() const;

    QSize minimumSize() const;
    QSize maximumSize() const;
    QSize baseSize() const;
    QSize sizeIncrement() const;

    void setMinimumSize(const QSize &size);
    void setMaximumSize(const QSize &size);
    void setBaseSize(const QSize &size);
    void setSizeIncrement(const QSize &size);

    void setGeometry(int x, int y, int w, int h) { setGeometry(QRect(x, y, w, h)); }
    void setGeometry(const QRect &rect);
    QRect geometry() const;

    inline int width() const { return geometry().width(); }
    inline int height() const { return geometry().height(); }
    inline int x() const { return geometry().x(); }
    inline int y() const { return geometry().y(); }

    inline QSize size() const { return geometry().size(); }
    inline QPoint pos() const { return geometry().topLeft(); }

    inline void move(const QPoint &pt) { setGeometry(QRect(pt, size())); }
    inline void move(int x, int y) { move(QPoint(x, y)); }

    inline void resize(const QSize &size) { setGeometry(QRect(pos(), size)); }
    inline void resize(int w, int h) { setGeometry(QRect(x(), y(), w, h)); }

    QMargins frameMargins() const;

    void setWindowIcon(const QImage &icon) const;

    void destroy();

    QPlatformWindow *handle() const;

    bool setKeyboardGrabEnabled(bool grab);
    bool setMouseGrabEnabled(bool grab);

    QScreen *screen() const;
    void setScreen(QScreen *screen);

    QPoint mapToGlobal(const QPoint &pos) const;
    QPoint mapFromGlobal(const QPoint &pos) const;

public Q_SLOTS:
    inline void show() { setVisible(true); }
    inline void hide() { setVisible(false); }

    void showMinimized();
    void showMaximized();
    void showFullScreen();
    void showNormal();

    bool close();
    void raise();
    void lower();

    void setWindowTitle(const QString &);

Q_SIGNALS:
    void backBufferReady();

protected:
    virtual void exposeEvent(QExposeEvent *);
    virtual void resizeEvent(QResizeEvent *);

    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

    virtual bool event(QEvent *);
    virtual void keyPressEvent(QKeyEvent *);
    virtual void keyReleaseEvent(QKeyEvent *);
    virtual void inputMethodEvent(QInputMethodEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseDoubleClickEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
#ifndef QT_NO_WHEELEVENT
    virtual void wheelEvent(QWheelEvent *);
#endif

    QWindow(QWindowPrivate &dd, QWindow *parent);

private:
    QPlatformSurface *surfaceHandle() const;

    Q_DISABLE_COPY(QWindow)

    friend class QGuiApplication;
    friend class QGuiApplicationPrivate;
    friend Q_GUI_EXPORT QWindowPrivate *qt_window_private(QWindow *window);
};

QT_END_NAMESPACE

QT_END_HEADER

#endif // QWINDOW_QPA_H
