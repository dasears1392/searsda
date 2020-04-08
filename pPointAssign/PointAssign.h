/************************************************************/
/*    NAME: searsda                                         */
/*    ORGN: MIT                                             */
/*    FILE: PointAssign.h                                   */
/*    DATE: 11 Mar 2020                                     */
/************************************************************/

#ifndef PointAssign_HEADER
#define PointAssign_HEADER

#include "MOOS/libMOOS/MOOSLib.h"
//#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <string>
#include <vector>
#include "XYPoint.h"

using namespace std;

class PointAssign : public CMOOSApp
{
  
public:
  PointAssign();
  ~PointAssign();
  
protected: // Standard MOOSApp functions to overload
  bool OnNewMail(MOOSMSG_LIST &NewMail);
  bool Iterate();
  bool OnConnectToServer();
  bool OnStartUp();

  
protected:
  void RegisterVariables();
  void postViewPoint(double x, double y, string label, string color);

  int m_string_index;
  bool m_num_iteration;
  
  string m_visit_point;
  list<string> m_mylist; //to handle my mail
  
  string firstpoint; //per lab
  string lastpoint; //per lab
  
  string m_vname; 
  string m_vname_1; //Henry (one per vehicle)
  string m_vname_2; //Gilda (one per vehicle)
  string m_assign_by_region; 
  
private: // Configuration variables
  
private: // State variables
};
#endif
