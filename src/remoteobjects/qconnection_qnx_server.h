/****************************************************************************
**
** Copyright (C) 2014-2016 Ford Motor Company
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

#ifndef QQNXNATIVESERVER_H
#define QQNXNATIVESERVER_H

#include <QtNetwork/qabstractsocket.h>
#include <QtRemoteObjects/qtremoteobjectglobal.h>

QT_BEGIN_NAMESPACE

class QQnxNativeServerPrivate;
class QQnxNativeIo;
class QIOQnxSource;

class Q_REMOTEOBJECTS_EXPORT QQnxNativeServer : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QQnxNativeServer)

Q_SIGNALS:
    void newConnection();

public:
    explicit QQnxNativeServer(QObject *parent = 0);
    ~QQnxNativeServer();

    void close();
    bool hasPendingConnections() const;
    bool isListening() const;
    bool listen(const QString &name);
    QIOQnxSource *nextPendingConnection();
    QString serverName() const;
    bool waitForNewConnection(int msec = 0, bool *timedOut = 0);

private Q_SLOTS:
    void onSourceClosed();

private:
    Q_DISABLE_COPY(QQnxNativeServer)
    friend class QIOQnxSource;
};

QT_END_NAMESPACE

#endif // QQNXNATIVESERVER_H
