#ifndef GOOGLERESULTDELEGATE_H
#define GOOGLERESULTDELEGATE_H

#include <QStyledItemDelegate>

class GoogleResultDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit GoogleResultDelegate(QObject *parent = 0);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    
};

#endif // GOOGLERESULTDELEGATE_H
