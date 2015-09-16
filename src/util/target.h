#ifndef TARGET_H
#define TARGET_H

#include <QListWidgetItem>

class Target : public QObject, public QListWidgetItem
{
    Q_OBJECT
private:
    QString name;
    QString command;
    QString query;
    bool enabled;
    QString hotKey;

//    static QBrush const & disabledBrush();
//    Q_GLOBAL_STATIC_WITH_ARGS(QBrush, disabledBrush, (QColor(150, 150, 150)))

public:
    enum Type {
        TargetType = 0x451
    };

    explicit Target(QListWidget *parent = 0) : QListWidgetItem(parent, TargetType){}

    inline QString const & getName() const {return name;} //*(new QString(qvariant_cast<QString>(data(Qt::DisplayRole))));}
    inline QString const & getCommand() const {return command;}
    inline QString const & getQuery() const {return query;}
    inline bool const & isEnabled() const {return enabled;}
    inline QString const & getHotKey() const {return hotKey;}

signals:
    
public slots:
    inline void setName(QString const & newName) {
        name = newName;
        setData(Qt::DisplayRole, newName);

        //Not viable, since setData() creates a copy anyways
        //{name = newName; setData(Qt::DisplayRole, name); name.append("YO!");}
    }
    inline void setCommand(QString const & newCommand = "") {command = newCommand;}
    inline void setQuery(QString const & newQuery = "") {query = newQuery;}
    inline void setEnabled(bool const & newEnabled) {
        enabled = newEnabled;
        if (enabled) {
            setData(Qt::ForegroundRole, 0);
        } else {

            ///Decided not to use, since setData creates a copy anyways... BUMMER!! Lost the whole afternoon messing with static
            //Static variables inside an inline function always point to the same address
            //The solution of using a static private variable in the header means every translation unit (.cpp importing .h) would have it's own copy of the variable, hence not really static
            //The solution of using a static private variable in the header and defined in the .cpp would solve, but with a longer approach. It is best used if the variable would be shared across multiple functions
            //static QBrush const disabledBrush(QColor(150, 150, 150));

            setData(Qt::ForegroundRole, QBrush(QColor(150, 150, 150)));
        }
    }
    inline void setHotKey(QString const & newHotKey = "") {hotKey = newHotKey;}
};

#endif // TARGET_H
