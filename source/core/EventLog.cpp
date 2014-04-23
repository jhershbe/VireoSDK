/**
 
Copyright (c) 2014 National Instruments Corp.
 
This software is subject to the terms described in the LICENSE.TXT file
 
SDG
*/

/*! \file
 */

#include "TypeAndDataManager.h"
#include "EventLog.h"

using namespace Vireo;

//------------------------------------------------------------
EventLog::EventLog(StringRef string)
{
    _traceEnabled = false;
    _errorLog = string;
    _softErrorCount = 0;
    _hardErrorCount = 0;
    _warningCount = 0;
}
//------------------------------------------------------------
void EventLog::LogEvent(EventSeverity severity, Int32 lineNumber, const char *message, SubString *extra)
{
    char buffer[200];

    const char* preamble;
    
    switch (severity) {
        case kTrace:
            preamble = "Trace";
            break;
        case kWarning:
            preamble = "Warning";
            break;
        case kSoftDataError:
            preamble = "Error";
            _softErrorCount++;
            break;
        case kHardDataError:
            preamble = "HardError";
            _hardErrorCount++;
            break;
        case kAssetFailure:
            preamble = "Assert";
            _hardErrorCount++;
            break;
        default:
            preamble = "Event";
            break;
    }
    
    // If there is a string to collect the messages then add them.
    if (_errorLog) {
        Int32 length;
        if (extra) {
            length = snprintf(buffer, sizeof(buffer), "(Line %d %s \"%s '%.*s'.\")\n", lineNumber, preamble, message, FMT_LEN_BEGIN(extra));
        } else {
            length = snprintf(buffer, sizeof(buffer), "(Line %d %s \"%s.\")\n", lineNumber, preamble, message);
        }
        _errorLog->Append(length, (const Utf8Char*)buffer);
    }
}

#if 0
DEFINE_VIREO_BEGIN(Vireo_EventLog)
    DEFINE_VIREO_FUNCTION(EventLogRecordEvent, "p(i(.String))")
DEFINE_VIREO_END()
#endif