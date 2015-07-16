#pragma once

#include <QString>
#include <QFrame>
#include <QIcon>

// implement this in all plugins
struct Metadata
{
public:
    // plugin name to be displayed in the interface
    virtual QString name() = 0;
    // plugin icon, you can return an empty QIcon()
    virtual QIcon icon() = 0;
    // optional destructor
    virtual ~Metadata() {}
};

// implement this in filters
struct IFilter
{
public:
    // optional destructor
    virtual ~IFilter() {}
    // perform filtering step.
    // you have to take care of dt on your own, try "opentrack/timer.hpp"
    virtual void filter(const double *input, double *output) = 0;
};

struct IFilterDialog : public QWidget
{
    // optional destructor
    virtual ~IFilterDialog() {}
    // receive a pointer to thefilter from ui thread
    virtual void register_filter(IFilter* filter) = 0;
    // received filter pointer is about to get deleted
    virtual void unregister_filter() = 0;
};

// call once with your chosen class names in the plugin
#define OPENTRACK_DECLARE_FILTER(filter_class, dialog_class, metadata_class) \
    OPENTRACK_DECLARE_PLUGIN_INTERNAL(filter_class, IFilter, metadata_class, dialog_class, IFilterDialog)

// implement this in protocols
struct IProtocol
{
public:
    // optional destructor
    virtual ~IProtocol() {}
    // return true if protocol was properly initialized
    virtual bool correct() = 0;
    // called 250 times a second with XYZ yaw pitch roll pose
    // try not to perform intense computation here. if you must, use a thread.
    virtual void pose(const double* headpose) = 0;
    // return game name or placeholder text
    virtual QString game_name() = 0;
};

struct IProtocolDialog : public QWidget
{
    // optional destructor
    virtual ~IProtocolDialog() {}
    // receive a pointer to theprotocol from ui thread
    virtual void register_protocol(IProtocol *protocol) = 0;
    // received protocol pointer is about to get deleted
    virtual void unregister_protocol() = 0;
};

// call once with your chosen class names in the plugin
#define OPENTRACK_DECLARE_PROTOCOL(protocol_class, dialog_class, metadata_class) \
    OPENTRACK_DECLARE_PLUGIN_INTERNAL(protocol_class, IProtocol, metadata_class, dialog_class, IProtocolDialog)

// implement this in trackers
struct ITracker
{
public:
    // optional destructor
    virtual ~ITracker() {}
    // start tracking, and grab a frame to display webcam video in, optionally
    virtual void start_tracker(QFrame* frame) = 0;
    // return XYZ yaw pitch roll data. don't block here, use a separate thread for computation.
    virtual void data(double *data) = 0;
};

struct ITrackerDialog : public QWidget
{
    // optional destructor
    virtual ~ITrackerDialog() {}
    // receive a pointer to thetracker from ui thread
    virtual void register_tracker(ITracker *tracker) = 0;
    // received tracker pointer is about to get deleted
    virtual void unregister_tracker() = 0;
};
