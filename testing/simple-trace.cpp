/**
 * Record a single trace and nothing more
 */

#include <simple-trace.h>
#include <iostream>
     
#define EPS 1e-9

extern "C" Plugin::Object *createRTXIPlugin(void) {
    return new SimpleTrace();
}

static DefaultGUIModel::variable_t vars[] = {
    {
        "Vin",
        "",
        DefaultGUIModel::INPUT,
    },
    {
        "Record Length (s)",
        "How many seconds to record for",
        DefaultGUIModel::PARAMETER | DefaultGUIModel::DOUBLE,
    },
    {
        "Acquire?",
        "Acquire data 0 = no, 1 = yes",
        DefaultGUIModel::PARAMETER | DefaultGUIModel::UINTEGER,
    },
    {
        "Cell (#)",
        "",
        DefaultGUIModel::PARAMETER | DefaultGUIModel::UINTEGER,
    },
    {
        "File Prefix",
        "",
        DefaultGUIModel::PARAMETER,
    },
    {
        "File Info",
        "",
        DefaultGUIModel::PARAMETER,
    },
};

static size_t num_vars = sizeof(vars)/sizeof(DefaultGUIModel::variable_t);

SimpleTrace::SimpleTrace(void)
    : DefaultGUIModel("SimpleTrace",::vars,::num_vars), dt(RT::System::getInstance()->getPeriod()*1e-6),
    len(1.0),
    acquire(0), cellnum(1), prefix("SimpleTrace"), info("n/a") {


    // clear temp data vector
    newdata.clear();

    update(INIT);
    refresh();
}




SimpleTrace::~SimpleTrace(void) {}

void SimpleTrace::execute(void) {

    // do nothing more than save a trace
    V = input(0);

    if (tcnt < (len - EPS)) {

        // count forward make sure we are using seconds
        tcnt += dt / 1000;

        // log data if needed
        if (acquire) {
            newdata.push_back(tcnt);
            newdata.push_back(V);
            data.insertdata(newdata);
            newdata.clear();
        }
    } else if (acquire) {

        // set acq to 0 first so we're sure we are stopping 
        // to collect data before writebuffer() breaks realtime
        acquire = 0;
        data.writebuffer(prefix, info);
        data.resetbuffer();
        
        setParameter("Acquire?", acquire);
    }
}



void SimpleTrace::update(DefaultGUIModel::update_flags_t flag) 
{

    switch(flag) {
        case INIT:
            setParameter("Record Length (s)", len);
            
            setParameter("Acquire?",acquire);
            setParameter("Cell (#)",cellnum);
            setParameter("File Prefix", prefix);
            setParameter("File Info", info);
            
            break;
        case MODIFY:
            len = getParameter("Record Length (s)").toDouble();

            acquire = getParameter("Acquire?").toInt();
            cellnum = getParameter("Cell (#)").toInt();
            prefix = getParameter("File Prefix").data();
            info = getParameter("File Info").data();

            data.newcell(cellnum);
            data.resetbuffer();
            tcnt = 0;

            break;
        case PAUSE:
            output(0) = 0;
        case PERIOD:
            dt = RT::System::getInstance()->getPeriod()*1e-6;
        default:
            break;
    }

    // Some Error Checking for fun
    if (len < 0.0) {
        setParameter("Record Length (s)", 0.0);
        refresh();
    }
}



