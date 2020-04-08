/************************************************************/
/*    NAME: searsda                                         */
/*    ORGN: MIT                                             */
/*    FILE: PointAssign.cpp                                 */
/*    DATE: 11 Mar 2020                                     */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "PointAssign.h"
//#include "ACTable.h"

using namespace std;

//---------------------------------------------------------
// Constructor

PointAssign::PointAssign()
{

  m_string_index=1;
  m_num_iteration=false;
  
}

//---------------------------------------------------------
// Destructor

PointAssign::~PointAssign()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool PointAssign::OnNewMail(MOOSMSG_LIST &NewMail)
{
  //AppCastingMOOSApp::OnNewMail(NewMail);
  
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
    if (key == "VISIT_POINT"){
      //will be passed VISIT_POINT_VNAME with uFldShoreBroker
      m_visit_point = msg.GetString(); // reads my mail
      m_mylist.push_back(m_visit_point); //creates ordered list of my mail

      if(m_visit_point=="lastpoint"){
	m_num_iteration=true;
      }
    }
    
  }
  
  return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool PointAssign::OnConnectToServer()
{
   RegisterVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool PointAssign::Iterate()
{
  //AppCastingMOOSApp::Iterate();

  //AppCastingMOOSApp::PostReport();

  if(m_num_iteration==true){

    list<string>::iterator p;

    //----------Method1: Assign Alternatively -----------
    if(m_assign_by_region=="FALSE"){

      for(p=m_mylist.begin(); p!=m_mylist.end(); p++){
	string str = *p;
	string start =str;
	string foo_1 = biteStringX(start,',');
	string foo_2 = biteStringX(foo_1,'=');
	string foo_3 = biteStringX(start,',');
	string foo_4 = biteStringX(foo_3,'=');
	string foo_5 = biteStringX(start,'=');

	
	if(m_string_index==1){
	  Notify("VISIT_POINT_"+m_vname_1, "firstpoint");
	  Notify("VISIT_POINT_"+m_vname_2, "firstpoint");
	}
	else if(m_string_index >=2){
	  if(m_string_index <=101){
	    if(m_string_index % 2 ==0){
	      Notify("VISIT_POINT_"+m_vname_1,str); //EVEN-VEH1
	      postViewPoint(stod(foo_1),stod(foo_3),start,"red");
	    }
	    else{
	      Notify("VISIT_POINT_"+m_vname_2,str); //ODD-VEH2
	      postViewPoint(stod(foo_1),stod(foo_3),start,"yellow");
	    }
	  }
	}
	
	else if(m_string_index == 102){
	  Notify("VISIT_POINT_"+m_vname_1,"lastpoint");
	  Notify("VISIT_POINT_"+m_vname_2,"lastpoint");
	}
	m_string_index++;
      }
      
    }
    


  //-----------Method2: Assign by Region-------------
    else if(m_assign_by_region=="TRUE"){
      
      for(p=m_mylist.begin(); p!=m_mylist.end(); p++){
	string str = *p;
	string start =str;
	string foo_1 = biteStringX(start,',');
	string foo_2 = biteStringX(foo_1,'=');
	string foo_3 = biteStringX(start,',');
	string foo_4 = biteStringX(foo_3,'=');
	string foo_5 = biteStringX(start,'=');
	
	if(m_string_index==1){
	  Notify("VISIT_POINT_"+m_vname_1, "firstpoint");
	  Notify("VISIT_POINT_"+m_vname_2, "firstpoint");
	}
	
	else if(m_string_index >=2){
	  if(m_string_index <=101){
	    if(stod(foo_1) <87.5){
	      Notify("VISIT_POINT_"+m_vname_1,str); //WEST REGION
	      postViewPoint(stod(foo_1),stod(foo_3),start,"red");
	    }
	    
	    else{ 
	      Notify("VISIT_POINT_"+m_vname_2,str); //EAST REGION
	      postViewPoint(stod(foo_1),stod(foo_3),start,"yellow");
	    }
	  }
	}
	
	else if(m_string_index == 102){
	  Notify("VISIT_POINT_"+m_vname_1,"lastpoint");
	  Notify("VISIT_POINT_"+m_vname_2,"lastpoint");
	}
	m_string_index++;
	
	
      }
      Notify("VISIT_POINT_"+m_vname_1,"lastpoint");
      Notify("VISIT_POINT_"+m_vname_2,"lastpoint");
    }
    m_num_iteration=false;
  }
  
  
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool PointAssign::OnStartUp()
{
  //AppCastingMOOSApp::OnStartUp();
  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string line  = *p;
      string param = toupper(biteStringX(line, '='));
      string value = line;

      if(param == "VNAME_1"){
	m_vname_1=value;
      }
      else if(param=="VNAME_2"){
	m_vname_2=value;
      }
      else if(param=="ASSIGN_BY_REGION"){
	m_assign_by_region=value;
      }
      
    }
  }
  
  RegisterVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void PointAssign::RegisterVariables()
{
  //AppCastingMOOSApp::RegisterVariables();
  // Register("FOOBAR", 0);

   Register("VISIT_POINT", 0);

}



//------------------------------------------------------------
// Procedure: postViewPoint

void PointAssign::postViewPoint(double x, double y, string label, string color)
{
  XYPoint point(x, y);
  point.set_label(label);
  point.set_color("vertex", color);
  point.set_param("vertex_size", "2");
  
  string spec = point.get_spec();
  Notify("VIEW_POINT", spec);
}

//------------------------------------------------------------

