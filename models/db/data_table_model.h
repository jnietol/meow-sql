#ifndef DATA_TABLE_MODEL_H
#define DATA_TABLE_MODEL_H

#include <QObject>
#include "query_data_sort_filter_proxy_model.h"
#include "base_data_table_model.h"
#include "db/common.h"

// Main Window
//   Central Right Widget
//     Data Tab
//       Table Model

namespace meow {
namespace models {
namespace db {

class DataTableModel : public BaseDataTableModel
{
    Q_OBJECT
public:
    explicit DataTableModel(QObject *parent = nullptr);
    virtual ~DataTableModel() override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index,
                 const QVariant &value,
                 int role = Qt::EditRole) override;

    void setEntity(meow::db::Entity * tableOrViewEntity, bool loadData = true);
    void removeData();
    void loadData(bool force = false);
    void refresh();
    void invalidateData();

    void setNoRowsCountLimit();
    void incRowsCountForOneStep(bool reset = false);
    bool isLimited() const;
    bool allDataLoaded() const;

    QString rowCountStats() const;

    bool isEditable() const;
    bool isEditing();
    bool isModified();

    void applyModifications(int rowToApply = -1);
    void discardModifications();

    void setCurrentRowNumber(int row);

    bool deleteRowInDB(int row);

    int insertEmptyRow();

    QAbstractItemModel * createSortFilterModel();

    void setFilterPattern(const QString & pattern, bool regexp);
    QString filterPattern() const;
    bool filterPatternIsRegexp() const { return _filterPatternIsRegexp; }

    int filterMatchedRowCount() const;

    Q_SIGNAL void editingStarted();

    QModelIndex mapToSource(const QModelIndex &proxyIndex) const {
        if (_sortFilterModel) {
            return _sortFilterModel->mapToSource(proxyIndex);
        } else {
            return proxyIndex;
        }
    }

    QModelIndexList mapToSource(const QModelIndexList &proxyIndexList) const {
        if (_sortFilterModel) {
            QModelIndexList result = proxyIndexList;
            for (auto & index : result) {
                index = _sortFilterModel->mapToSource(index);
            }
            return result;
        } else {
            return proxyIndexList;
        }
    }

    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const {
        if (_sortFilterModel) {
            return _sortFilterModel->mapFromSource(sourceIndex);
        } else {
            return sourceIndex;
        }
    }

    QModelIndexList mapFromSource(const QModelIndexList &sourceIndexList) const {
        if (_sortFilterModel) {
            QModelIndexList result = sourceIndexList;
            for (auto & index : result) {
                index = _sortFilterModel->mapFromSource(index);
            }
            return result;
        } else {
            return sourceIndexList;
        }
    }

    QModelIndex createIndexForRow(int row) {
        return createIndex(row, 0);
    }

private:

    QueryDataSortFilterProxyModel * _sortFilterModel;
    QString _filterPattern;
    bool _filterPatternIsRegexp;

    bool _entityChangedProcessed;
    meow::db::Entity * _dbEntity;
    meow::db::ulonglong _wantedRowsCount;
};


} // namespace db
} // namespace models
} // namespace meow

#endif // DATA_TABLE_MODEL_H
