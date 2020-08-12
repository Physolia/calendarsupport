/*
  SPDX-FileCopyrightText: 2004 Reinhold Kainhofer <reinhold@kainhofer.com>

  SPDX-License-Identifier: GPL-2.0-or-later WITH Qt-Commercial-exception-1.0
*/

#include "journalprint.h"
#include "utils.h"
#include <KConfigGroup>
#include "calendarsupport_debug.h"

using namespace CalendarSupport;

/**************************************************************
 *           Print Journal
 **************************************************************/

QWidget *CalPrintJournal::createConfigWidget(QWidget *w)
{
    return new CalPrintJournalConfig(w);
}

void CalPrintJournal::readSettingsWidget()
{
    CalPrintJournalConfig *cfg
        = dynamic_cast<CalPrintJournalConfig *>((QWidget *)mConfigWidget);
    if (cfg) {
        mFromDate = cfg->mFromDate->date();
        mToDate = cfg->mToDate->date();
        mUseDateRange = cfg->mRangeJournals->isChecked();
    }
}

void CalPrintJournal::setSettingsWidget()
{
    CalPrintJournalConfig *cfg
        = dynamic_cast<CalPrintJournalConfig *>((QWidget *)mConfigWidget);
    if (cfg) {
        cfg->mFromDate->setDate(mFromDate);
        cfg->mToDate->setDate(mToDate);

        if (mUseDateRange) {
            cfg->mRangeJournals->setChecked(true);
            cfg->mFromDateLabel->setEnabled(true);
            cfg->mFromDate->setEnabled(true);
            cfg->mToDateLabel->setEnabled(true);
            cfg->mToDate->setEnabled(true);
        } else {
            cfg->mAllJournals->setChecked(true);
            cfg->mFromDateLabel->setEnabled(false);
            cfg->mFromDate->setEnabled(false);
            cfg->mToDateLabel->setEnabled(false);
            cfg->mToDate->setEnabled(false);
        }
    }
}

void CalPrintJournal::loadConfig()
{
    if (mConfig) {
        KConfigGroup config(mConfig, "Journalprint");
        mUseDateRange = config.readEntry("JournalsInRange", false);
    }
    setSettingsWidget();
}

void CalPrintJournal::saveConfig()
{
    qCDebug(CALENDARSUPPORT_LOG);

    readSettingsWidget();
    if (mConfig) {
        KConfigGroup config(mConfig, "Journalprint");
        config.writeEntry("JournalsInRange", mUseDateRange);
    }
}

void CalPrintJournal::setDateRange(const QDate &from, const QDate &to)
{
    CalPrintPluginBase::setDateRange(from, to);
    CalPrintJournalConfig *cfg
        = dynamic_cast<CalPrintJournalConfig *>((QWidget *)mConfigWidget);
    if (cfg) {
        cfg->mFromDate->setDate(from);
        cfg->mToDate->setDate(to);
    }
}

void CalPrintJournal::print(QPainter &p, int width, int height)
{
    int x = 0, y = 0;
    KCalendarCore::Journal::List journals(mCalendar->journals());
    if (mUseDateRange) {
        const KCalendarCore::Journal::List allJournals = journals;
        journals.clear();
        for (const KCalendarCore::Journal::Ptr &j : allJournals) {
            const QDate dt = j->dtStart().date();
            if (mFromDate <= dt && dt <= mToDate) {
                journals.append(j);
            }
        }
    }

    QRect headerBox(0, 0, width, headerHeight());
    QRect footerBox(0, height - footerHeight(), width, footerHeight());
    height -= footerHeight();

    drawHeader(p, i18n("Journal entries"), QDate(), QDate(), headerBox);
    y = headerHeight() + 15;

    for (const KCalendarCore::Journal::Ptr &j : qAsConst(journals)) {
        drawJournal(j, p, x, y, width, height);
    }

    drawFooter(p, footerBox);
}
