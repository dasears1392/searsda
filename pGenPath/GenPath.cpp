/************************************************************/
/*    NAME: Darien Sears                                    */
/*    ORGN: MIT                                             */
/*    FILE: GenPath.cpp                                     */
/*    DATE: 12 Mar 2020                                     */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "GenPath.h"
//#include "ACTable.h"

using namespace std;

//---------------------------------------------------------
// Constructor

GenPath::GenPath()
{
  m_num_iteration=false; //initialize variables
  m_x=0;
  m_y=0;
}

//---------------------------------------------------------
// Destructor

GenPath::~GenPath()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool GenPath::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);
  
  MOOSMSG_LIST::iterator p;
   
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;

#if 0 // Keep these around just for template
    string key   = msg.GetKey();
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString(); 
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif

    string key = msg.GetKey();
    
    if(key == "VISIT_POINT") {
      m_visit_point = msg.GetString();
      m_mylist.push_back(m_visit_point);
      
      
      if(m_visit_point=="lastpoint"){
        m_num_iteration=true;
      }
    }
    
  }
  
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool GenPath::OnConnectToServer()
{
   RegisterVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool GenPath::Iterate()
{
  AppCastingMOOSApp::Iterate();
  

  if(m_num_iteration==true){
    m_list_size=m_mylist.size();
    list<string>::iterator p;
    
  for(int i=1; i!=m_list_size-1; i++){
    m_min_dist=1000;

    for(p=next(m_mylist.begin()); p!=prev(m_mylist.end()); p++){
      string str = *p;
      string start =str;
      string foo_1 = biteStringX(start,',');
      string foo_2 = biteStringX(foo_1,'=');
      string foo_3 = biteStringX(start,',');
      string foo_4 = biteStringX(foo_3,'=');
      string foo_5 = biteStringX(start,'=');

      m_new_x=stod(foo_1);
      m_new_y=stod(foo_3);
      m_dist=sqrt(pow((m_new_x-m_x),2)+pow((m_new_y-m_y),2));

      if(m_dist < m_min_dist){
	m_min_dist=m_dist;
	m_min_x  = m_new_x;
	m_min_y  = m_new_y;
      }
    }

    p = m_mylist.erase(p); 
      my_seglist.add_vertex(m_min_x,m_min_y);
      m_x = m_min_x;
      m_y = m_min_y;
    }

    string update_str = "points = ";
    update_str += my_seglist.get_spec();
    Notify("UPDATES_VAR", update_str);

    m_num_iteration=false;
    
  }
   AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool GenPath::OnStartUp()
{
 AppCastingMOOSApp:OnStartUp();
  
  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string line  = *p;
      string param = tolower(biteStringX(line, '='));
      string value = line;
      //bool handled = false;
      
      if(param == "foo") {
        //handled
      }
      else if(param == "bar") {
        //handled
      }
      
    }
  }
  
  RegisterVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void GenPath::RegisterVariables()
{
  AppCastingMOOSApp::RegisterVariables();
   
  // Register("FOOBAR", 0);
  Register("VISIT_POINT",0);
  Register("VIEW_POINT",0);
 
}



