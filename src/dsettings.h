#pragma once

#include <string>

// static methods - no need to instantiate

class DSettings
{

	public:

    enum DSoundType
    {
        DSYNTHSUB,
        DSYNTHFM,
        DSYNTHVAR,
        DSAMPLER,
        DRUM
        // more to come: mixer, fx, seq etc
    };

    enum DSoundSubType
    {
        NONE,
        DBASS,
        DSNARE,
        DHIHAT,
        DCLAP,
        DCYMBAL,
        DDRUM
    };

    DSettings() {}
    ~DSettings() {}
    
    void static SaveSetting(DSoundType type, DSoundSubType subtype, string file_name, void *config);
    void static LoadSetting(DSoundType type, DSoundSubType subtype, string file_name, void *config);

private:

    std::string static VecToStr(std::vector<float> vec);
    std::vector<float> static StrToVec(std::string str);
};
