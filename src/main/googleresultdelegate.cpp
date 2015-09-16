#include "googleresultdelegate.h"

GoogleResultDelegate::GoogleResultDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void GoogleResultDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString data = index.data().toString();
    if (data.endsWith(' ')) {
        QStyleOptionViewItem newOption = QStyleOptionViewItem(option);
        newOption.font.setItalic(true);
        newOption.font.setBold(true);
        QStyledItemDelegate::paint(painter, newOption, index);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
    //QListView *view = option.widget;
//    painter->save();
//    painter->translate(option.rect.left(), option.rect.top());
//    painter->setClipRect(option.rect);
//    painter->fillRect(option.rect, QColor(255, 0, 0));
//    painter->restore();

//    QStyleOptionViewItemV4 optionV4 = option;
//    initStyleOption(&optionV4, index);

//    QStyle *style = optionV4.widget? optionV4.widget->style() : QApplication::style();

//    QTextDocument doc;
//    doc.setHtml(optionV4.text);

//    /// Painting item without text
//    optionV4.text = QString();
//    style->drawControl(QStyle::CE_ItemViewItem, &optionV4, painter);

//    QAbstractTextDocumentLayout::PaintContext ctx;

//    // Highlighting text if item is selected
//    if (optionV4.state & QStyle::State_Selected)
//        ctx.palette.setColor(QPalette::Text, optionV4.palette.color(QPalette::Active, QPalette::HighlightedText));

//    QRect textRect = style->subElementRect(QStyle::SE_ItemViewItemText, &optionV4);
//    painter->save();
//    painter->translate(textRect.topLeft());
//    painter->setClipRect(textRect.translated(-textRect.topLeft()));
//    doc.documentLayout()->draw(painter, ctx);
//    painter->restore();
}

QSize GoogleResultDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setHeight(option.fontMetrics.height());
    return size;
//    QStyleOptionViewItemV4 optionV4 = option;
//    initStyleOption(&optionV4, index);

//    QTextDocument doc;
//    doc.setHtml(optionV4.text);
//    doc.setTextWidth(optionV4.rect.width());
//    return QSize(doc.idealWidth(), doc.size().height());
}
