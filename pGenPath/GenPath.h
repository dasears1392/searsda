/************************************************************/
/*    NAME: Darien Sears                                    */
/*    ORGN: MIT                                             */
/*    FILE: GenPath.h                                       */
/*    DATE: 12 Mar 2020                                     */
/************************************************************/

#ifndef GenPath_HEADER
#define GenPath_HEADER

#include "MOOS/libMOOS/MOOSLib.h"
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include "MBUtils.h"
#include "XYSegList.h"
#include <list>
#include <string>
#include <math.h>
#include <cmath>

using namespace std;

class GenPath : public AppCastingMOOSApp
{
 public:
   GenPath();
   ~GenPath();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected:
  void RegisterVariables();
  
  
  string point;
  string m_visit_point;

  bool m_num_iteration;
  list<string>m_mylist;
  int m_list_size;
  
  XYSegList my_seglist; //changed from sorted_points

  double m_x;
  double m_y;
  double m_new_x;
  double m_new_y;
  double m_min_x;
  double m_min_y;
  double m_dist;
  double m_min_dist;
  
 private: // Configuration variables
  
  
 private: // State variables
};

#endif 
