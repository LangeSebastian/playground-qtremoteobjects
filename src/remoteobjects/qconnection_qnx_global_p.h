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

#ifndef QNXIPCPRIVATE_GLOBAL_H
#define QNXIPCPRIVATE_GLOBAL_H

#include <sys/neutrino.h>
#include <sys/dispatch.h>
#include <sys/siginfo.h>
#include <unistd.h> // provides SETIOV
#include <sys/netmgr.h>  //FOR ND_LOCAL_NODE
#include <errno.h>
#include <QThread>
#ifdef USE_HAM
# include <ha/ham.h>
#endif

#define WARNING(cmd) qCWarning(QT_REMOTEOBJECT) << "Warning " #cmd << strerror(errno) \
                        << Q_FUNC_INFO << __FILE__ << __LINE__;

#define WARN_ON_ERROR(cmd, ...) if (cmd(__VA_ARGS__) == -1) qCWarning(QT_REMOTEOBJECT) \
                        << "Error " #cmd << strerror(errno) << Q_FUNC_INFO << __FILE__ << __LINE__;

#define WARN_AND_RETURN_ON_ERROR(cmd, retval, ...) if (cmd(__VA_ARGS__) == -1) \
                        { qCWarning(QT_REMOTEOBJECT) << "Error " #cmd << strerror(errno) \
                        << Q_FUNC_INFO << __FILE__ << __LINE__; return (retval); }

#define FATAL_ON_ERROR(cmd, ...) if (cmd(__VA_ARGS__) == -1) qFatal("Error %s: %s %s %s %d", \
                        #cmd, strerror(errno), Q_FUNC_INFO, __FILE__, __LINE__);

const int MAX_RETRIES = 3;

enum MsgType : uint16_t { REPLICA_INIT = _IO_MAX+100,
                          REPLICA_TX_RECV,
                          SOURCE_TX_RESP,
                          SOURCE_TX_RESP_REPEAT,
                        };
enum PulseType : uint8_t { SOURCE_TX_RQ = _PULSE_CODE_MINAVAIL+42,
                           REPLICA_WRITE,
                           TERMINATE,
                           NODE_DEATH
                         };
union recv_msgs
{
    struct _pulse pulse;
    uint16_t type;
};

template <typename T>
class Thread : public QThread
{
public:
    Thread(T *obj, const QString &name = QString()) : QThread(), m_obj(obj)
    {
        if (!name.isEmpty())
            setObjectName(name);
    }
    void run() Q_DECL_OVERRIDE
    {
        m_obj->thread_func();
    }
private:
    T *m_obj;
};

#endif // QNXIPCPRIVATE_GLOBAL_H

