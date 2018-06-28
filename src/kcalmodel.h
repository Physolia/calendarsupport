/*
  Copyright (c) 2008 Bruno Virlet <bvirlet@kdemail.net>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.
*/

#ifndef CALENDARSUPPORT_KCALMODEL_H
#define CALENDARSUPPORT_KCALMODEL_H

#include <ItemModel>

namespace CalendarSupport {
class KCalModel : public Akonadi::ItemModel
{
public:
    enum Column {
        Summary,
        DateTimeStart,
        DateTimeEnd,
        Type
    };

    explicit KCalModel(QObject *parent = nullptr);

    ~KCalModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    /**
      Reimplemented from QAbstractItemModel.
    */
    Q_REQUIRED_RESULT QStringList mimeTypes() const override;

private:
    class Private;
    Private *const d;
};
}

#endif
