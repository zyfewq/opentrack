#pragma once
#include "ui_test.h"
#include "api/plugin-api.hpp"
#include "compat/timer.hpp"

#include <cmath>

class test_tracker : public ITracker
{
public:
    test_tracker();
    ~test_tracker() override;
    void start_tracker(QFrame *) override;
    void data(double *data) override;

private:
    static constexpr double r2d = 180 / M_PI;
    static constexpr double d2r = M_PI / 180;

    static const double incr[6];
    double last_x[6];
    Timer t;
};

class dialog: public ITrackerDialog
{
    Q_OBJECT

    Ui::test_ui ui;
public:
    dialog();
    void register_tracker(ITracker *) override {}
    void unregister_tracker() override {}
private slots:
    void doOK();
    void doCancel();
};

class metadata : public Metadata
{
public:
    QString name() { return QString(QCoreApplication::translate("metadata", "Testing - sine wave")); }
    QIcon icon() { return QIcon(":/images/facetracknoir.png"); }
};

