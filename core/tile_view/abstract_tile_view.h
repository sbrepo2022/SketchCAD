#ifndef ABSTRACTTILEVIEW_H
#define ABSTRACTTILEVIEW_H

#include <QWidget>

class AbstractTileView : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractTileView(QWidget *parent = nullptr);

signals:

};

#endif // ABSTRACTTILEVIEW_H
