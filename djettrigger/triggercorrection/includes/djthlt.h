#ifndef DJTHLT_H_
#define DJTHLT_H_

namespace djthlt
{
  bool checkHlt(const djet &djt, float jetpt, int ispp, int fileno)
  {
    bool result = true;
    if(ispp)
      {
        if(jetpt >= 40 && jetpt < 60 && (!djt.HLT_AK4Jet40 || fileno==1)) result = false;
        if(jetpt >= 60 && jetpt < 80 && (!djt.HLT_AK4Jet60 || fileno==1)) result = false;
        if(jetpt >= 80 && jetpt < 100 && (!djt.HLT_AK4Jet80 || fileno==0)) result = false;
        if(jetpt >= 100 && (!djt.HLT_AK4Jet80 || fileno==0)) result = false;

        // if((jetpt > 40 && jetpt < 60 && (!djt.HLT_AK4Jet40 || fileno==1)) ||
        //    (jetpt > 60 && jetpt < 80 && (!djt.HLT_AK4Jet60 || fileno==1)) ||
        //    (jetpt > 80 && (!djt.HLT_AK4Jet80 || fileno==0))) 
        //   result = false;
      }
    else
      {
        if(jetpt >= 40 && jetpt < 60 && !djt.HLT_AK4Jet40) result = false;
        if(jetpt >= 60 && jetpt < 80 && !djt.HLT_AK4Jet60) result = false;
        if(jetpt >= 80 && jetpt < 100 && !djt.HLT_AK4Jet80) result = false;
        if(jetpt >= 100 && !djt.HLT_AK4Jet100) result = false;

        // if((jetpt > 40 && jetpt < 60 && !djt.HLT_AK4Jet40) ||
        //    (jetpt > 60 && jetpt < 80 && (!djt.HLT_AK4Jet40 && !djt.HLT_AK4Jet60)) ||
        //    (jetpt > 80 && (!djt.HLT_AK4Jet40 && !djt.HLT_AK4Jet60 && !djt.HLT_AK4Jet80)))
        //   result = false;

        // if(!djt.HLT_AK4Jet40 && !djt.HLT_AK4Jet60 && !djt.HLT_AK4Jet80) 
        //   result = false;
      }
    return result;
  }
}

#endif
