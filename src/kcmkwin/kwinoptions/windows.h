/*
    windows.h

    SPDX-FileCopyrightText: 1997 Patrick Dowler <dowler@morgul.fsh.uvic.ca>
    SPDX-FileCopyrightText: 2001 Waldo Bastian <bastian@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef KKWMWINDOWS_H
#define KKWMWINDOWS_H

#include <QWidget>
#include <kcmodule.h>

#include "ui_advanced.h"
#include "ui_focus.h"
#include "ui_moving.h"

class QRadioButton;
class QCheckBox;
class QPushButton;
class KComboBox;
class QGroupBox;
class QLabel;
class QSlider;
class QGroupBox;
class QSpinBox;

class KColorButton;

class KWinOptionsSettings;
class KWinOptionsKDEGlobalsSettings;

class KWinFocusConfigForm : public QWidget, public Ui::KWinFocusConfigForm
{
    Q_OBJECT

public:
    explicit KWinFocusConfigForm(QWidget* parent);
};

class KWinMovingConfigForm : public QWidget, public Ui::KWinMovingConfigForm
{
    Q_OBJECT

public:
    explicit KWinMovingConfigForm(QWidget* parent);
};

class KWinAdvancedConfigForm : public QWidget, public Ui::KWinAdvancedConfigForm
{
    Q_OBJECT

public:
    explicit KWinAdvancedConfigForm(QWidget* parent);
};

class KFocusConfig : public KCModule
{
    Q_OBJECT
public:
    KFocusConfig(bool _standAlone, KWinOptionsSettings *settings, QWidget *parent);

    void load() override;
    void save() override;
    void defaults() override;

    bool isDefaults() const;
    bool isSaveNeeded() const;

protected:
    void initialize(KWinOptionsSettings *settings);
    void showEvent(QShowEvent *ev) override;

private Q_SLOTS:
    void focusPolicyChanged();
    void updateMultiScreen();
    void updateDefaultIndicator();

private:
    bool     standAlone;
    bool m_unmanagedChangeState = false;
    bool m_unmanagedDefaultState = true;

    KWinFocusConfigForm *m_ui;
    KWinOptionsSettings *m_settings;
};

class KMovingConfig : public KCModule
{
    Q_OBJECT
public:
    KMovingConfig(bool _standAlone, KWinOptionsSettings *settings, QWidget *parent);

    void save() override;

    bool isDefaults() const;
    bool isSaveNeeded() const;

protected:
    void initialize(KWinOptionsSettings *settings);
    void showEvent(QShowEvent *ev) override;

private:
    KWinOptionsSettings *m_settings;
    bool     standAlone;
    KWinMovingConfigForm *m_ui;
};

class KAdvancedConfig : public KCModule
{
    Q_OBJECT
public:
    KAdvancedConfig(bool _standAlone, KWinOptionsSettings *settings, KWinOptionsKDEGlobalsSettings *globalSettings, QWidget *parent);

    void save() override;

    bool isDefaults() const;
    bool isSaveNeeded() const;

protected:
    void initialize(KWinOptionsSettings *settings, KWinOptionsKDEGlobalsSettings *globalSettings);
    void showEvent(QShowEvent *ev) override;

private:

    bool     standAlone;
    KWinAdvancedConfigForm *m_ui;
    KWinOptionsSettings *m_settings;
};

#endif // KKWMWINDOWS_H
