/*
  SPDX-FileCopyrightText: 2005 Rafal Rzepecki <divide@users.sourceforge.net>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "calendarsupport_export.h"

#include <QVariant>

class QComboBox;

namespace CalendarSupport
{
class CALENDARSUPPORT_EXPORT CategoryHierarchyReader
{
public:
    void read(const QStringList &categories);
    virtual ~CategoryHierarchyReader() = default;

    static QStringList path(QString string);

protected:
    CategoryHierarchyReader() = default;

    virtual void clear() = 0;
    virtual void goUp() = 0;
    virtual void addChild(const QString &label, const QVariant &userData = QVariant()) = 0;
    virtual int depth() const = 0;
};

class CALENDARSUPPORT_EXPORT CategoryHierarchyReaderQComboBox : public CategoryHierarchyReader
{
public:
    explicit CategoryHierarchyReaderQComboBox(QComboBox *box)
        : mBox(box)
    {
    }

    ~CategoryHierarchyReaderQComboBox() override = default;

protected:
    void clear() override;
    void goUp() override;
    void addChild(const QString &label, const QVariant &userData = QVariant()) override;
    int depth() const override;

private:
    QComboBox *const mBox;
    int mCurrentDepth = 0;
};

}
