#include "checkerSubString.h"

checker::checker(){
};


bool checker::checkSubString(std::string subSt, std::string st){
    if(subSt.size() > st.size())
        return false;
    std::string s = "*" + subSt + "#" + st;
    int cnt, l, r;
    cnt = l = r = 0;
    int n = s.size() - 1;
    
    //// reset the z function
    for(int i = 1; i <= n; ++i)
        z[i] = 0;
    ///

    for(int i = 1; i <= n; ++i){
        if(i > r)
            cnt = 1;
        else 
            cnt = std::min(z[i - l + 1], r - i + 1) + 1;
        
        while(i + cnt - 1 <= n && s[i + cnt - 1] == s[cnt])
            ++cnt;
        --cnt;
        z[i] = cnt;
        if(i + cnt - 1 > r){
            l = i;
            r = i + cnt - 1;
        }
        if(z[i] == subSt.size())
            return true;
    }
    return false;
}
