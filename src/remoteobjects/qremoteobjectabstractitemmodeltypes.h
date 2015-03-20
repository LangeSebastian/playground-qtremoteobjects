/****************************************************************************
**
** Copyright (C) 2014 Ford Motor Company
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtRemoteObjects module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QREMOTEOBJECTS_ABSTRACT_ITEM_MODEL_TYPES_H
#define QREMOTEOBJECTS_ABSTRACT_ITEM_MODEL_TYPES_H

#include <QList>
#include <QVector>
#include <QPair>
#include <QVariant>
#include <QModelIndex>
#include <QDebug>
#include <qnamespace.h>
#include <QtRemoteObjects/qtremoteobjectglobal.h>

QT_BEGIN_NAMESPACE

struct ModelIndex
{
    ModelIndex() : row(-1), column(-1) {}
    ModelIndex(int row, int column)
        : row(row)
        , column(column)
    {}

    inline bool operator==(const ModelIndex &other) const { return row == other.row && column == other.column; }
    inline bool operator!=(const ModelIndex &other) const { return !(*this == other); }
    int row;
    int column;
};

inline QDebug& operator<<(QDebug &stream, const ModelIndex &index)
{
    return stream.nospace() << "ModelIndex[row=" << index.row << ", column=" << index.column << "]";
}

inline QDataStream& operator<<(QDataStream &stream, const ModelIndex &index)
{
    return stream << index.row << index.column;
}

inline QDataStream& operator>>(QDataStream &stream, ModelIndex &index)
{
    return stream >> index.row >> index.column;
}

inline QDataStream& operator<<(QDataStream &stream, Qt::Orientation orient)
{
    return stream << static_cast<int>(orient);
}

inline QDataStream& operator>>(QDataStream &stream, Qt::Orientation &orient)
{
    int val;
    QDataStream &ret = stream >> val;
    orient = static_cast<Qt::Orientation>(val);
    return ret;
}

typedef QList<ModelIndex> IndexList;

typedef QPair<IndexList, QVariantList> IndexValuePair;

typedef QVector<IndexValuePair> DataEntries;

inline QModelIndex toQModelIndex(const IndexList &list, const QAbstractItemModel *model)
{
    QModelIndex result;
    Q_FOREACH (const ModelIndex &index, list)
        result = model->index(index.row, index.column, result);
    return result;
}

inline IndexList toModelIndexList(const QModelIndex &index, const QAbstractItemModel *model)
{
    IndexList list;
    list << ModelIndex(index.row(), index.column());
    for (QModelIndex curIndex = model->parent(index); curIndex.isValid(); curIndex = model->parent(curIndex))
        list << ModelIndex(curIndex.row(), curIndex.column());
    return list;
}

Q_DECLARE_METATYPE(ModelIndex)
Q_DECLARE_METATYPE(IndexList)
Q_DECLARE_METATYPE(DataEntries)
Q_DECLARE_METATYPE(IndexValuePair)
Q_DECLARE_METATYPE(Qt::Orientation)

QT_END_NAMESPACE

#endif // QREMOTEOBJECTS_ABSTRACT_ITEM_MODEL_TYPES_H
