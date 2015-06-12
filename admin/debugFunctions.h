/* 
 * File:   debugFunctions.h
 * Author: yvan
 *
 * Created on May 10, 2015, 4:18 PM
 */

#ifndef DEBUGFUNCTIONS_H
#define	DEBUGFUNCTIONS_H


class debugFunctions {
public:
  void printHelp();
  
  void parse(int argc, char** argv);
  
private:
  void removeAllStudents();
  void groupsToSmartschool();
  void convertToNewAccount();
  void testFunction();
};

debugFunctions & DebugFunctions();

#endif	/* DEBUGFUNCTIONS_H */

