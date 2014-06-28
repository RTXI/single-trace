/**
 * Record a Single trace
 */

#include <default_gui_model.h>
#include <string>
#include <DataLogger.cpp>

class SimpleTrace : public DefaultGUIModel
{

public:

    SimpleTrace(void);
    virtual ~SimpleTrace(void);
    virtual void execute(void);

protected:

    virtual void update(DefaultGUIModel::update_flags_t);

private:
    double V, Iout;
    double dt;
    double len;
    
    // DataLogger
    DataLogger data;
    int acquire;
    double  tcnt;
    int cellnum;
    string prefix, info;
    vector<double> newdata;
    
};
