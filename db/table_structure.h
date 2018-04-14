#ifndef DB_TABLE_STRUCTURE_H
#define DB_TABLE_STRUCTURE_H

#include <QObject>
#include "db/common.h"
#include "table_column.h"
#include "table_index.h"
#include "foreign_key.h"

namespace meow {
namespace db {

class TableEntity;

// Holds table structure items and additional options
class TableStructure : public QObject
{
    Q_OBJECT

public:
    TableStructure(TableEntity * table);
    virtual ~TableStructure();

    TableEntity * table() const { return _table; }
    void setTable(TableEntity * table);

    const QList<TableColumn *> & columns() const { return _columns; }
    void clearColumns() { qDeleteAll(_columns); _columns.clear(); }
    void appendColumn(TableColumn * column);

    QList<TableIndex  *> & indicies() { return _indicies; }
    void appendIndex(TableIndex * index);

    QList<ForeignKey  *> & foreighKeys() { return _foreignKeys; }

    QString rowFormatStr() const { return _rowFormatStr; }
    void setRowFormat(const QString & format) { _rowFormatStr = format; }

    db::ulonglong avgRowLen() const { return _avgRowLen; }
    void setAvgRowLen(db::ulonglong len) { _avgRowLen = len; }

    db::ulonglong autoInc() const { return _autoInc; }
    void setAutoInc(db::ulonglong inc) { _autoInc = inc; }

    db::ulonglong maxRows() const { return _maxRows; }
    void setMaxRows(db::ulonglong maxRows) { _maxRows = maxRows; }

    bool isCheckSum() const { return _isCheckSum; }
    void setCheckSum(bool checksum) { _isCheckSum = checksum; }

    QString comment() const { return _comment; }
    void setComment(const QString & comment) { _comment = comment; }

    bool hasIndexForColumn(const QString & columnName, TableIndexClass indexClass);

    TableStructure * deepCopy(TableEntity * parentTable) const;

    int insertEmptyDefaultColumn(int afterIndex = -1);
    TableIndex * insertEmptyDefaultIndex();
    int insertEmptyDefaultColumnToIndex(int index);

    bool canRemoveColumn(int index) const;
    bool removeColumnAt(int index);

    bool canMoveColumnUp(int index) const;
    bool moveColumnUp(int index);

    bool canMoveColumnDown(int index) const;
    bool moveColumnDown(int index);

    bool canRemoveAllIndices() const;
    void removeAllIndicies();

    bool isValidIndex(int index) const;

    bool canRemoveIndex(int index) const;
    bool removeIndexAt(int index);

    bool canRemoveIndexColumn(int index, int column) const;
    bool removeIndexColumn(int index, int column);

    bool canMoveIndexColumnUp(int index, int column) const;

    bool canMoveIndexColumnDown(int index, int column) const;

    unsigned nextColumnUniqueId() { return ++_nextColumnUniqueId; }
    TableColumn * columnById(unsigned id) const;
    TableColumn * columnByName(const QString & name) const;
    TableColumn * prevColumn(TableColumn * column) const;

    unsigned nextIndexUniqueId() { return ++_nextIndexUniqueId; }
    TableIndex * indexById(unsigned id) const;

    Q_SIGNAL void beforeColumnRemoved(const QString & name);

private:

    TableEntity * _table;

    QString _comment;
    QString _rowFormatStr;
    db::ulonglong _avgRowLen;
    db::ulonglong _autoInc;
    db::ulonglong _maxRows;
    bool _isCheckSum;

    QList<TableColumn *>  _columns;
    QList<TableIndex  *>  _indicies;
    QList<ForeignKey  *>  _foreignKeys;

    unsigned _nextColumnUniqueId;
    unsigned _nextIndexUniqueId;

};

} // namespace db
} // namespace meow

#endif // DB_TABLE_STRUCTURE_H
