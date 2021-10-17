#ifndef MEOW_THREADS_QUERY_TASK_H
#define MEOW_THREADS_QUERY_TASK_H

#include <QStringList>
#include "thread_task.h"
#include "db/user_query/batch_executor.h"
#include "db/query.h"

namespace meow {

namespace db {
using SQLBatch = QStringList;
class Connection;
}



namespace threads {

class QueryTask : public ThreadTask
{
public:
    QueryTask(const db::SQLBatch & queries, db::Connection * connection);
    ~QueryTask() override;
    void run() override;
    bool isFailed() const override;
    QString errorMessage() const;
    const QList<db::QueryPtr> results() const;
private:
    db::SQLBatch _queries;
    db::Connection * _connection;
    db::user_query::BatchExecutor _executor;
};


} // namespace threads
} // namespace meow

#endif // MEOW_THREADS_QUERY_TASK_H
