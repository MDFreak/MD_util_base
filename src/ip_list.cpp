/*************************************************************************
|  Filename..............: ip_list.cpp
 * Project...............: part of standard utilities
 * Autor.................: Martin Dorfner (MD)
 * Date .................: 20.11.2020
 *-----------------------------------------------------------------------
 * Function:
 *   provide a list containing network login data
 *-----------------------------------------------------------------------
 * Dependecies:
 *   md_defines.h    (utility intern)
 *   linked_list.hpp (utility intern)
 *   ip_list.hpp
 ************************************************************************
 * Version| Date   | Changes                                    | Autor
 *-----------------------------------------------------------------------
 * 0.1.0  |20.11.20| import from former project                 | MD
*-----------------------------------------------------------------------*/

#include <ip_list.hpp>

// ---------------------------
// class ip_cell
  ip_cell::ip_cell() : md_cell()
    {
                #if (MDIP_DEBUG > CFG_DEBUG_NONE)
                  SOUT(millis()); SOUT(" ip_cell new "); SOUTHEXLN((u_long) this);
                #endif
    }
  ip_cell::~ip_cell()
    {
                #if (MDIP_DEBUG > CFG_DEBUG_NONE)
                  SOUT(millis()); SOUT(" ip_cell del me "); SOUTHEXLN((u_long) this);
                #endif
    }
  //
  void ip_cell::init(uint32_t locIP, uint32_t gwIP, uint32_t snIP,
                       const char ssid[NET_MAX_SSID_LEN],
                       const char pw[NET_MAX_PW_LEN])
    {
      _locIP = locIP;
      _gwIP  = gwIP;
      _snIP  = snIP;
      strncpy(_ssid, ssid, NET_MAX_SSID_LEN);
      strncpy(_pw, pw, NET_MAX_PW_LEN);
                #if (MDIP_DEBUG > CFG_DEBUG_NONE)
                  SOUT(millis()); SOUT(" ip_cell init _locIP "); SOUTHEX(_locIP); SOUT("  _ssid "); SOUTLN(_ssid);
                #endif
    }

// ---------------------------
// class ip_list
  ip_list::ip_list() : md_list()
    {
                #if (MDIP_DEBUG > CFG_DEBUG_NONE)
                  SOUT(millis()); SOUT(" ip_list new");  SOUTHEXLN((u_long) this);
                #endif
    }

  ip_list::~ip_list()
    {
      ip_cell* pip = NULL;
      void*    ptmp = NULL;
      uint16_t cnt  = this->count();
                #if (MDIP_DEBUG > CFG_DEBUG_NONE)
                  SOUT(millis()); SOUT(" ip_list delete me");  SOUTHEX((u_long) this);
              	  SOUT(" count "); SOUTLN(this->count());
                #endif
      while (cnt > 0)
        {
          ptmp = this->pFirst();
          pip = (ip_cell*) ptmp;
          rem(OFIRST);
          if (cnt > this->count())
            {
                    #if (MDIP_DEBUG > CFG_DEBUG_NONE)
                      SOUT(" delete first "); SOUTHEXLN((u_long) pip);
                    #endif
              delete( (ip_cell*) pip ) ;
              cnt--;
            }
        }
                    //SOUT(millis()); SOUT(" ip_list deleted ");  SOUTHEXLN((u_long) this);
    }
  //
  void ip_list::append(uint32_t locIP, uint32_t gwIP, uint32_t snIP,
                       const char ssid[NET_MAX_SSID_LEN],
                       const char pw[NET_MAX_PW_LEN])
    {
      ip_cell* neu = new ip_cell();
      this->add((void*) neu);
      neu->init(locIP, gwIP, snIP, ssid, pw);
      char stmp[NET_MAX_SSID_LEN];
      neu->getSSID(stmp);
                #if (MDIP_DEBUG > CFG_DEBUG_NONE)
                    SOUT(millis());
                    SOUT("  append ip_cell "); SOUTHEX((u_long) neu);
                    SOUT("  locIP "); SOUTHEX(neu->locIP()); SOUT("  ssid "); SOUTLN(stmp);
                #endif
    }


  ip_cell* ip_list::find(const char ssid[NET_MAX_SSID_LEN])
    {
      void*    ptmp = this->pFirst();
      ip_cell* pcell = (ip_cell*) ptmp;
      char myname[NET_MAX_SSID_LEN + 1] = "";
                #if (MDIP_DEBUG > CFG_DEBUG_NONE)
                    SOUT(" ip_list::find search for ssid "); SOUT(ssid); //SOUT(" ptmp "); SOUTHEXLN((u_long) ptmp);
                #endif
      while ( ptmp != NULL )
        {
          pcell = (ip_cell*) ptmp;
          pcell->getSSID(myname);
                          //SOUT(" ptmp "); SOUTHEX((u_long) ptmp); SOUT(" cell ssid "); SOUT(myname);
          if (strcmp(myname, ssid) == 0)
            {
                          //SOUT(" ssid found "); SOUTLN(myname);
              break;
            }
          else
            {
                          //SOUTLN(" ssid wrong -> continue");
            }
          ptmp = pcell->pNext();
        }
                          //SOUT(" exit find pCell "); SOUTHEX((u_long) ptmp); SOUT(" cell ssid "); SOUTLN(myname);
      return (ip_cell*) ptmp;
    }

/* EOF */

